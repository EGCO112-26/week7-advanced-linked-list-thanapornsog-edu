// ไฟล์: ll.c (Doubly Linked List Version)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. ปรับ Struct ให้เป็น Doubly Linked List
struct Node {
    int id;
    char name[50];
    struct Node *nextPtr; // ชี้ไปตัวถัดไป
    struct Node *pPtr;    // ชี้ไปตัวก่อนหน้า (Previous Pointer)
};

typedef struct Node LLnode;
typedef LLnode *LLPtr;

// แสดงคำสั่ง (เหมือนเดิม)
void instructions( void )
{
    puts( "Enter your choice:\n"
          "   1 to insert an element into the list.\n"
          "   2 to delete an element from the list.\n"
          "   3 to end." );
}

// 2. แก้ insert ให้รองรับ Doubly Linked List และเรียงตาม ID
void insert( LLPtr *sPtr, int id, char *name )
{
    LLPtr newPtr;       // โหนดใหม่
    LLPtr previousPtr;  // ตัวก่อนหน้า
    LLPtr currentPtr;   // ตัวปัจจุบัน

    newPtr = (LLPtr) malloc( sizeof( LLnode ) );

    if ( newPtr != NULL ) {
        newPtr->id = id;
        strcpy( newPtr->name, name );
        
        newPtr->nextPtr = NULL;
        newPtr->pPtr = NULL; // เริ่มต้น set เป็น NULL ไว้ก่อน

        previousPtr = NULL;
        currentPtr = *sPtr;

        // วนลูปหาตำแหน่งที่จะแทรก (เรียงน้อย -> มาก)
        while ( currentPtr != NULL && id > currentPtr->id ) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        // --- Logic การเชื่อมต่อสายของ Doubly Linked List ---
        
        // 1. เชื่อม newPtr กับ currentPtr (ด้านขวาของโหนดใหม่)
        newPtr->nextPtr = currentPtr;
        if ( currentPtr != NULL ) {
            currentPtr->pPtr = newPtr; // ให้ตัวถัดไปชี้กลับมาหาตัวใหม่
        }

        // 2. เชื่อม newPtr กับ previousPtr (ด้านซ้ายของโหนดใหม่)
        newPtr->pPtr = previousPtr;
        if ( previousPtr == NULL ) {
            *sPtr = newPtr; // ถ้าไม่มีตัวก่อนหน้า แสดงว่าเป็นหัวแถวใหม่
        } else {
            previousPtr->nextPtr = newPtr; // ให้ตัวก่อนหน้าชี้มาหาตัวใหม่
        }
        // ------------------------------------------------
    } else {
        printf( "%d not inserted. No memory available.\n", id );
    }
}

// 3. แก้ delete ให้ตัดสายทั้งไปและกลับ
int deletes( LLPtr *sPtr, int id )
{
    LLPtr currentPtr; // โหนดที่จะลบ

    // ถ้าลิสต์ว่าง
    if ( *sPtr == NULL ) return 0;

    // กรณีลบตัวแรก (Head)
    if ( id == ( *sPtr )->id ) {
        currentPtr = *sPtr;
        *sPtr = ( *sPtr )->nextPtr; // ย้ายหัวไปตัวถัดไป

        // ถ้ายังมีโหนดเหลืออยู่ ต้องตัด pPtr ของหัวใหม่ให้เป็น NULL
        if ( *sPtr != NULL ) {
            ( *sPtr )->pPtr = NULL;
        }

        free( currentPtr );
        return id;
    } 
    else {
        // กรณีลบตัวกลางหรือท้าย
        currentPtr = *sPtr;

        // วนหาตัวที่จะลบ
        while ( currentPtr != NULL && currentPtr->id != id ) {
            currentPtr = currentPtr->nextPtr;
        }

        // ถ้าเจอตัวที่จะลบ
        if ( currentPtr != NULL ) {
            
            // เชื่อมตัวก่อนหน้า ข้ามไปหาตัวถัดไป
            if ( currentPtr->pPtr != NULL ) {
                currentPtr->pPtr->nextPtr = currentPtr->nextPtr;
            }

            // เชื่อมตัวถัดไป ย้อนกลับไปหาตัวก่อนหน้า (ถ้ามีตัวถัดไป)
            if ( currentPtr->nextPtr != NULL ) {
                currentPtr->nextPtr->pPtr = currentPtr->pPtr;
            }

            free( currentPtr );
            return id;
        }
    }

    return 0; // หาไม่เจอ
}

int isEmpty( LLPtr sPtr )
{
    return sPtr == NULL;
}

// ปริ้นขาไป (Forward)
void printList( LLPtr currentPtr )
{
    if ( isEmpty( currentPtr ) ) {
        puts( "List is empty." );
    } else {
        puts( "The list is (Forward):" );
        while ( currentPtr != NULL ) {
            printf( "%d %s --> ", currentPtr->id, currentPtr->name );
            currentPtr = currentPtr->nextPtr;
        }
        puts( "NULL" );
    }
}

// ปริ้นขากลับ (Backward) โดยใช้ pPtr
// วิธีนี้ดีกว่า recursive เพราะพิสูจน์ว่า Doubly Link เชื่อมกันจริง
void printListReverse( LLPtr currentPtr )
{
    if ( isEmpty( currentPtr ) ) {
        return;
    }

    // 1. วิ่งไปให้สุดสายก่อน
    while ( currentPtr->nextPtr != NULL ) {
        currentPtr = currentPtr->nextPtr;
    }

    // 2. วิ่งย้อนกลับด้วย pPtr
    puts( "The list is (Backward):" );
    while ( currentPtr != NULL ) {
        printf( "%d %s --> ", currentPtr->id, currentPtr->name );
        currentPtr = currentPtr->pPtr; // ถอยหลัง
    }
    puts( "NULL" );
}

// เคลียร์โหนดทั้งหมด (ใช้เมื่อกด 3 หรือจบโปรแกรม)
void clearList( LLPtr *sPtr )
{
    LLPtr currentPtr = *sPtr;
    LLPtr tempPtr;

    while ( currentPtr != NULL ) {
        tempPtr = currentPtr;
        printf( "delete %d\n", tempPtr->id ); 
        currentPtr = currentPtr->nextPtr;
        free( tempPtr );
    }
    *sPtr = NULL;
}