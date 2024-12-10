#pragma once
#include <map>

#include <string>
#include "enums.h"
#include <iostream>
#include <sstream>

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

struct Response
{
private:
    SOCKET clientSocket;
public:

    Response() : clientSocket(INVALID_SOCKET) {}

    Response(SOCKET currentSocket)
    {
        this->clientSocket = currentSocket;
    }

    // TODO: make simpler & more user friendly
    inline void go(int statusCode, const std::string& statusMessage,
        const std::string& body, CONTENT_TYPE contentType,
        const std::map<std::string, std::string>& customHeaders = {}) {

        std::string contentTypeStr;
        switch (contentType)
        {
        case CONTENT_TYPE::JSON:
            contentTypeStr = "application/json";
            break;
        case CONTENT_TYPE::HTML:
            contentTypeStr = "text/html";
            break;
        case CONTENT_TYPE::XML:
            contentTypeStr = "application/xml";
            break;
        case CONTENT_TYPE::PLAIN_TEXT:
            contentTypeStr = "text/plain";
            break;
        }

        std::stringstream response;
        response << "HTTP/1.1 " << statusCode << " " << statusMessage << "\r\n";
        response << "Content-Type: " << contentTypeStr << "\r\n";
        response << "Content-Length: " << body.size() << "\r\n";

        for (const auto& header : customHeaders)
        {
            response << header.first << ": " << header.second << "\r\n";
        }

        response << "\r\n";
        response << body;

        send(clientSocket, response.str().c_str(), static_cast<int>(response.str().size()), 0);\
            closesocket(clientSocket);
    }
};

struct Request
{
    Request(std::string routeUrl, std::string body, HTTP_METHOD method)
    {
        this->routeUrl = routeUrl;
        this->body = body;
        this->method = method;
    }

    std::string routeUrl;
    std::string body;
    HTTP_METHOD method;
    CONTENT_TYPE contentType;
    std::string authorization;
    std::string host;
    std::string accept;
    std::string userAgent;
    std::string acceptEncoding;
    std::string connection;
    int contentLength;
    Response response;
};