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

void instructions( void )
{
    puts( "Enter your choice:\n"
          "   1 to insert an element into the list.\n"
          "   2 to delete an element from the list.\n"
          "   3 to end." );
}

void insert( LLPtr *sPtr, int id, char *name )
{
    LLPtr newPtr;
    LLPtr previousPtr;
    LLPtr currentPtr;

    newPtr = (LLPtr) malloc( sizeof( LLnode ) );

    if ( newPtr != NULL ) {
        newPtr->id = id;
        strcpy( newPtr->name, name );
        newPtr->nextPtr = NULL;
        newPtr->pPtr = NULL;

        previousPtr = NULL;
        currentPtr = *sPtr;

        while ( currentPtr != NULL && id > currentPtr->id ) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        newPtr->nextPtr = currentPtr;
        if ( currentPtr != NULL ) {
            currentPtr->pPtr = newPtr;
        }

        newPtr->pPtr = previousPtr;
        if ( previousPtr == NULL ) {
            *sPtr = newPtr;
        } else {
            previousPtr->nextPtr = newPtr;
        }
    } else {
        printf( "%d not inserted. No memory available.\n", id );
    }
}

int deletes( LLPtr *sPtr, int id )
{
    LLPtr currentPtr = *sPtr;

    if ( *sPtr == NULL ) return 0;

    while ( currentPtr != NULL && currentPtr->id != id ) {
        currentPtr = currentPtr->nextPtr;
    }

    if ( currentPtr == NULL ) return 0;

    if ( currentPtr->pPtr != NULL ) {
        currentPtr->pPtr->nextPtr = currentPtr->nextPtr;
    } else {
        *sPtr = currentPtr->nextPtr;
    }

    if ( currentPtr->nextPtr != NULL ) {
        currentPtr->nextPtr->pPtr = currentPtr->pPtr;
    }

    free( currentPtr );
    return id;
}

int isEmpty( LLPtr sPtr )
{
    return sPtr == NULL;
}

void printList( LLPtr currentPtr )
{
    if ( isEmpty( currentPtr ) ) {
        puts( "List is empty." );
    } else {
        puts( "The list is:" );
        while ( currentPtr != NULL ) {
            // แก้ตรงนี้: เอาเว้นวรรคหลัง --> ออก
            printf( "%d %s -->", currentPtr->id, currentPtr->name );
            currentPtr = currentPtr->nextPtr;
        }
        puts( "NULL" );
    }
}

void printListReverse( LLPtr currentPtr )
{
    if ( isEmpty( currentPtr ) ) return;

    while ( currentPtr->nextPtr != NULL ) {
        currentPtr = currentPtr->nextPtr;
    }

    puts( "The list is (Reverse):" );
    while ( currentPtr != NULL ) {
        // แก้ตรงนี้: เอาเว้นวรรคหลัง --> ออก
        printf( "%d %s -->", currentPtr->id, currentPtr->name );
        currentPtr = currentPtr->pPtr;
    }
    puts( "NULL" );
}

void clearList( LLPtr *sPtr )
{
    LLPtr currentPtr = *sPtr;
    LLPtr tempPtr;

    while ( currentPtr != NULL ) {
        tempPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
        free( tempPtr );
    }
    *sPtr = NULL;
}