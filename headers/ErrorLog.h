#pragma once
#include <string>
inline void LogError(std::string err)
{
	fprintf(stderr, err.c_str());
	printf_s("\n");
	system("pause");
}