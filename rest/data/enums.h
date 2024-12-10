#pragma once
#include <iostream>
#include <string>

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

template<typename T>
inline std::string toString(T enum_value);

template<>
inline std::string toString(HTTP_METHOD method)
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
inline std::string toString(CONTENT_TYPE content)
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