#include "rest.h"
#include <iostream>

Endpoint testMethod(Request& request)
{
	printf("calling method: %s, %s\nbody: %s\n", request.routeUrl.c_str(), enums::getEnumString(request.method).c_str(), request.body.c_str());
	request.response.addHeader("Awesome-Header", "awesome");
	request.response.setBody("<h1>hello!</h1>");

	return Endpoint(HTTP_STATUS_CODE::OK, CONTENT_TYPE::HTML);
}

Endpoint testPost(Request& request)
{
	printf("calling method: %s, %s\nbody: %s\n", request.routeUrl.c_str(), enums::getEnumString(request.method).c_str(), request.body.c_str());
	std::string body = "post request body: " + request.body;
	request.response.setBody(body);

	return Endpoint(HTTP_STATUS_CODE::OK, CONTENT_TYPE::PLAIN_TEXT);
}

int main()
{
	rest::Service testService;
	testService.registerEndpoint("/what", HTTP_METHOD::POST, testPost);
	testService.registerEndpoint("/test", HTTP_METHOD::GET, testMethod);
	testService.start(3200);

	return 0;
}