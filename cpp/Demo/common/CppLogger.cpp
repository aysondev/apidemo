#include <iostream>
#include "CppLogger.h"

CppLogger::CppLogger()
{
}

CppLogger::~CppLogger() {}


void CppLogger::error(const std::string& msg)
{
	std::cout << msg.c_str() << std::endl;
}

void CppLogger::server(const std::string& msg)
{
	std::cout << msg.c_str() << std::endl;
}
