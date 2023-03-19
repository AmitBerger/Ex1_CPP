#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"



struct AdptArray_ {
    PElement* AnyData;
    int AdptArraySize;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
};

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc) {
    PAdptArray AdpArray = (PAdptArray) malloc(sizeof(struct AdptArray_));
    AdpArray->AnyData = (PElement*) calloc(0, sizeof(PElement));
    AdpArray->AdptArraySize = 0;
    AdpArray->copyFunc = copyFunc;
    AdpArray->delFunc = delFunc;
    AdpArray->printFunc = printFunc;
    return AdpArray;
}

void DeleteAdptArray(PAdptArray AdpArray) {
    if (AdpArray == NULL) return ;

    for (int i = 0; i < AdpArray->AdptArraySize; i++) {
        if (AdpArray->AnyData[i] != NULL) {
            AdpArray->delFunc(AdpArray->AnyData[i]);
        }
    }

    free(AdpArray->AnyData);
    free(AdpArray);
}

Result SetAdptArrayAt(PAdptArray AdpArray, int index, PElement element) {
    if (AdpArray == NULL || index < 0) {
        return FAIL;
    }

    if (index >= AdpArray->AdptArraySize) {
        int newSize = index +1;
        PElement* newData = (PElement*) realloc(AdpArray->AnyData, newSize * sizeof(PElement));
        if (newData == NULL) {
            return FAIL;
        }
        AdpArray->AnyData = newData;
        for (int i = AdpArray->AdptArraySize; i < newSize; i++) {
            AdpArray->AnyData[i] = NULL;
        }
        AdpArray->AdptArraySize = newSize;
    }

    if (AdpArray->AnyData[index] != NULL) {
        AdpArray->delFunc(AdpArray->AnyData[index]);
    }

    AdpArray->AnyData[index] = AdpArray->copyFunc(element);

    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray AdpArray, int index) {
    if (AdpArray == NULL || index < 0 || index >= AdpArray->AdptArraySize) {
        return NULL;
    }
    if (AdpArray->AnyData[index]==NULL)
    {
        return NULL;
    }
    
    return AdpArray->copyFunc(AdpArray->AnyData[index]);

   
}

int GetAdptArraySize(PAdptArray AdpArray) {
    if (!AdpArray) {
        return -1;
    }
    if (AdpArray == NULL) {
        return 0;
    }

    return AdpArray->AdptArraySize;
}

void PrintDB(PAdptArray AdpArray) {
    if (AdpArray == NULL) {
        return;
    }

    for (int i = 0; i < AdpArray->AdptArraySize; i++) {
        if (AdpArray->AnyData[i] != NULL) {
            AdpArray->printFunc(AdpArray->AnyData[i]);
        }
    }
}

