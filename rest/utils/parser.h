
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>

#include "../data/content_type.h"
#include "../data/http_method.h"
#include "../data/warmup_request.h"
#include "converter.h"

namespace parser
{
    WarmupRequest parseWarmup(std::string request)
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

        WarmupRequest warmupRequest(url, body, method);
        warmupRequest.authorization = headers["Authorization"];
        warmupRequest.host = headers["Host"];
        warmupRequest.accept = headers["Accept"];
        warmupRequest.userAgent = headers["User-Agent"];
        warmupRequest.acceptEncoding = headers["Accept-Encoding"];
        warmupRequest.connection = headers["Connection"];
        warmupRequest.contentType = contentType;
        warmupRequest.contentLength = headers.count("Content-Length") ? std::stoi(headers["Content-Length"]) : 0;

        return warmupRequest;
    }
}