#include "HashTable.h"

template<typename T>
HashTable<T>* CreateHashTable()
{
    HashTable* hashTable = new HashTable();

    hashTable->entries = (Entry**) malloc(sizeof(Entry*)* HASH_TABLE_SIZE);

    for (u32 i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hashTable->entries[i] = NULL;
    }
    
    return hashTable;
}

u32 GetHash(String const* key)
{
    u32 value = 0;
    u32 index = 0;
    u8 const multiplier = 37;

    while (char const character =  *(*key))
    {
       value = (value * multiplier) + (character * ++index);
    }
    
    // make sure value is 0 <= value <= HASH_TABLE_SIZE
    value %= HASH_TABLE_SIZE;

    return value;
}

template<typename T>
void HashTableSet(HashTable<T>* hashTable, String const* key, T const* value)
{
    u32 const slot = GetHash(key);

    Entry* entry = hashTable->entries[slot];

    if (!entry)
    {
        hashTable->entries[slot] = HashPair(key, value);
        return;
    }

    Entry* prevEntry;

    while (entry)
    {
        if (entry->key == key)
        {
            // match found, replace value
            free(entry->value);
            u64 size =  sizeof(value);
            entry->value = malloc(size);
            memcpy(entry->value, value, size);
            return;
        }

        prevEntry = entry;
        entry = prevEntry->next;
    }
    
    // end of chain reached without a match add new
    prevEntry->next = HashPair(key, value);
}

template<typename T>
T* GetValue(HashTable<T>* hashTable, String const* key)
{
    u32 const slot = GetHash(key);

    Entry* entry = hashTable->entries[slot];

    while (entry)
    {
        if (entry->key == key)
        {
            return entry->value;
        }

        entry = entry->next;
    }
    
    return NULL;
}