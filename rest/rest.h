#pragma once

#include <iostream>
#include <winsock2.h>
#include <string>
#include <vector>

#include "data/http_method.h"

#pragma comment(lib, "ws2_32.lib")

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
			HTTP_METHOD method;
			void* handler;
		};

		std::vector<Route> routes;

		void callRoute(void* handler, Request request);
		void handleRequest(SOCKET clientSocket);
	};

	void test();
}

#endif