#pragma once

#include <string>
#include <algorithm>

#include "../data/enums.h"

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
}