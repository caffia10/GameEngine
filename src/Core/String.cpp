#include "String.h"

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