#pragma once
#include <map>

#include <unordered_map>
#include <string>
#include <iostream>

#include "enums.h"
#include "response.h"

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
    std::unordered_map<std::string, std::string> additionalHeaders;
};