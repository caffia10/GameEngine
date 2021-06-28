#include "String.h"

extern String operator""_s(char const* str, u64 size)
{
    return String(str, size);
}

char operator*(String const& string)
{
    return *string.characters;
}

char operator*(String& string)
{
    return *string.characters;
}

char const* operator++(String& string)
{
    return ++string.characters;
}

char const* operator++(String& string, int)
{
    return string.characters++;
}

char const* operator--(String& string)
{
    return string.characters--;
}

char const* operator--(String& string, int)
{
    return --string.characters;
}

String* operator+(String const& stringA, String const& stringB)
{
    u64 const size = stringA.charCount + stringB.charCount + 1;
    char* aux = (char*)malloc(size);
    memcpy(aux, stringA.characters, stringA.charCount);
    memcpy(aux + stringA.charCount, stringB.characters, stringB.charCount);
    aux [size] = 0;
    return new String(aux, size, 0);
}

char const* operator+(String const& stringA, char const* stringB)
{
     u64 const sizeStrB = strlen(stringB);
    u64 const size = stringA.charCount + sizeStrB + 1;
    char* aux = (char*)malloc(size);
    memcpy(aux, stringA.characters, stringA.charCount);
    memcpy(aux + stringA.charCount, stringB, sizeStrB);
    aux [size] = 0;

    return aux;
}

void ResetCharPosition(String& string)
{
    string.characters = string.characters - string.charCount;
}

bool IsEmpty(String& string)
{
    return string.charCount == 0;
}

inline bool IsEmpty(String const& string)
{
    return string.charCount == 0;
}

String* ConvertToString(char const* characters)
{
    u64 const size = strlen(characters);
    return new String(characters, size);
}

inline char const* GetLastCharacter(String& string)
{
    return string.characters + string.charCount;
}

void Concat(String& dest, String& src)
{
    u64 const size = dest.charCount + src.charCount + 1;
    char* aux = (char*)malloc(size);
    memcpy(aux, dest.characters, dest.charCount);
    memcpy(aux + dest.charCount, src.characters, src.charCount);

    delete dest.characters;

    dest.characters = aux;
}

bool Contains(String const& string, char const* wordToFind)
{
    char const* wordToFindCurrentChar = wordToFind;

    bool contains = false;
    for (u64 i = 0; i < string.charCount; i++)
    {
        if (!*wordToFindCurrentChar)
        {
            contains = true;
        }

        if (*wordToFindCurrentChar == string.characters[i])
        {
            wordToFindCurrentChar++;
        }
        else
        {
            // reset position
            wordToFindCurrentChar = wordToFind;
        }
    }

    return contains;
}

String const& GetConstStrRef(String const* string)
{
    return (*string);
}

String& GetStrRef(String* string)
{
    return (*string);
}

// ------------- String Builder

void Append(StringBuilder& stringBuilder, char const character)
{
    u64 const freeSpace = stringBuilder.size - stringBuilder.charCount;

    if (freeSpace == 0)
    {
        // We add the missing space
        u64 const spaceNeeded = stringBuilder.size * 2;
        realloc(&stringBuilder.buffer, spaceNeeded);
        char const* characters = stringBuilder.buffer;

        for (u64 i = stringBuilder.charCount; i < stringBuilder.size; i++)
        {
            characters++;
            characters = 0;
        }
    }

    stringBuilder.buffer[stringBuilder.charCount] = character;
    stringBuilder.charCount++;
}

String* MakeString(StringBuilder& stringBuilder)
{
    return new String(stringBuilder.buffer, stringBuilder.charCount);
}

void RestartStringBuilder(StringBuilder& stringBuilder)
{
    if (stringBuilder.charCount == 0)
    {
        return;
    }

    stringBuilder.buffer = (char*)malloc(stringBuilder.size);
    MZeroMemory(stringBuilder.buffer, stringBuilder.size);
    stringBuilder.charCount = 0;
}