#pragma once
#include "utils/parser.h"
#include "rest.h"
#include "data/endpoint.h"

using namespace rest;

void Service::registerEndpoint(const std::string& path, HTTP_METHOD method, Endpoint(*handler)(Request&))
{
    routes.push_back({ path, method, handler });
}

void Service::callRoute(void* handler, Request& request, SOCKET currnetSocket)
{
    Endpoint endpointData = reinterpret_cast<Endpoint(*)(Request&)>(handler)(request);
    auto statusCode = endpointData.getStatusCode();

    std::stringstream response;
    response << "HTTP/1.1 " << static_cast<int>(statusCode) << " " << enums::getEnumString(statusCode) << "\r\n";
    response << "Content-Type: " << enums::getEnumString(endpointData.getContentType()) << "\r\n";

    for (const auto& header : request.response.getHeaders())
    {
        response << header.first << ": " << header.second << "\r\n";
    }

    response << "\r\n";
    response << request.response.getBody();

    send(currnetSocket, response.str().c_str(), static_cast<int>(response.str().size()), 0);
    closesocket(currnetSocket); // hmm
}

void Service::handleRequest(SOCKET clientSocket)
{
    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (!(bytesReceived > 0))
    {
        closesocket(clientSocket);
        return;
    }

    buffer[bytesReceived] = '\0';
    std::string request(buffer);
    Request parsedRequest = parser::parseRequest(request, clientSocket);

    bool routeFound = false;

    for (Route route : this->routes)
    {
        if (route.path == parsedRequest.routeUrl.c_str() && route.method == parsedRequest.method)
        {
            callRoute(route.handler, parsedRequest, clientSocket);
            routeFound = true;
            break;
        }
    }

    if (!routeFound)
    {
        printf("route was not found should 404\n");
    }
}

// uses select() to poll for active sockets (server and clients) and handle multiple
// connections concurrently without blocking. it accepts new clients, processes requests
// as they become ready, and closes sockets after handling. ensures non-blocking, efficient
// handling of multiple requests hopefully....
void Service::start(int port)
{
    WSADATA wsData;
    WSAStartup(MAKEWORD(2, 2), &wsData);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress = { 0 };
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, SOMAXCONN);

    printf("started server on port %i\n", port);

    fd_set masterSet, readSet;
    FD_ZERO(&masterSet);
    FD_ZERO(&readSet);

    FD_SET(serverSocket, &masterSet);
    std::vector<SOCKET> clientSockets;

    while (true)
    {
        readSet = masterSet;

        int activity = select(0, &readSet, nullptr, nullptr, nullptr);

        if (activity == SOCKET_ERROR)
        {
            printf("select error: %d\n", WSAGetLastError());
            break;
        }

        if (FD_ISSET(serverSocket, &readSet))
        {
            SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
            if (clientSocket != INVALID_SOCKET)
            {
                FD_SET(clientSocket, &masterSet);
                clientSockets.push_back(clientSocket);
            }
        }

        for (size_t i = 0; i < clientSockets.size(); ++i)
        {
            SOCKET clientSocket = clientSockets[i];

            if (FD_ISSET(clientSocket, &readSet))
            {
                handleRequest(clientSocket);

                FD_CLR(clientSocket, &masterSet);
                closesocket(clientSocket);
                clientSockets.erase(clientSockets.begin() + i);
                --i;
            }
        }
    }

    closesocket(serverSocket);
    WSACleanup();
}