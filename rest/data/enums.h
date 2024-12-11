#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

enum class HTTP_METHOD
{
    GET,
    POST,
    UNKNOWN
};

enum class CONTENT_TYPE
{
    FORM_URLENCODED,
    JSON,
    PLAIN_TEXT,
    XML,
    HTML,
    UNKNOWN
};

enum class HTTP_STATUS_CODE
{
    CONTINUE = 100,
    SWITCHING_PROTOCOLS = 101,
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NON_AUTHORITATIVE_INFORMATION = 203,
    NO_CONTENT = 204,
    RESET_CONTENT = 205,
    PARTIAL_CONTENT = 206,
    MULTI_STATUS = 207,
    ALREADY_REPORTED = 208,
    IM_USED = 226,
    MULTIPLE_CHOICES = 300,
    MOVED_PERMANENTLY = 301,
    FOUND = 302,
    SEE_OTHER = 303,
    NOT_MODIFIED = 304,
    USE_PROXY = 305,
    TEMPORARY_REDIRECT = 307,
    PERMANENT_REDIRECT = 308,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    PAYMENT_REQUIRED = 402,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    METHOD_NOT_ALLOWED = 405,
    NOT_ACCEPTABLE = 406,
    PROXY_AUTHENTICATION_REQUIRED = 407,
    REQUEST_TIMEOUT = 408,
    CONFLICT = 409,
    GONE = 410,
    LENGTH_REQUIRED = 411,
    PRECONDITION_FAILED = 412,
    PAYLOAD_TOO_LARGE = 413,
    URI_TOO_LONG = 414,
    UNSUPPORTED_MEDIA_TYPE = 415,
    RANGE_NOT_SATISFIABLE = 416,
    EXPECTATION_FAILED = 417,
    IM_A_TEAPOT = 418,
    MISDIRECTED_REQUEST = 421,
    UNPROCESSABLE_ENTITY = 422,
    LOCKED = 423,
    FAILED_DEPENDENCY = 424,
    TOO_EARLY = 425,
    UPGRADE_REQUIRED = 426,
    PRECONDITION_REQUIRED = 428,
    TOO_MANY_REQUESTS = 429,
    REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
    UNAVAILABLE_FOR_LEGAL_REASONS = 451,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503,
    GATEWAY_TIMEOUT = 504,
    HTTP_VERSION_NOT_SUPPORTED = 505,
    VARIANT_ALSO_NEGOTIATES = 506,
    INSUFFICIENT_STORAGE = 507,
    LOOP_DETECTED = 508,
    NOT_EXTENDED = 510,
    NETWORK_AUTHENTICATION_REQUIRED = 511
};

template<typename T>
inline std::string getEnumString(T enum_value);

template<>
inline std::string getEnumString(HTTP_STATUS_CODE code)
{
    static const std::unordered_map<HTTP_STATUS_CODE, std::string> statusCodeMap = {
        {HTTP_STATUS_CODE::CONTINUE, "Continue"},
        {HTTP_STATUS_CODE::SWITCHING_PROTOCOLS, "Switching Protocols"},
        {HTTP_STATUS_CODE::OK, "OK"},
        {HTTP_STATUS_CODE::CREATED, "Created"},
        {HTTP_STATUS_CODE::ACCEPTED, "Accepted"},
        {HTTP_STATUS_CODE::NON_AUTHORITATIVE_INFORMATION, "Non-Authoritative Information"},
        {HTTP_STATUS_CODE::NO_CONTENT, "No Content"},
        {HTTP_STATUS_CODE::RESET_CONTENT, "Reset Content"},
        {HTTP_STATUS_CODE::PARTIAL_CONTENT, "Partial Content"},
        {HTTP_STATUS_CODE::MULTI_STATUS, "Multi-Status"},
        {HTTP_STATUS_CODE::ALREADY_REPORTED, "Already Reported"},
        {HTTP_STATUS_CODE::IM_USED, "IM Used"},
        {HTTP_STATUS_CODE::MULTIPLE_CHOICES, "Multiple Choices"},
        {HTTP_STATUS_CODE::MOVED_PERMANENTLY, "Moved Permanently"},
        {HTTP_STATUS_CODE::FOUND, "Found"},
        {HTTP_STATUS_CODE::SEE_OTHER, "See Other"},
        {HTTP_STATUS_CODE::NOT_MODIFIED, "Not Modified"},
        {HTTP_STATUS_CODE::USE_PROXY, "Use Proxy"},
        {HTTP_STATUS_CODE::TEMPORARY_REDIRECT, "Temporary Redirect"},
        {HTTP_STATUS_CODE::PERMANENT_REDIRECT, "Permanent Redirect"},
        {HTTP_STATUS_CODE::BAD_REQUEST, "Bad Request"},
        {HTTP_STATUS_CODE::UNAUTHORIZED, "Unauthorized"},
        {HTTP_STATUS_CODE::PAYMENT_REQUIRED, "Payment Required"},
        {HTTP_STATUS_CODE::FORBIDDEN, "Forbidden"},
        {HTTP_STATUS_CODE::NOT_FOUND, "Not Found"},
        {HTTP_STATUS_CODE::METHOD_NOT_ALLOWED, "Method Not Allowed"},
        {HTTP_STATUS_CODE::NOT_ACCEPTABLE, "Not Acceptable"},
        {HTTP_STATUS_CODE::PROXY_AUTHENTICATION_REQUIRED, "Proxy Authentication Required"},
        {HTTP_STATUS_CODE::REQUEST_TIMEOUT, "Request Timeout"},
        {HTTP_STATUS_CODE::CONFLICT, "Conflict"},
        {HTTP_STATUS_CODE::GONE, "Gone"},
        {HTTP_STATUS_CODE::LENGTH_REQUIRED, "Length Required"},
        {HTTP_STATUS_CODE::PRECONDITION_FAILED, "Precondition Failed"},
        {HTTP_STATUS_CODE::PAYLOAD_TOO_LARGE, "Payload Too Large"},
        {HTTP_STATUS_CODE::URI_TOO_LONG, "URI Too Long"},
        {HTTP_STATUS_CODE::UNSUPPORTED_MEDIA_TYPE, "Unsupported Media Type"},
        {HTTP_STATUS_CODE::RANGE_NOT_SATISFIABLE, "Range Not Satisfiable"},
        {HTTP_STATUS_CODE::EXPECTATION_FAILED, "Expectation Failed"},
        {HTTP_STATUS_CODE::IM_A_TEAPOT, "I'm a Teapot"},
        {HTTP_STATUS_CODE::MISDIRECTED_REQUEST, "Misdirected Request"},
        {HTTP_STATUS_CODE::UNPROCESSABLE_ENTITY, "Unprocessable Entity"},
        {HTTP_STATUS_CODE::LOCKED, "Locked"},
        {HTTP_STATUS_CODE::FAILED_DEPENDENCY, "Failed Dependency"},
        {HTTP_STATUS_CODE::TOO_EARLY, "Too Early"},
        {HTTP_STATUS_CODE::UPGRADE_REQUIRED, "Upgrade Required"},
        {HTTP_STATUS_CODE::PRECONDITION_REQUIRED, "Precondition Required"},
        {HTTP_STATUS_CODE::TOO_MANY_REQUESTS, "Too Many Requests"},
        {HTTP_STATUS_CODE::REQUEST_HEADER_FIELDS_TOO_LARGE, "Request Header Fields Too Large"},
        {HTTP_STATUS_CODE::UNAVAILABLE_FOR_LEGAL_REASONS, "Unavailable For Legal Reasons"},
        {HTTP_STATUS_CODE::INTERNAL_SERVER_ERROR, "Internal Server Error"},
        {HTTP_STATUS_CODE::NOT_IMPLEMENTED, "Not Implemented"},
        {HTTP_STATUS_CODE::BAD_GATEWAY, "Bad Gateway"},
        {HTTP_STATUS_CODE::SERVICE_UNAVAILABLE, "Service Unavailable"},
        {HTTP_STATUS_CODE::GATEWAY_TIMEOUT, "Gateway Timeout"},
        {HTTP_STATUS_CODE::HTTP_VERSION_NOT_SUPPORTED, "HTTP Version Not Supported"},
        {HTTP_STATUS_CODE::VARIANT_ALSO_NEGOTIATES, "Variant Also Negotiates"},
        {HTTP_STATUS_CODE::INSUFFICIENT_STORAGE, "Insufficient Storage"},
        {HTTP_STATUS_CODE::LOOP_DETECTED, "Loop Detected"},
        {HTTP_STATUS_CODE::NOT_EXTENDED, "Not Extended"},
        {HTTP_STATUS_CODE::NETWORK_AUTHENTICATION_REQUIRED, "Network Authentication Required"}
    };

    auto it = statusCodeMap.find(code);
    if (it != statusCodeMap.end()) {
        return it->second;
    }
    else {
        return "Unknown";
    }
}

template<>
inline std::string getEnumString(HTTP_METHOD method)
{
    switch (method)
    {
    case HTTP_METHOD::GET: return "GET";
    case HTTP_METHOD::POST: return "POST";
    case HTTP_METHOD::UNKNOWN: return "UNKNOWN";
    default: return "INVALID";
    }
}

template<>
inline std::string getEnumString(CONTENT_TYPE content)
{
    switch (content)
    {
    case CONTENT_TYPE::FORM_URLENCODED: return "application/x-www-form-urlencoded";
    case CONTENT_TYPE::JSON: return "application/json";
    case CONTENT_TYPE::PLAIN_TEXT: return "text/plain";
    case CONTENT_TYPE::HTML: return "text/html";
    case CONTENT_TYPE::XML: return "application/xml";
    default: return "UNKNOWN";
    }
}