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
Entry<T>* HashPair(String const* key, T const& value);

template<typename T>
void HashTableSet(HashTable<T>* hashTable, String const* key, T const* value);

template<typename T>
T* GetValue(HashTable<T>* HashTable, String const* key);

#endif // HASH_TABLE_H