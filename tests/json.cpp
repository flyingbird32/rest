#include "rest.h"
#include <iostream>

Endpoint jsonEcho(Request& request)
{
	if (request.contentType != CONTENT_TYPE::APPLICATION_JSON)
	{
		request.response.setBody("{\"error\": \"please send json in the body\"}");
		return Endpoint(HTTP_STATUS_CODE::FORBIDDEN, CONTENT_TYPE::APPLICATION_JSON);
	}

	request.response.setBody(request.body);
	return Endpoint(HTTP_STATUS_CODE::OK, CONTENT_TYPE::APPLICATION_JSON);
}

Endpoint jsonMethod(Request& request)
{
	request.response.setBody("{\"hello\": true}");
	return Endpoint(HTTP_STATUS_CODE::OK, CONTENT_TYPE::APPLICATION_JSON);
}

int main()
{
	rest::Service testService;
	testService.registerEndpoint("/echo", HTTP_METHOD::POST, jsonEcho);
	testService.registerEndpoint("/json", HTTP_METHOD::GET, jsonMethod);
	testService.start(3200);

	return 0;
}