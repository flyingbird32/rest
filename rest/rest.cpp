#pragma once
#include "utils/parser.h"
#include "rest.h"

using namespace rest;

void Service::registerEndpoint(const std::string& path, HTTP_METHOD requestMethod, void* method)
{
	routes.push_back({ path, requestMethod, method });
}

void Service::callRoute(void* handler, Request request)
{
	reinterpret_cast<void(*)(Request)>(handler)(request);
}

void sendResponse(SOCKET clientSocket, const std::string& response) 
{
    send(clientSocket, response.c_str(), response.size(), 0);
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

	WarmupRequest warmupRequest = parser::parseWarmup(request);

	printf("method: %s, url: %s, body: %s, content: %s\n", converter::httpMethodS(warmupRequest.method).c_str(), warmupRequest.routeUrl.c_str(), warmupRequest.body.c_str(), converter::contentTypeS(warmupRequest.contentType).c_str());
    
	std::string response =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/plain\r\n"
		"Content-Length: 7\r\n\r\n"
		"awesome";
	sendResponse(clientSocket, response);
    closesocket(clientSocket);
}

void Service::start(int port)
{
	WSADATA wsData;
	WSAStartup(MAKEWORD(2, 2), &wsData);

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in serverAddr = { 0 };
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(serverSocket, SOMAXCONN);

	printf("started on port %i\n", port);

	while (true) 
	{
		SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
		if (clientSocket != INVALID_SOCKET) 
		{
			handleRequest(clientSocket);
		}
	}

	closesocket(serverSocket);
	WSACleanup();
}

void test()
{
	printf("test\n");
}