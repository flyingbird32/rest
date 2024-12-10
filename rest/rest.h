#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "data/http_method.h"

#ifndef REST_H
#define REST_H

namespace rest
{
	class Service
	{
	public:

		struct Request
		{
			std::string path;
			std::string data;
		};

		void start(int port);
		void registerEndpoint(const std::string& path, HTTP_METHOD requestMethod, void* method);


	private:
		struct Route
		{
			std::string path;
			HTTP_METHOD methods;
			void* handler;
		};

		std::vector<Route> routes;

		void callRoute(void* handler, Request request);
	};

	void test();
}

#endif