#include "rest.h"
#include <iostream>

void testMethod(Request request)
{
	printf("calling method: %s, %s\n", request.routeUrl.c_str(), getEnumString(request.method).c_str());

	request.response.addHeader("Awesome-Header", "awesome");
	request.response.setBody("<h1>hello!</h1>");
	request.response.build(HTTP_STATUS_CODE::OK, CONTENT_TYPE::HTML);
}

void testPost(Request request)
{
	printf("calling method: %s, %s\nbody: %s\n", request.routeUrl.c_str(), getEnumString(request.method).c_str(), request.body.c_str());
	std::string body = "post request body: " + request.body;

	request.response.setBody(body);
	request.response.build(HTTP_STATUS_CODE::OK, CONTENT_TYPE::PLAIN_TEXT);
}

int main()
{
	rest::Service testService;

	testService.registerEndpoint("/test", HTTP_METHOD::GET, testMethod);
	testService.registerEndpoint("/what", HTTP_METHOD::POST, testPost);
	testService.start(3200);

	return 0;
}