#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int id;
    char name[50];
    struct Node *nextPtr;
    struct Node *pPtr; 
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
    char name[50];

    instructions();
    printf( "? " );

    if (scanf( "%u", &choice ) != 1) {
         while(getchar() != '\n'); 
         choice = 0;
    }

    while ( choice != 3 ) {
        switch ( choice ) {
            case 1:
                printf( "Enter id and name: " );
                if ( scanf( "%d %s", &id, name ) == 2 ) {
                    insert( &startPtr, id, name );
                    printList( startPtr );
                    printListReverse( startPtr ); // ต้องมีบรรทัดนี้เพื่อผ่าน Test
                } else {
                    while(getchar() != '\n');
                }
                break;

            case 2:
                if ( !isEmpty( startPtr ) ) {
                    printf( "Enter number to be deleted: " );
                    if ( scanf( "%d", &id ) == 1 ) {
                        if ( deletes( &startPtr, id ) ) {
                            printf( "%d deleted.\n", id );
                            printList( startPtr );
                            printListReverse( startPtr ); // ต้องมีบรรทัดนี้เพื่อผ่าน Test
                        } else {
                            printf( "%d not found.\n\n", id );
                        }
                    } else {
                         while(getchar() != '\n');
                    }
                } else {
                    puts( "List is empty.\n" );
                }
                break;

            default:
                puts( "Invalid choice." );
                while(getchar() != '\n');
                instructions();
                break;
        }

        printf( "? " );
        if (scanf( "%u", &choice ) != 1) {
            while(getchar() != '\n');
            choice = 0;
        }
    }

    puts( "End of run." );
    clearList( &startPtr );
    return 0;
}