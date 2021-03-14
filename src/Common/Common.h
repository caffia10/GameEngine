#ifndef COMMON_H
#define COMMON_H

#if defined(WIN32) || defined(_WIN32)
#define TARGET_WINDOWS 1
#else
#define TARGET_WINDOWS 0
#endif

#include <stdio.h>
#include <stdarg.h>
#include <vector>

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


typedef std::vector<char*> Chars;
typedef std::vector<char const*> CharsConst;
typedef Chars::iterator CharsIterator;
typedef CharsConst::iterator CharsConstIterator;

#endif // COMMON_H