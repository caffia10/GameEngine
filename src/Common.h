#ifndef COMMON_H
#define COMMON_H

#if defined(WIN32) || defined(_WIN32)
#define TARGET_WINDOWS 1
#else
#define TARGET_WINDOWS 0
#endif

#include <stdio.h>
#include <stdarg.h>

#include <iostream>
#include <fstream>

#if !TARGET_WINDOWS
#include <assert.h>
#define MAX_PATH PATH_MAX
#endif


#if DEBUG_BUILD
#if TARGET_WINDOWS
#define ASSERT(expr) do { if (!(expr)) __debugbreak(); } while (false)
#define THROWDEBUGBREAK __debugbreak();
#else
#define ASSERT(expr) assert(expr)
#endif
#else
#define ASSERT(expr)
#define THROWDEBUGBREAK
#endif

#define NOMANGLE extern "C"

#define ArrayCount(array) (sizeof(array) / sizeof(array[0]))

// I hate this programming language
#undef near
#undef far

#define LOG(format, __ARGS__)
#define UI_LOG(format, ...)

std::string ReadFile(char const* fileName)
{
	std::string contents;
	std::FILE* fp = std::fopen(fileName, "rb");
	if (fp)
	{
		std::fseek(fp, 0, SEEK_END);
		contents.resize(std::ftell(fp));
		std::rewind(fp);
		std::fread(&contents[0], 1, contents.size(), fp);
		std::fclose(fp);
	}

	return(contents);
}


#endif // COMMON_H