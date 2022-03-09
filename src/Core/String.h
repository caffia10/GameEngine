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

inline String operator""_s(char const* str, u64 size)
{
    return String(str, size);
}

inline bool operator==(String const& string, String const& other) 
{ 
    return std::strcmp(string.characters, other.characters) == 0;
}

inline char operator*(String const& string)
{
    return *string.characters;
}

inline char operator*(String& string)
{
    return *string.characters;
}

inline char const* operator++(String& string)
{
    return ++string.characters;
}

inline char const* operator++(String& string, int)
{
    return string.characters++;
}


inline char const* operator--(String& string)
{
    return string.characters--;
}

inline char const* operator--(String& string, int)
{
    return --string.characters;
}


inline String* operator+(String const& stringA, String const& stringB)
{
    u64 const size = stringA.charCount + stringB.charCount + 1;
    char* aux = (char*)malloc(size);
    memcpy(aux, stringA.characters, stringA.charCount);
    memcpy(aux + stringA.charCount, stringB.characters, stringB.charCount);
    aux[size] = 0;
    return new String(aux, size, 0);
}

inline char const* operator+(String const& stringA, char const* stringB)
{
    u64 const sizeStrB = strlen(stringB);
    u64 const size = stringA.charCount + sizeStrB + 1;
    char* aux = (char*)malloc(size);
    memcpy(aux, stringA.characters, stringA.charCount);
    memcpy(aux + stringA.charCount, stringB, sizeStrB);
    aux[size] = 0;

    return aux;
}

inline void ResetCharPosition(String& string)
{
    string.characters = string.characters - string.charCount;
}

inline bool IsEmpty(String* string) 
{
    return string->charCount == 0;
}

inline bool IsEmpty(String& string)
{
    return string.charCount == 0;
}

inline bool IsEmpty(String const& string)
{
    return string.charCount == 0;
}

inline String* ConvertToString(char const* characters)
{
    u64 const size = strlen(characters);
    return new String(characters, size);
}

inline char const* GetLastCharacter(String& string)
{
    return string.characters + string.charCount;
}

void Concat(String& dest, String& src);

bool Contains(String const& string, char const* wordToFind);

inline String const& GetConstStrRef(String const* string)
{
    return (*string);
}

inline String& GetStrRef(String * string)
{
    return (*string);
}

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

inline String* MakeString(StringBuilder& stringBuilder)
{
    return new String(stringBuilder.buffer, stringBuilder.charCount);
}

inline void RestartStringBuilder(StringBuilder& stringBuilder)
{
    if (stringBuilder.charCount == 0)
    {
        return;
    }

    stringBuilder.buffer = (char*)malloc(stringBuilder.size);
    MZeroMemory(stringBuilder.buffer, stringBuilder.size);
    stringBuilder.charCount = 0;
}

#endif // STRING_H