#include "rest.h"
#include <iostream>

Endpoint testMethod(Request& request)
{
	request.response.addHeader("Awesome-Header", "awesome");
	request.response.setBody("<h1>hello!</h1>");

	return Endpoint(HTTP_STATUS_CODE::OK, CONTENT_TYPE::TEXT_HTML);
}

Endpoint testPost(Request& request)
{
	std::string body = "post request body: " + request.body;
	request.response.setBody(body);

	return Endpoint(HTTP_STATUS_CODE::OK, CONTENT_TYPE::TEXT_PLAIN);
}

int main()
{
	rest::Service testService;
	testService.registerEndpoint("/what", HTTP_METHOD::POST, testPost);
	testService.registerEndpoint("/test", HTTP_METHOD::GET, testMethod);
	testService.setStaticDirectory("static");
	testService.start(3200);

	return 0;
}