#include "ccstack.h"
#include "common.h"
#include <stddef.h>
#include <stdlib.h>

int StCreate(CC_STACK **Stack)
{
    if (Stack == NULL) {
        return -1;
    }

    *Stack = (CC_STACK *)malloc(sizeof(CC_STACK));
    if (*Stack == NULL) {
        return -1;
    }

    (*Stack)->Size = 0;
    (*Stack)->Top = NULL;

    return 0;
}

int StDestroy(CC_STACK **Stack)
{
    if (Stack == NULL || *Stack == NULL) {
        return -1;
    }

    StClear(*Stack);

    free(*Stack);
    *Stack = NULL;

    return 0;
}

int StPush(CC_STACK *Stack, int Value)
{
    if (Stack == NULL) {
        return -1;
    }

    PSNODE toInsert = (PSNODE)malloc(sizeof(SNODE));

    if (toInsert == NULL) {
        return -1;
    }

    toInsert->Value = Value;
    toInsert->PNext = Stack->Top;

    Stack->Top = toInsert;
    ++Stack->Size;

    return 0;
}

int StPop(CC_STACK *Stack, int *Value)
{
    if (Stack == NULL || Stack->Size == 0) {
        return -1;
    }

    PSNODE toPop = Stack->Top;
    *Value = toPop->Value;
    Stack->Top = (Stack->Top)->PNext;
    --Stack->Size;
    free(toPop);
    
    return 0;    
}

int StPeek(CC_STACK *Stack, int *Value)
{
    if (Stack == NULL || Stack->Size == 0) {
        return -1;
    }

    *Value = Stack->Top->Value;

    return 0;
}

int StIsEmpty(CC_STACK *Stack)
{
    if (Stack == NULL) {
        return -1;
    }

    return Stack->Size == 0;
}

int StGetCount(CC_STACK *Stack)
{
    if (Stack == NULL) {
        return -1;
    }

    return Stack->Size;
}

int StClear(CC_STACK *Stack)
{
    if (Stack == NULL) {
        return -1;
    }

    if (Stack->Top == NULL) {
        return 0;
    }

    PSNODE aux = Stack->Top, aux2;

    while (aux->PNext) {
        aux2 = aux;
        aux = aux->PNext;
        free(aux2);
    }

    free(aux);
    Stack->Top = NULL;
    Stack->Size = 0;

    return 0;
}

int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
    if (Stack == NULL || StackToPush == NULL) {
        return -1;
    }

    if (StGetCount(StackToPush) == 0) {
        return 0;
    }
    //if the second stack is empty we won't make all the computations from below

    int value;
    CC_STACK* intermediary;
    StCreate(&intermediary);

    while (!StIsEmpty(StackToPush)) {
        StPop(StackToPush, &value);
        StPush(intermediary, value);
    }

    while (!StIsEmpty(intermediary) ) {
        StPop(intermediary, &value);
        StPush(Stack, value);
    }

    StDestroy(&intermediary);

    return 0;
}
