#include "ccvector.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>

int VecCreate(CC_VECTOR **Vector)
{
    if (Vector == NULL) {
        return -1;
    }

    *Vector = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));

    if (*Vector == NULL) {
        return -1;
    }

    (*Vector)->Head = NULL;
    (*Vector)->Tail = NULL;
    (*Vector)->Size = 0;

    return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
    if (Vector == NULL || *Vector == NULL) {
        return -1;
    }
    //delete all the elements of the vector first to free all the alloted memory
    VecClear(*Vector);

    free(*Vector);
    *Vector = NULL;

    return 0;
}

int VecInsertTail(CC_VECTOR *Vector, int Value)
{
    if (Vector == NULL) {
        return -1;
    }

    PNODE toInsert = (PNODE)malloc(sizeof(NODE));

    if (toInsert == NULL) {
        return -1;
    }

    toInsert->PBack = NULL;
    toInsert->PNext = NULL;
    toInsert->Value = Value;

    if (Vector->Tail == NULL) {
        Vector->Head = toInsert;
        Vector->Tail = toInsert;
    }
    else {
        toInsert->PBack = Vector->Tail;
        (Vector->Tail)->PNext = toInsert;
        Vector->Tail = toInsert;
    }

    ++Vector->Size;

    return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{
    if (Vector == NULL) {
        return -1;
    }

    PNODE toInsert = (PNODE)malloc(sizeof(NODE));

    if (toInsert == NULL) {
        return -1;
    }

    toInsert->PBack = NULL;
    toInsert->PNext = NULL;
    toInsert->Value = Value;

    if (Vector->Head == NULL) {
        Vector->Head = toInsert;
        Vector->Tail = toInsert;
    }
    else {
        toInsert->PNext = Vector->Head;
        (Vector->Head)->PBack = toInsert;
        Vector->Head = toInsert;
    }

    ++Vector->Size;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{
    if (Vector == NULL || Index >= Vector->Size) {
        return -1;
    }

    if (Index == Vector->Size - 1) {
        VecInsertTail(Vector, Value);
    }
    //if we want to insert on the last position, update the tail as well

    PNODE toInsert = (PNODE)malloc(sizeof(NODE));

    if (toInsert == NULL) {
        return -1;
    }

    toInsert->PBack = NULL;
    toInsert->PNext = NULL;
    toInsert->Value = Value;

    PNODE aux = Vector->Head;
    //the head is not null because it would have hailed in the first if, the second statement
    for (int i = 0; i < Index; ++i) {
        aux = aux->PNext;
    }

    toInsert->PNext = aux->PNext;
    toInsert->PBack = aux;
    aux->PNext = toInsert;
    (toInsert->PNext)->PBack = toInsert;

    ++Vector->Size;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
    if (Vector == NULL || Index >= Vector->Size) {
        return -1;
    }

    PNODE toDelete = Vector->Head;
    //this element is not null because it passed 
    //the first if statement, we surely have at least 1 element

    for (int i = 0; i < Index; ++i) {
        toDelete = toDelete->PNext;
    }

    if (Index == 0) {
        if (Vector->Size == 1) {
            Vector->Head = NULL;
            Vector->Tail = NULL;
        }
        else {
            Vector->Head = (Vector->Head)->PNext;
            (Vector->Head)->PBack = NULL;
        }
    }

    else if (Index == Vector->Size - 1) {
        Vector->Tail = (Vector->Tail)->PBack;
        (Vector->Tail)->PNext = NULL;
    }
    else {
        (toDelete->PBack)->PNext = toDelete->PNext;
        (toDelete->PNext)->PBack = toDelete->PBack;
    }

    free(toDelete);
    --Vector->Size;

    return 0;
}

int VecGetValueByIndex(CC_VECTOR *Vector, int Index, int *Value)
{
    if (Vector == NULL || Index >= Vector->Size) {
        return -1;
    }

    PNODE toGet = Vector->Head;
    for (int i = 0; i < Index; ++i) {
        toGet = toGet->PNext;
    }

    *Value = toGet->Value;

    return 0;
}

int VecGetCount(CC_VECTOR *Vector)
{
    if (Vector == NULL) {
        return -1;
    }

    return Vector->Size;
}

int VecClear(CC_VECTOR *Vector)
{
    if (Vector == NULL) {
        return -1;
    }

    if (Vector->Head == NULL) {
        return 0;
    }

    PNODE aux = Vector->Head, aux2;

    while (aux->PNext) {
        aux2 = aux;
        aux = aux->PNext;
        free(aux2);
    }

    free(aux);
    Vector->Head = NULL;
    Vector->Tail = NULL;
    Vector->Size = 0;

    return 0;
}

int VecSort(CC_VECTOR *Vector)
{
    if (Vector == NULL) {
        return -1;
    }
    if (Vector->Size == 0 || Vector->Size == 1) {
        return 0;
    }
    
    PNODE first, second;
    int pos;
    int value;
    int counter;

    for (int i = 0; i < Vector->Size - 1; ++i) {
        first = Vector->Head;
        for (int j = 0; j < i; ++j) {
            first = first->PNext;
        }

        second = first;
        pos = counter = i;

        while (second->PNext) {
            second = second->PNext;
            ++counter;
            if (first->Value > second->Value) {
                pos = counter;
            }
        }

        if (pos != i) {
            second = first;
            for (int j = 0; j < pos - i; ++j) {
                second = second->PNext;
            }

            value = first->Value;
            first->Value = second->Value;
            second->Value = value;
        }
    }

    return 0;
}
