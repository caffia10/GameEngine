#ifndef STRING_B
#define STRING_B

#include "malloc.h"
#include "String.h"


// -------------------- StringConst ---------------------------

inline StringConst operator""_sc(char const* str, u64 size)
{
    return { str, size };
}

inline char operator*(StringConst& string)
{
    return *string.characters;
}

inline void operator++(StringConst& string)
{
    ++string.characters;
}

inline void operator++(StringConst& string, int)
{
    string.characters++;
}

inline void operator--(StringConst& string)
{
    string.characters--;
}

inline void operator--(StringConst& string, int)
{
    --string.characters;
}

inline bool IsEmpty(StringConst& string)
{
    return string.size == 0;
}

inline String operator""_s(char const* str, u64 size)
{
    char* copy;
    strcpy(copy, str);
    return { copy, size, size };
}

inline StringConst ConvertToStringConst(char const* characters, u64 const size)
{
    return { characters, size };
}

StringConst ConvertToStringConst(char const* characters)
{
    u64 const size = strlen(characters);
    return ConvertToStringConst(characters, size);
}

// -------------------- String ---------------------------

inline char operator*(String& string)
{
    return *string.characters;
}

inline char* operator++(String& string)
{
     return ++string.characters;
}

inline char* operator++(String& string, int)
{
     return string.characters++;
}

inline void operator--(String& string)
{
    --string.characters;
}

inline void operator--(String& string, int)
{
    string.characters--;
}

inline u64 GetStrFreeSpace(String str)
{
    return str.size - str.charCount;
}

String ConvertToString(char* characters)
{
    u64 charCount = 0;
    char * originalPos = characters;
    while (*characters)
    {
        characters++;
        charCount++;
    }

    return String(originalPos, charCount, charCount);
}

inline String ConvertToString(char const* characters, u64 const& size)
{
    char* copy = (char*) malloc(size);
    strcpy(copy, characters);
    return ConvertToString(copy);
}

String ConvertToString(char const* characters)
{
    u64 const size = strlen(characters);
    return ConvertToString(characters, size);
}

inline StringConst ToConst(String& string)
{
    return { string.characters, string.charCount };
}

void CheckIfNeedMoreSpace(String& string, u64 const& newSpaceToAlloc)
{
    u64 const freeSpace = GetStrFreeSpace(string);
    if (freeSpace < newSpaceToAlloc)
    {
        // We add the missing space
        u64 const spaceNeeded = string.size * 2;
        realloc(&string.characters, spaceNeeded);
        string.characters[spaceNeeded - 1] = NULL;
    }
}

inline void ConcatUnsafe(String& dest, String& src)
{
    char* charptr = &dest.characters[dest.charCount - 1];
    while (*charptr++ = *src.characters++)
    {
        dest.charCount++;
    }
}

void Concat(String& dest, String& src)
{
    CheckIfNeedMoreSpace(dest, src.charCount);
    ConcatUnsafe(dest, src);
}

inline void AppendUnsafe(String& string, char const character)
{
    string.characters[string.charCount - 1] = character;
    string.charCount++;
}

void Append(String& string, char const character)
{
    const u8 minimumSpace = 2;
    CheckIfNeedMoreSpace(string, minimumSpace);
    AppendUnsafe(string, character);
}

inline char const* c_str(String& string)
{
    char const* characters = string.characters;
    return characters;
}

inline char const* c_str(String const& string)
{
    char const* characters = string.characters;
    return characters;
}

inline bool IsEmpty(String& string)
{
    return string.charCount == 0;
}

inline bool IsEmpty(String const& string)
{
    return string.charCount == 0;
}


#endif // STRING_B