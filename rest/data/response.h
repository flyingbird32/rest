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
    std::string body;
    std::unordered_map<std::string, std::string> headers;
public:
    Response() {}

    inline std::unordered_map<std::string, std::string> getHeaders()
    {
        return this->headers;
    }

    inline std::string getBody()
    {
        return this->body;
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
};