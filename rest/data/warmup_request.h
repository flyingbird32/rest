#pragma once

#include <string>
#include "content_type.h"
#include "http_method.h"

struct WarmupRequest
{
	WarmupRequest(std::string routeUrl, std::string body, HTTP_METHOD method)
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
};