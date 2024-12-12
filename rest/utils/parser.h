
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <variant>
#include <unordered_set>

#include <winsock2.h>
#include <ws2tcpip.h>

#include "../data/enums.h"
#include "../data/request.h"
#include "../data/response.h"
#include "converter.h"

namespace parser
{
    std::string getClientIpAddress(SOCKET clientSocket)
    {
        sockaddr_in clientAddr;
        int addrSize = sizeof(clientAddr);
        char ipBuffer[INET_ADDRSTRLEN];

        if (getpeername(clientSocket, (sockaddr*)&clientAddr, &addrSize) == 0) {
            inet_ntop(AF_INET, &clientAddr.sin_addr, ipBuffer, sizeof(ipBuffer));
            return std::string(ipBuffer);
        }

        return "unknown";
    }

    Request parseRequest(std::string request, SOCKET currentSocket)
    {
        std::istringstream stream(request);
        std::string line;

        std::getline(stream, line);
        size_t methodEnd = line.find(' ');
        std::string methodStr = line.substr(0, methodEnd);
        HTTP_METHOD method = converter::httpMethod(methodStr);

        size_t urlEnd = line.find(' ', methodEnd + 1);
        std::string url = line.substr(methodEnd + 1, urlEnd - methodEnd - 1);

        std::unordered_map<std::string, std::string> headers;
        std::unordered_map<std::string, std::string> additionalHeaders;
        while (std::getline(stream, line) && !line.empty() && line != "\r")
        {
            size_t colonPos = line.find(':');
            if (colonPos != std::string::npos)
            {
                std::string headerName = line.substr(0, colonPos);
                std::string headerValue = line.substr(colonPos + 1);
                headerValue.erase(0, headerValue.find_first_not_of(" \t"));
                headers[headerName] = headerValue;
            }
        }

        std::string body;
        if (headers.count("Content-Length"))
        {
            int contentLength = std::stoi(headers["Content-Length"]);
            body.resize(contentLength);
            stream.read(&body[0], contentLength);
        }

        CONTENT_TYPE contentType = CONTENT_TYPE::UNKNOWN;
        if (headers.count("Content-Type"))
        {
            std::string contentTypeStr = headers["Content-Type"];
            contentType = converter::contentType(contentTypeStr);
        }

        Request parsedRequest(url, body, method);
        parsedRequest.authorization = headers["Authorization"];
        parsedRequest.host = headers["Host"];
        parsedRequest.accept = headers["Accept"];
        parsedRequest.userAgent = headers["User-Agent"];
        parsedRequest.acceptEncoding = headers["Accept-Encoding"];
        parsedRequest.connection = headers["Connection"];
        parsedRequest.contentType = contentType;
        parsedRequest.contentLength = headers.count("Content-Length") ? std::stoi(headers["Content-Length"]) : 0;
        parsedRequest.response = Response();

        std::unordered_set<std::string> predefinedHeaders = {
            "Authorization", "Host", "Accept", "User-Agent",
            "Accept-Encoding", "Connection", "Content-Type", "Content-Length"
        };

        for (const auto& [headerName, headerValue] : headers)
        {
            if (predefinedHeaders.find(headerName) == predefinedHeaders.end())
            {
                additionalHeaders[headerName] = headerValue;
            }
        }

        parsedRequest.additionalHeaders = additionalHeaders;
        parsedRequest.ipAddress = getClientIpAddress(currentSocket);

        return parsedRequest;
    }
}