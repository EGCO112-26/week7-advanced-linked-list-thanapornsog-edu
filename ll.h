#ifndef LL_H
#define LL_H

#define SIZE 50

// โครงสร้าง Node ของ Doubly Linked List
struct Node {
    int id;                // รหัส
    char name[SIZE];       // ชื่อ
    struct Node *nextPtr;  // ชี้ไปโหนดถัดไป
    struct Node *pPtr;     // ชี้ไปโหนดก่อนหน้า
};

typedef struct Node LLnode;
typedef LLnode *LLPtr;

// ฟังก์ชันต้นแบบทั้งหมดที่จำเป็น
void insert(LLPtr *sPtr, int id, char name[]);
void deletes(LLPtr *sPtr, int id);
void printList(LLPtr currentPtr);
void printListReverse(LLPtr currentPtr);
int isEmpty(LLPtr sPtr);
void instructions(void);
void clearList(LLPtr *sPtr);

#endif