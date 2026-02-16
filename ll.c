#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

// ฟังก์ชันสำหรับแทรกโหนด (Insert)
void insert(LLPtr *sPtr, int id, char name[]) {
    LLPtr newPtr = malloc(sizeof(LLnode));

    if (newPtr != NULL) {
        newPtr->id = id;
        strcpy(newPtr->name, name);
        newPtr->nextPtr = NULL;
        newPtr->pPtr = NULL;

        LLPtr previousPtr = NULL;
        LLPtr currentPtr = *sPtr;

        while (currentPtr != NULL && id > currentPtr->id) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if (previousPtr == NULL) { 
            newPtr->nextPtr = *sPtr;
            if (*sPtr != NULL) (*sPtr)->pPtr = newPtr;
            *sPtr = newPtr;
        } else { 
            previousPtr->nextPtr = newPtr;
            newPtr->pPtr = previousPtr;
            newPtr->nextPtr = currentPtr;
            if (currentPtr != NULL) currentPtr->pPtr = newPtr;
        }
    } else {
        printf("%d not inserted. No memory available.\n", id);
    }
}

// ฟังก์ชันสำหรับลบโหนด (Delete)
void deletes(LLPtr *sPtr, int id) {
    LLPtr currentPtr = *sPtr;

    while (currentPtr != NULL && currentPtr->id != id) {
        currentPtr = currentPtr->nextPtr;
    }

    if (currentPtr != NULL) {
        LLPtr tempPtr = currentPtr;

        if (currentPtr->pPtr == NULL) { 
            *sPtr = currentPtr->nextPtr;
            if (*sPtr != NULL) (*sPtr)->pPtr = NULL;
        } else { 
            currentPtr->pPtr->nextPtr = currentPtr->nextPtr;
            if (currentPtr->nextPtr != NULL) {
                currentPtr->nextPtr->pPtr = currentPtr->pPtr;
            }
        }
        free(tempPtr);
    } else {
        printf("%d not found.\n", id);
    }
}

// ฟังก์ชันพิมพ์ List (หน้าไปหลัง)
void printList(LLPtr currentPtr) {
    if (currentPtr == NULL) {
        printf("List is empty.\n");
    } else {
        while (currentPtr != NULL) {
            printf("%d %s -->", currentPtr->id, currentPtr->name);
            currentPtr = currentPtr->nextPtr;
        }
        printf("NULL\n");
    }
}

// ฟังก์ชันพิมพ์ List ย้อนกลับ (หลังมาหน้า)
void printListReverse(LLPtr currentPtr) {
    if (currentPtr == NULL) {
        printf("List is empty.\n");
    } else {
        while (currentPtr->nextPtr != NULL) {
            currentPtr = currentPtr->nextPtr;
        }
        while (currentPtr != NULL) {
            printf("%d %s -->", currentPtr->id, currentPtr->name);
            currentPtr = currentPtr->pPtr;
        }
        printf("NULL\n");
    }
}