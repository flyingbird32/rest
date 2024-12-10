#include "rest.h"
#include <iostream>

void testMethod(Request request)
{
	printf("calling method: %s, %s\n", request.routeUrl.c_str(), toString(request.method).c_str());
	request.response.go(200, "OK", "<h1>yay</h1>", CONTENT_TYPE::HTML);
}

void testPost(Request request)
{
	printf("calling method: %s, %s\nbody: %s", request.routeUrl.c_str(), toString(request.method).c_str(), request.body.c_str());
	std::string body = "post request body: " + request.body;
	request.response.go(200, "OK", body, CONTENT_TYPE::PLAIN_TEXT);
}

int main()
{
	rest::Service testService;

	testService.registerEndpoint("/test", HTTP_METHOD::GET, testMethod);
	testService.registerEndpoint("/what", HTTP_METHOD::POST, testPost);
	testService.start(3200);

	return 0;
}