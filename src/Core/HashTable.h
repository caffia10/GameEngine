#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include "String.h"
#include <stdlib.h>
#include <stdbool.h>

#define HASH_TABLE_SIZE 1000

template<typename T>
struct Entry
{
    String* key;
    T value;
    Entry* next = NULL;
};

template<typename T>
struct HashTable
{
    Entry<T>** entries;
};

template<typename T>
HashTable<T>* CreateHashTable();

u32 GetHash(String const* key);

template<typename T>
inline Entry<T>* HashPair(String* key, void* value)
{
    Entry* entry = new Entry();
    entry->key = key;
    entry->value = value;
    return entry;
}

template<typename T>
void HashTableSet(HashTable<T>* hashTable, String const* key, T const* value);

template<typename T>
T* GetValue(HashTable<T>* HashTable, String const* key);

#endif // HASH_TABLE_H