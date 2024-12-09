#pragma once
#include <iostream>
#include "rest.h"

namespace rest
{
	void Network::test(int x, int y)
	{
		int response = x + y;
		printf("repsonse is %i\n", response);
	}

	void test()
	{
		printf("test\n");
	}
}