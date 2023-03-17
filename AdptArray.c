#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"



struct AdptArray_ {
    PElement* data;
    int size;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
};

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc) {
    PAdptArray array = (PAdptArray) malloc(sizeof(struct AdptArray_));
    array->data = (PElement*) realloc(0, sizeof(PElement));
    array->size = 0;
    array->copyFunc = copyFunc;
    array->delFunc = delFunc;
    array->printFunc = printFunc;
    return array;
}

void DeleteAdptArray(PAdptArray array) {
    if (array == NULL) return ;

    for (int i = 0; i < array->size; i++) {
        if (array->data[i] != NULL) {
            array->delFunc(array->data[i]);
        }
    }

    free(array->data);
    free(array);
}

Result SetAdptArrayAt(PAdptArray array, int index, PElement element) {
    if (array == NULL || index < 0) {
        return FAIL;
    }

    if (index >= array->size) {
        int newSize = index +1;
        PElement* newData = (PElement*) realloc(array->data, newSize * sizeof(PElement));
        if (newData == NULL) {
            return FAIL;
        }
        array->data = newData;
        for (int i = array->size; i < newSize; i++) {
            array->data[i] = NULL;
        }
        array->size = newSize;
    }

    if (array->data[index] != NULL) {
        array->delFunc(array->data[index]);
    }

    array->data[index] = array->copyFunc(element);

    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray array, int index) {
    if (array == NULL || index < 0 || index >= array->size) {
        return NULL;
    }
    if (array->data[index]==NULL)
    {
        return NULL;
    }
    
    return array->copyFunc(array->data[index]);

   
}

int GetAdptArraySize(PAdptArray array) {
    if (array == NULL) {
        return 0;
    }

    return array->size;
}

void PrintDB(PAdptArray array) {
    if (array == NULL) {
        return;
    }

    for (int i = 0; i < array->size; i++) {
        if (array->data[i] != NULL) {
            array->printFunc(array->data[i]);
        }
    }
}
