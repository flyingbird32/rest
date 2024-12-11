#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <sstream>

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include "enums.h"

struct Response
{
private:
    SOCKET clientSocket;
    std::string body;
    std::unordered_map<std::string, std::string> headers;

public:

    Response() : clientSocket(INVALID_SOCKET) {}

    Response(SOCKET currentSocket)
    {
        this->clientSocket = currentSocket;
    }

    inline void setBody(std::string _body)
    {
        this->body = _body;
        headers["Content-Length"] = std::to_string(body.size());
    }

    inline void addHeader(std::string name, std::string value)
    {
        headers[name] = value;
    }

    inline void build(HTTP_STATUS_CODE statusCode, CONTENT_TYPE contentType)
    {
        std::stringstream response;
        response << "HTTP/1.1 " << static_cast<int>(statusCode) << " " << getEnumString(statusCode) << "\r\n";
        response << "Content-Type: " << getEnumString(contentType) << "\r\n";

        for (const auto& header : headers)
        {
            response << header.first << ": " << header.second << "\r\n";
        }

        response << "\r\n";
        response << this->body;

        send(clientSocket, response.str().c_str(), static_cast<int>(response.str().size()), 0);
        closesocket(clientSocket);
    }
};