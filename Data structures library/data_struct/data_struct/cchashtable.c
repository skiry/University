#include "cchashtable.h"
#include "common.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define HASHSIZE 593//428801

int HtCreate(CC_HASH_TABLE** HashTable)
{
    if (HashTable == NULL) {
        return -1;
    }

    *HashTable = (CC_HASH_TABLE*)malloc(sizeof(CC_HASH_TABLE));

    if (*HashTable == NULL) {
        return -1;
    }

    (*HashTable)->Elems = (PHTNODE*)malloc(HASHSIZE * sizeof(PHTNODE));

    if ((*HashTable)->Elems == NULL) {
        return -1;
    }

    for (int i = 0; i < HASHSIZE; ++i) {
        (*HashTable)->Elems[i] = NULL;
    }
    (*HashTable)->Size = 0;

    return 0;
}

int HtDestroy(CC_HASH_TABLE** HashTable)
{
    if (HashTable == NULL || *HashTable == NULL) {
        return -1;
    }

    HtClear(*HashTable);

    free((*HashTable)->Elems);
    free(*HashTable);
    *HashTable = NULL;

    return 0;
}

int HtHash(unsigned char* Key) {
    unsigned long hash = 0;
    int c;

    while (c = *Key++) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash % HASHSIZE;
}

int HtSetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int Value)
{
    if (HashTable == NULL) {
        return -1;
    }

    PHTNODE toAdd = (PHTNODE)malloc(sizeof(HTNODE));

    if (toAdd == NULL) {
        return -1;
    }

    toAdd->PNext = NULL;
    toAdd->PBack = NULL;
    toAdd->Value = Value;
    toAdd->Key = (char*)malloc(strlen(Key) * sizeof(char) + 1);

    if (toAdd->Key == NULL) {
        return -1;
    }

    strcpy_s(toAdd->Key, strlen(Key) + 1, Key);
    //strlen + 1 because of \0 at the end

    int hashValue = HtHash((unsigned char*)Key);
    PHTNODE aux = (HashTable->Elems)[hashValue];

    if (aux == NULL) {
        (HashTable->Elems)[hashValue] = toAdd;
    }
    else {
        if (aux->PNext) {
            (aux->PNext)->PBack = toAdd;
            toAdd->PNext = aux->PNext;
        }
        toAdd->PBack = aux;
        aux->PNext = toAdd;
    }

    ++HashTable->Size;

    return 0;
}

int HtGetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int *Value)
{
    if (HashTable == NULL || !HtHasKey(HashTable, Key)) {
        return -1;
    }

    PHTNODE toSearch = HashTable->Elems[HtHash((unsigned char*)Key)];
    while (toSearch && strcmp(toSearch->Key, Key)) {
        toSearch = toSearch->PNext;
    }

    if (toSearch == NULL) {
        return -1;
    }
    //just in case

    *Value = toSearch->Value;

    return 0;
}

int HtRemoveKey(CC_HASH_TABLE* HashTable, char* Key)
{
    if (HashTable == NULL || !HtHasKey(HashTable, Key)) {
        return -1;
    }

    int hashValue = HtHash((unsigned char*)Key);
    PHTNODE toRemove = HashTable->Elems[hashValue];

    while (toRemove && strcmp(toRemove->Key, Key)) {
        toRemove = toRemove->PNext;
    }

    if (toRemove->PBack == NULL) {
        HashTable->Elems[hashValue] = HashTable->Elems[hashValue]->PNext;
        if (toRemove->PNext) {
            HashTable->Elems[hashValue]->PBack = NULL;
        }
    }
    else {
        (toRemove->PBack)->PNext = toRemove->PNext;
        if (toRemove->PNext) {
            (toRemove->PNext)->PBack = toRemove->PBack;
        }
    }

    free(toRemove->Key);
    free(toRemove);
    --HashTable->Size;

    return 0;
}

int HtHasKey(CC_HASH_TABLE* HashTable, char* Key)
{
    if (HashTable == NULL) {
        return -1;
    }

    int found = 0;
    PHTNODE toSearch = HashTable->Elems[HtHash((unsigned char*)Key)];

    while (toSearch) {
        if (!strcmp(toSearch->Key, Key)) {
            ++found;
            break;
        }
        toSearch = toSearch->PNext;
    }

    return found == 1;
}

int HtGetNthKey(CC_HASH_TABLE* HashTable, int Index, char** Key)
{
    if (HashTable == NULL || Index >= HashTable->Size) {
        return -1;
    }

    PHTNODE iterator;
    int positionsIterated = 0, entriesIterated = 0, foundKey = 0;

    while (entriesIterated <= Index && !foundKey) {
        iterator = HashTable->Elems[positionsIterated++];
        while (iterator && !foundKey) {
            if (entriesIterated == Index) {
                strcpy_s(*Key, strlen(iterator->Key) + 1, iterator->Key);
                ++foundKey;
            }
            ++entriesIterated;
            iterator = iterator->PNext;
        }
    }

    return 0;
}

int HtClear(CC_HASH_TABLE* HashTable)
{
    if (HashTable == NULL) {
        return -1;
    }

    for (int i = 0; i < HASHSIZE, HashTable->Size > 0; ++i) {
        while (HashTable->Elems[i]) {
            HtRemoveKey(HashTable, HashTable->Elems[i]->Key);
        }
    }

    return 0;
}

int HtGetKeyCount(CC_HASH_TABLE* HashTable)
{
    if (HashTable == NULL) {
        return -1;
    }

    return HashTable->Size;
}
