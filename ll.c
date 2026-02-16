#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"

// ฟังก์ชันสำหรับแทรกโหนด (Insert)
void insert(LLPtr *sPtr, int id, char name[]) {
    LLPtr newPtr = malloc(sizeof(LL));

    if (newPtr != NULL) {
        newPtr->id = id;
        strcpy(newPtr->name, name);
        newPtr->nextPtr = NULL;
        newPtr->pPtr = NULL;

        LLPtr previousPtr = NULL;
        LLPtr currentPtr = *sPtr;

        // วนลูปหาตำแหน่งที่จะแทรก (เรียงตาม ID)
        while (currentPtr != NULL && id > currentPtr->id) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if (previousPtr == NULL) { // แทรกที่หัว list
            newPtr->nextPtr = *sPtr;
            if (*sPtr != NULL) (*sPtr)->pPtr = newPtr;
            *sPtr = newPtr;
        } else { // แทรกระหว่างกลางหรือท้าย
            previousPtr->nextPtr = newPtr;
            newPtr->pPtr = previousPtr;
            newPtr->nextPtr = currentPtr;
            if (currentPtr != NULL) currentPtr->pPtr = newPtr;
        }
    } else {
        printf("%d not inserted. No memory available.\n", id);
    }
}

// ฟังก์ชันสำหรับลบโหนด (Delete) - จุดที่มีปัญหาใน Log ของคุณ
void deletes(LLPtr *sPtr, int id) {
    LLPtr currentPtr = *sPtr;

    // วนลูปหาโหนดที่มี ID ตรงกับที่ระบุ
    while (currentPtr != NULL && currentPtr->id != id) {
        currentPtr = currentPtr->nextPtr;
    }

    if (currentPtr != NULL) {
        LLPtr tempPtr = currentPtr;

        if (currentPtr->pPtr == NULL) { // กรณีลบตัวแรก (Head)
            *sPtr = currentPtr->nextPtr;
            if (*sPtr != NULL) (*sPtr)->pPtr = NULL;
        } else { // กรณีลบตัวกลางหรือตัวท้าย
            // บรรทัดที่ 74 ที่เคย Error: เชื่อมตัวก่อนหน้าให้ข้ามตัวปัจจุบันไปหาตัวถัดไป
            currentPtr->pPtr->nextPtr = currentPtr->nextPtr;
            
            // ถ้ามีตัวถัดไป ให้ตัวถัดไปชี้กลับมาที่ตัวก่อนหน้า
            if (currentPtr->nextPtr != NULL) {
                currentPtr->nextPtr->pPtr = currentPtr->pPtr;
            }
        }
        free(tempPtr);
        printf("ID %d deleted.\n", id);
    } else {
        printf("ID %d not found.\n", id);
    }
} // ปิดปีกกาฟังก์ชันให้ครบ

// ฟังก์ชันพิมพ์ List (จากหน้าไปหลัง)
void printList(LLPtr currentPtr) {
    if (currentPtr == NULL) {
        puts("List is empty.\n");
    } else {
        while (currentPtr != NULL) {
            printf("%d %s -->", currentPtr->id, currentPtr->name);
            currentPtr = currentPtr->nextPtr;
        }
        puts("NULL\n");
    }
}

// ฟังก์ชันพิมพ์ List ย้อนกลับ (Reverse) - ถ้าโจทย์ต้องการ
void printListReverse(LLPtr currentPtr) {
    if (currentPtr == NULL) {
        puts("List is empty.\n");
    } else {
        // วนไปจนสุดท้ายก่อน
        while (currentPtr->nextPtr != NULL) {
            currentPtr = currentPtr->nextPtr;
        }
        // วนกลับโดยใช้ pPtr
        while (currentPtr != NULL) {
            printf("%d %s -->", currentPtr->id, currentPtr->name);
            currentPtr = currentPtr->pPtr;
        }
        puts("NULL\n");
    }
}