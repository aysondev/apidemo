#pragma once

class CppLogger
{
public:

	CppLogger();
	~CppLogger();

	void error(const std::string& msg);
	void server(const std::string& msg);
};
extern CppLogger ExtLogger; // Global