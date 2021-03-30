#ifndef STRING_H
#define STRING_H

#include "Common.h"
#include "Maths/MathDef.h"

#define STRING_MAX_SIZE_RECOMMENDED 1000000u

struct StringConst
{
    char const* characters;
    u64 size;

    StringConst(char const* characters, u64 size)
    {
        this->size = size;
        this->characters = characters;
    }
};

struct String
{
    char* characters;
    u64 size;
    u64 charCount = 0;

    String(char* characters, u64 size, u64 charCount)
    {
        this->size = size;
        this->characters = characters;
        this->charCount = charCount;
    }

    String(u64 size)
    {
        this->size = size;
        characters = (char*) malloc(size);
        MZeroMemory(characters, size);
    }
};

typedef std::vector<String> Strings;

#endif // STRING_H