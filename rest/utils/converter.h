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

    std::string sanitizeString(const std::string& input)
    {
        std::string sanitized = input;

        sanitized.erase(std::remove_if(sanitized.begin(), sanitized.end(),
            [](unsigned char c) {
                return !isprint(c);
            }),
            sanitized.end());

        std::replace(sanitized.begin(), sanitized.end(), '\n', ' ');
        std::replace(sanitized.begin(), sanitized.end(), '\r', ' ');

        return sanitized;
    }

    HTTP_METHOD httpMethod(const std::string& methodStr)
    {
        static const std::unordered_map<std::string, HTTP_METHOD> methodMap = 
        {
            {"POST", HTTP_METHOD::POST},
            {"GET", HTTP_METHOD::GET}
        };

        auto it = methodMap.find(methodStr);
        return (it != methodMap.end()) ? it->second : HTTP_METHOD::UNKNOWN;
    }

    CONTENT_TYPE contentType(const std::string& contentTypeStr)
    {
        static const std::unordered_map<std::string, CONTENT_TYPE> contentTypeMap = 
        {
            {"text/plain", CONTENT_TYPE::TEXT_PLAIN},
            {"text/html", CONTENT_TYPE::TEXT_HTML},
            {"text/css", CONTENT_TYPE::TEXT_CSS},
            {"text/javascript", CONTENT_TYPE::TEXT_JAVASCRIPT},
            {"text/xml", CONTENT_TYPE::TEXT_XML},
            {"text/csv", CONTENT_TYPE::TEXT_CSV},
            {"application/json", CONTENT_TYPE::APPLICATION_JSON},
            {"application/xml", CONTENT_TYPE::APPLICATION_XML},
            {"application/x-www-form-urlencoded", CONTENT_TYPE::APPLICATION_FORM_URLENCODED},
            {"application/javascript", CONTENT_TYPE::APPLICATION_JAVASCRIPT},
            {"application/pdf", CONTENT_TYPE::APPLICATION_PDF},
            {"application/zip", CONTENT_TYPE::APPLICATION_ZIP},
            {"application/gzip", CONTENT_TYPE::APPLICATION_GZIP},
            {"application/vnd.ms-excel", CONTENT_TYPE::APPLICATION_MS_EXCEL},
            {"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet", CONTENT_TYPE::APPLICATION_MS_EXCEL_XLSX},
            {"application/vnd.ms-powerpoint", CONTENT_TYPE::APPLICATION_MS_POWERPOINT},
            {"application/vnd.openxmlformats-officedocument.presentationml.presentation", CONTENT_TYPE::APPLICATION_MS_POWERPOINT_PPTX},
            {"application/msword", CONTENT_TYPE::APPLICATION_MS_WORD},
            {"application/vnd.openxmlformats-officedocument.wordprocessingml.document", CONTENT_TYPE::APPLICATION_MS_WORD_DOCX},
            {"image/jpeg", CONTENT_TYPE::IMAGE_JPEG},
            {"image/png", CONTENT_TYPE::IMAGE_PNG},
            {"image/gif", CONTENT_TYPE::IMAGE_GIF},
            {"image/webp", CONTENT_TYPE::IMAGE_WEBP},
            {"image/bmp", CONTENT_TYPE::IMAGE_BMP},
            {"image/svg+xml", CONTENT_TYPE::IMAGE_SVG_XML},
            {"audio/mpeg", CONTENT_TYPE::AUDIO_MPEG},
            {"audio/ogg", CONTENT_TYPE::AUDIO_OGG},
            {"audio/wav", CONTENT_TYPE::AUDIO_WAV},
            {"video/mp4", CONTENT_TYPE::VIDEO_MP4},
            {"video/mpeg", CONTENT_TYPE::VIDEO_MPEG},
            {"video/webm", CONTENT_TYPE::VIDEO_WEBM},
            {"video/ogg", CONTENT_TYPE::VIDEO_OGG},
            {"multipart/form-data", CONTENT_TYPE::MULTIPART_FORM_DATA},
            {"multipart/byteranges", CONTENT_TYPE::MULTIPART_BYTERANGES},
            {"application/octet-stream", CONTENT_TYPE::APPLICATION_OCTET_STREAM},
            {"application/rtf", CONTENT_TYPE::APPLICATION_RTF},
            {"application/sql", CONTENT_TYPE::APPLICATION_SQL},
            {"application/wasm", CONTENT_TYPE::APPLICATION_WASM},
            {"application/vnd.apple.installer+xml", CONTENT_TYPE::APPLICATION_MPKG}
        };

        std::string trimmedContentType = trim(contentTypeStr);

        auto it = contentTypeMap.find(trimmedContentType);
        return (it != contentTypeMap.end()) ? it->second : CONTENT_TYPE::UNKNOWN;
    }
}