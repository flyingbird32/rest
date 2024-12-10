#include "rest.h"
#include <iostream>

void testMethod(rest::Service::Request request)
{
	printf("test: %s, %s\n", request.path.c_str(), request.data.c_str());
}

int main()
{
	rest::Service testService;
	
	testService.registerEndpoint("/test", HTTP_METHOD::GET, testMethod);
	
	testService.start(3200);

	return 0;
}