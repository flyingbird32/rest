#pragma once

#include <string>
#include <algorithm>

#include "../data/content_type.h"
#include "../data/http_method.h"

namespace converter
{
    std::string trim(const std::string& str)
    {
        size_t start = str.find_first_not_of(" \t\r\n");
        size_t end = str.find_last_not_of(" \t\r\n");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    HTTP_METHOD httpMethod(const std::string& methodStr)
    {
        static const std::unordered_map<std::string, HTTP_METHOD> methodMap = {
            {"POST", HTTP_METHOD::POST},
            {"GET", HTTP_METHOD::GET}
        };

        auto it = methodMap.find(methodStr);
        return (it != methodMap.end()) ? it->second : HTTP_METHOD::UNKNOWN;
    }

    CONTENT_TYPE contentType(const std::string& contentTypeStr)
    {
        static const std::unordered_map<std::string, CONTENT_TYPE> contentTypeMap = {
            {"application/x-www-form-urlencoded", CONTENT_TYPE::FORM_URLENCODED},
            {"application/json", CONTENT_TYPE::JSON},
            {"text/plain", CONTENT_TYPE::PLAIN_TEXT}
        };

        std::string trimmedContentType = trim(contentTypeStr);
        auto it = contentTypeMap.find(trimmedContentType);
        return (it != contentTypeMap.end()) ? it->second : CONTENT_TYPE::UNKNOWN;
    }

    std::string httpMethodS(HTTP_METHOD method)
    {
        switch (method)
        {
        case HTTP_METHOD::GET: return "GET";
        case HTTP_METHOD::POST: return "POST";
        default: return "UNKNOWN";
        }
    }

    std::string contentTypeS(CONTENT_TYPE content)
    {
        switch (content)
        {
        case CONTENT_TYPE::FORM_URLENCODED: return "FORM_URLENCODED";
        case CONTENT_TYPE::JSON: return "JSON";
        case CONTENT_TYPE::PLAIN_TEXT: return "PLAIN TEXT";
        case CONTENT_TYPE::XML: return "XML";
        default: return "UNKNOWN";
        }
    }
}