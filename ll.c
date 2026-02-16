#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

// ฟังก์ชันตรวจสอบว่า List ว่างหรือไม่
int isEmpty(LLPtr sPtr) {
    return sPtr == NULL;
}

// ฟังก์ชันแสดงเมนูคำแนะนำ
void instructions(void) {
    printf("Enter your choice:\n"
           "   1 to insert an element into the list.\n"
           "   2 to delete an element from the list.\n"
           "   3 to end.\n");
}

// ฟังก์ชันแทรกโหนด (เรียงตาม ID)
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

        if (previousPtr == NULL) { // แทรกที่หัว
            newPtr->nextPtr = *sPtr;
            if (*sPtr != NULL) (*sPtr)->pPtr = newPtr;
            *sPtr = newPtr;
        } else { // แทรกกลางหรือท้าย
            previousPtr->nextPtr = newPtr;
            newPtr->pPtr = previousPtr;
            newPtr->nextPtr = currentPtr;
            if (currentPtr != NULL) currentPtr->pPtr = newPtr;
        }
    }
}

// ฟังก์ชันลบโหนด
void deletes(LLPtr *sPtr, int id) {
    LLPtr currentPtr = *sPtr;
    while (currentPtr != NULL && currentPtr->id != id) {
        currentPtr = currentPtr->nextPtr;
    }
    
    if (currentPtr != NULL) {
        LLPtr tempPtr = currentPtr;
        if (currentPtr->pPtr == NULL) { // ลบหัว
            *sPtr = currentPtr->nextPtr;
            if (*sPtr != NULL) (*sPtr)->pPtr = NULL;
        } else { // ลบกลางหรือท้าย
            currentPtr->pPtr->nextPtr = currentPtr->nextPtr;
            if (currentPtr->nextPtr != NULL) {
                currentPtr->nextPtr->pPtr = currentPtr->pPtr;
            }
        }
        free(tempPtr);
        printf("ID %d deleted.\n", id);
    } else {
        printf("ID %d not found.\n", id);
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

// ฟังก์ชันเคลียร์หน่วยความจำก่อนจบโปรแกรม
void clearList(LLPtr *sPtr) {
    LLPtr currentPtr = *sPtr;
    LLPtr tempPtr;
    while (currentPtr != NULL) {
        tempPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
        free(tempPtr);
    }
    *sPtr = NULL;
}