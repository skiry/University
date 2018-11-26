#pragma once

typedef struct _HTNODE {
    struct _HTNODE* PNext;
    struct _HTNODE* PBack;
    char* Key;
    int Value;
} HTNODE, *PHTNODE;

typedef struct _CC_HASH_TABLE {
    PHTNODE* Elems;
    int Size;
} CC_HASH_TABLE; 
  
int HtCreate(CC_HASH_TABLE** HashTable); 
int HtDestroy(CC_HASH_TABLE** HashTable); 
 
int HtSetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int Value); //add pair <key,value>
int HtGetKeyValue(CC_HASH_TABLE* HashTable, char* Key, int *Value); //get value from pair <key,value>
int HtRemoveKey(CC_HASH_TABLE* HashTable, char* Key); //delete <key,value>
int HtHasKey(CC_HASH_TABLE* HashTable, char* Key);  //return 1 if key in hash table, 0 otherwise
int HtGetNthKey(CC_HASH_TABLE* HashTable, int Index, char** Key); 
int HtClear(CC_HASH_TABLE* HashTable); 
int HtGetKeyCount(CC_HASH_TABLE* HashTable);  
int HtHash(unsigned char* Key); //computes the location in the hash table for a string
                                //cast to unsigned; ensure that every character is >= 0