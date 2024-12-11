#pragma once

#include <iostream>
#include <winsock2.h>
#include <string>
#include <vector>
#pragma comment(lib, "ws2_32.lib")

#include "./data/enums.h"
#include "./data/request.h"
#include "./data/endpoint.h"

#ifndef REST_H
#define REST_H

namespace rest
{
	class Service
	{
	public:
		void start(int port);
		void registerEndpoint(const std::string& path, HTTP_METHOD method, Endpoint(*handler)(Request&));
	private:
		struct Route
		{
			std::string path;
			HTTP_METHOD method;
			Endpoint(*handler)(Request&);
		};

		std::vector<Route> routes;

		void callRoute(void* handler, Request& request, SOCKET currnetSocket);
		void handleRequest(SOCKET clientSocket);
	};
}

#endif