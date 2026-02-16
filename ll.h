
// self-referential structure
struct Node {
   int data; // each listNode contains a character
   struct Node *nextPtr; // pointer to next node
}; // end structure listNode

typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

