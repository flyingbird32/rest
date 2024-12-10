#pragma once
#include <iostream>
#include "rest.h"

namespace rest
{
	void Service::registerEndpoint(const std::string& path, HTTP_METHOD requestMethod, void* method)
	{
		routes.push_back({ path, requestMethod, method });
	}

	// TODO: add more data
	void Service::callRoute(void* handler, Request request)
	{
		reinterpret_cast<void(*)(Request)>(handler)(request);
	}

	void Service::start(int port)
	{
		printf("started on port %i\n", port);

		// open socket and start polling, check if certain paths are equal to any of our existing routes
		// if path is equal, generate the data needed, and call the route.

		for (auto endpoint : routes)
		{
			callRoute(endpoint.handler, { "GET", "IDK" });
		}
	}

	void test()
	{
		printf("test\n");
	}
} 