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

	for (Route route : this->routes)
	{
		if (route.path == parsedRequest.routeUrl.c_str() && route.method == parsedRequest.method)
		{
			callRoute(route.handler, parsedRequest);
			break;
		}
	}

	// fix this, because what? - also need better error handling
	std::string notFoundHtml = "<head><title>404 Not Found</title></head><body><h1>404 Not Found</h1><p>The page you are looking for could not be found.</p></body>";

	Response errorResponse(clientSocket);
	errorResponse.setBody(notFoundHtml);
	errorResponse.build(HTTP_STATUS_CODE::NOT_FOUND, CONTENT_TYPE::HTML);
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