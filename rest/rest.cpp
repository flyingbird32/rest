#pragma once
#include <filesystem>
#include <fstream>

#include "utils/parser.h"
#include "rest.h"
#include "data/endpoint.h"
#include "utils/logger.h"

using namespace rest;

void Service::registerController(const std::string& basePath, BaseController* controller) 
{
    for (const auto& endpoint : controller->getEndpoints()) 
    {
        std::string fullPath = basePath + endpoint.path;
        registerEndpoint(fullPath, endpoint.method, endpoint.handler);
    }
}

void Service::registerController(BaseController* controller)
{
    for (const auto& endpoint : controller->getEndpoints())
    {
        registerEndpoint(endpoint.path, endpoint.method, endpoint.handler);
    }
}
    
void Service::registerEndpoint(const std::string& path, HTTP_METHOD method, Endpoint(*handler)(Request&))
{
    routes.push_back({ path, method, handler });
    LogInfo("[%s] %s - registered", enums::getEnumString(method).c_str(), path.c_str());
}

void Service::logConnections(bool value)
{
    LogWarning("logging connections, not recommended for production");
    this->shouldLogConnections = value;
}

void Service::callRoute(void* handler, Request& request, SOCKET currentSocket)
{
    Endpoint endpointData = reinterpret_cast<Endpoint(*)(Request&)>(handler)(request);
    auto statusCode = endpointData.getStatusCode();

    if (shouldLogConnections)
    {
        std::string sanitizedUserAgent = converter::sanitizeString(request.userAgent);
        std::string sanitizedIpAddress = converter::sanitizeString(request.ipAddress);

        LogInfo("[%s] %s - %s (%s)",
            enums::getEnumString(request.method).c_str(),
            request.routeUrl.c_str(),
            sanitizedUserAgent.c_str(),
            sanitizedIpAddress.c_str());
    }

    std::string responseBody = request.response.getBody();

    if (responseBody.empty())
    {
        LogError("builder has no body for [%s] %s. defaulting to empty body",
            enums::getEnumString(request.method).c_str(), request.routeUrl.c_str());
        responseBody = "";
    }

    request.response.addHeader("Content-Length", std::to_string(responseBody.size()));

    std::stringstream response;
    response << "HTTP/1.1 " << static_cast<int>(statusCode) << " " << enums::getEnumString(statusCode) << "\r\n";
    response << "Content-Type: " << enums::getEnumString(endpointData.getContentType()) << "\r\n";

    for (const auto& header : request.response.getHeaders())
    {
        response << header.first << ": " << header.second << "\r\n";
    }

    response << "\r\n" << responseBody;

    send(currentSocket, response.str().c_str(), static_cast<int>(response.str().size()), 0);
    closesocket(currentSocket);
}

// TODO: make this more advanced? maybe custom, maybe look for 404.html in static directory for defaults idk
void Service::send404Response(SOCKET currentSocket)
{
    HTTP_STATUS_CODE statusCode = HTTP_STATUS_CODE::NOT_FOUND;

    std::stringstream response;
    response << "HTTP/1.1 " << static_cast<int>(statusCode) << " " << enums::getEnumString(statusCode) << "\r\n";
    response << "Content-Type: " << enums::getEnumString(CONTENT_TYPE::TEXT_HTML) << "\r\n";

    response << "\r\n";
    response << "<h1>404 Not Found</h1>";

    send(currentSocket, response.str().c_str(), static_cast<int>(response.str().size()), 0);
    closesocket(currentSocket);
}

void Service::renderFile(const std::string& filePath, SOCKET currentSocket)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open())
    {
        send404Response(currentSocket);
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    std::string extension = std::filesystem::path(filePath).extension().string();
    static const std::unordered_map<std::string, std::string> contentTypeMap =
    {
        {".html", "text/html"},
        {".css", "text/css"},
        {".js", "application/javascript"},
        {".json", "application/json"},
        {".png", "image/png"},
        {".jpg", "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".gif", "image/gif"},
        {".bmp", "image/bmp"},
        {".svg", "image/svg+xml"},
        {".ico", "image/vnd.microsoft.icon"},
        {".woff", "font/woff"},
        {".woff2", "font/woff2"},
        {".ttf", "font/ttf"},
        {".otf", "font/otf"},
        {".xml", "application/xml"},
        {".pdf", "application/pdf"},
        {".zip", "application/zip"},
        {".gzip", "application/gzip"},
        {".txt", "text/plain"}
    };

    std::string contentType = "application/octet-stream";
    auto it = contentTypeMap.find(extension);
    if (it != contentTypeMap.end())
        contentType = it->second;

    std::stringstream response;
    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Type: " << contentType << "\r\n";
    response << "Content-Length: " << content.size() << "\r\n";
    response << "Connection: close\r\n";
    response << "\r\n";
    response << content;

    send(currentSocket, response.str().c_str(), static_cast<int>(response.str().size()), 0);
    closesocket(currentSocket);
}

void Service::setStaticDirectory(const std::string& directory)
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string currentDirectory = std::filesystem::path(buffer).parent_path().string();

    this->staticDirectory = std::filesystem::absolute(std::filesystem::path(currentDirectory) / directory).string();

    if (!staticDirectory.empty() && staticDirectory.back() != '\\')
        staticDirectory += '\\';
}

bool Service::doesStaticDirectoryExist()
{
    std::string path = this->staticDirectory;

    if (path.empty())
        return false;

    if (!std::filesystem::is_directory(path))
    {
        LogError("static directory '%s' doesn't exist", path.c_str());
        return false;
    }

    return true;
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

    if (routeFound)
        return;

    if (doesStaticDirectoryExist())
    {
        std::filesystem::path fullStaticDirectory(staticDirectory);
        std::string currentRoute = parsedRequest.routeUrl.substr(1);

        for (const auto& entry : std::filesystem::recursive_directory_iterator(fullStaticDirectory))
        {
            if (!entry.is_regular_file())
                continue;

            std::string relativePath = std::filesystem::relative(entry.path(), fullStaticDirectory).string();
            std::replace(relativePath.begin(), relativePath.end(), '\\', '/');

            if (relativePath == currentRoute)
            {
                renderFile(entry.path().string(), clientSocket);
                return;
            }
        }
    }

    send404Response(clientSocket);
}

void Service::start(int port)
{
    // initializes winsock for network communication on windows
    WSADATA wsData;
    WSAStartup(MAKEWORD(2, 2), &wsData);

    // creates a socket and binds it to a port for listening
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress = { 0 };
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, SOMAXCONN);

    LogInfo("server started on port: %i", port);

    // sets up fd_set structures for monitoring sockets
    fd_set masterSet, readSet;
    FD_ZERO(&masterSet);
    FD_SET(serverSocket, &masterSet);
    std::vector<SOCKET> clientSockets;

    while (true)
    {
        // duplicates master set to read set for select() call
        readSet = masterSet;

        // monitors sockets for activity without blocking
        int activity = select(0, &readSet, nullptr, nullptr, nullptr);

        if (activity == SOCKET_ERROR)
        {
            LogError("select error %d\n", WSAGetLastError());
            break;
        }

        if (FD_ISSET(serverSocket, &readSet))
        {
            // accepts new client connections
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
                // handles client request and closes the socket
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