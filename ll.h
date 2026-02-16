#ifndef ll_h
#define ll_h

#define SIZE 50

struct Node {
    int id;                // ต้องใช้ชื่อ id ตามใน ll.c
    char name[SIZE];       // ต้องใช้ชื่อ name
    struct Node *nextPtr;
    struct Node *pPtr;     // ต้องใช้ชื่อ pPtr สำหรับ Doubly Linked List
};

typedef struct Node LLnode;
typedef LLnode *LLPtr;

// ฟังก์ชันต้นแบบ
void insert(LLPtr *sPtr, int id, char name[]);
void deletes(LLPtr *sPtr, int id);
void printList(LLPtr currentPtr);
void printListReverse(LLPtr currentPtr);

#endif