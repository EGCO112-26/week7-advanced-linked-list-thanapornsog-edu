// ไฟล์: ll_example.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ต้องประกาศ Struct ให้เหมือนกับใน ll.c (หรือถ้ามีไฟล์ .h ให้แก้ในนั้น)
struct Node {
    int id;
    char name[50]; 
    struct Node *nextPtr;
};
typedef struct Node LLnode;
typedef LLnode *LLPtr;

// Prototypes
void insert( LLPtr *sPtr, int id, char *name );
int deletes( LLPtr *sPtr, int id );
int isEmpty( LLPtr sPtr );
void printList( LLPtr currentPtr );
void printListReverse( LLPtr currentPtr );
void instructions( void );
void clearList( LLPtr *sPtr );

int main( void )
{
    LLPtr startPtr = NULL; 
    unsigned int choice;
    int id;
    char name[50]; // ตัวแปรเก็บชื่อ

    instructions();
    printf( "? " );
    scanf( "%u", &choice );

    while ( choice != 3 ) {
        switch ( choice ) {
            case 1:
                printf( "Enter id and name: " ); // ข้อความตามรูป
                scanf( "%d %s", &id, name ); // รับค่า id และ name
                insert( &startPtr, id, name );
                
                // ปริ้น 2 บรรทัดตามรูป
                printList( startPtr );        // บรรทัดแรก (ปกติ)
                printListReverse( startPtr ); // บรรทัดสอง (ย้อนหลัง)
                puts( "NULL" );               // ปิดท้ายบรรทัดย้อนหลัง
                break;

            case 2:
                if ( !isEmpty( startPtr ) ) {
                    printf( "Enter number to be deleted: " );
                    scanf( "%d", &id );

                    if ( deletes( &startPtr, id ) ) {
                        printf( "%d deleted.\n", id );
                        // ลบเสร็จ ปริ้น 2 บรรทัดเหมือนกัน
                        printList( startPtr );
                        printListReverse( startPtr );
                        puts( "NULL" );
                    } else {
                        printf( "%d not found.\n\n", id );
                    }
                } else {
                    puts( "List is empty.\n" );
                }
                break;
            default:
                puts( "Invalid choice.\n" );
                instructions();
                break;
        }
        printf( "? " );
        scanf( "%u", &choice );
    }

    // ส่วนจบการทำงาน (ตามรูปภาพ)
    puts( "Clear all nodes" );
    clearList( &startPtr );
    puts( "End of run." );
    return 0;
}