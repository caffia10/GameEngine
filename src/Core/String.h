#ifndef STRING_H
#define STRING_H

#include "Common.h"
#include "MathDef.h"
#include "malloc.h"

#define STRING_MAX_SIZE_RECOMMENDED 1000000u


struct String
{
    char const* characters;
    u64 size;
    u64 charCount;

    String(char const* characters, u64 size)
    {
        char* copy = (char*)malloc(size);
        memcpy(copy, characters, size);
        copy[size] = 0;
        this->size = size;
        this->characters = copy;
        this->charCount = size;
    }

    String(char const* characters, u64 size, u8)
    {
        this->size = size;
        this->characters = characters;
        this->charCount = size;
    }

    ~String()
    {
        delete characters;
    }
};

typedef std::vector<String*> Strings;

inline String operator""_s(char const* str, u64 size);

inline bool operator==(String const& string, String const& other) 
{ 
    return std::strcmp(string.characters, other.characters) == 0;
}

char operator*(String const& string);
char operator*(String& string);

char const* operator++(String& string);
char const* operator++(String& string, int);
char const* operator--(String& string);
char const* operator--(String& string, int);

String* operator+(String const& stringA, String const& stringB);
char const* operator+(String const& stringA, char const* characters);

void ResetCharPosition(String& string);

bool IsEmpty(String& string);

bool IsEmpty(String const& string);

String* ConvertToString(char const* characters);

char const* GetLastCharacter(String& string);

void Concat(String& dest, String& src);

bool Contains(String const& string, char const* wordToFind);

String const& GetConstStrRef(String const* string);

String& GetStrRef(String * string);

struct StringBuilder
{
    char* buffer;
    u64 size;
    u64 charCount;

    StringBuilder(u64 size)
    {
        this->size = size;
        buffer = (char*) malloc(size);
        MZeroMemory(buffer,size);
    }
};


void Append(StringBuilder& stringBuilder, char const character);

String* MakeString(StringBuilder& stringBuilder);

void RestartStringBuilder(StringBuilder& stringBuilder);

#endif // STRING_H