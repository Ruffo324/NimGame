//ConsoleHandler.cpp : Defines the exported functions for the DLL application

#include "stdafx.h"
#include "ConsoleHandler.h"
#include <stdexcept>

using namespace std;

namespace ConsoleHandler
{
	double ConsoleHandlerCore::Multiply(double a, double b)
	{
		return  a * b;
	}
}
