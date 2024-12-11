#pragma once

#include "enums.h"
#include "response.h"

struct Endpoint
{
private:
    HTTP_STATUS_CODE statusCode;
    CONTENT_TYPE contentType;
public:
    Endpoint(HTTP_STATUS_CODE statusCode, CONTENT_TYPE contentType)
    {
        this->statusCode = statusCode;
        this->contentType = contentType;
    }

    HTTP_STATUS_CODE getStatusCode()
    {
        return this->statusCode;
    }

    CONTENT_TYPE getContentType()
    {
        return this->contentType;
    }
};