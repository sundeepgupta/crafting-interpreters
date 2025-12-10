#include <stdlib.h>
#include <stdio.h>

// Step 1: Define our doubly linked list node
// In Swift, you'd use: class Node { var data: Int; var next: Node?; var prev: Node? }
// In C, we use a struct and explicit pointers
typedef struct Node {
    int data;              // The value stored in this node
    struct Node* next;     // Pointer to next node (like Swift's optional reference)
    struct Node* prev;     // Pointer to previous node
} Node;

// Step 2: Create a new node
// Unlike Swift where ARC manages memory, in C you must manually allocate with malloc()
Node* createNode(int data) {
    // malloc() allocates memory on the heap (returns NULL if it fails)
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;  // NULL is like Swift's nil
    newNode->prev = NULL;

    return newNode;
}

// Step 3: Insert at the head (beginning) of the list
// We need Node** (pointer to pointer) to modify the head pointer itself
void insertAtHead(Node** head, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) return;

    newNode->next = *head;  // *head dereferences to get the actual head pointer

    if (*head != NULL) {
        (*head)->prev = newNode;  // Update old head's prev pointer
    }

    *head = newNode;  // Update head to point to the new node
}

void insertBeforeNode(Node** head, int dataToFind, int newData) {
    if (*head == NULL) {
        printf("No head node");
        return;
    }

    Node* current = *head;
    while (current->data != dataToFind) {
        if (current == NULL) {
            printf("Node not found");
            return;
        }
        current = current->next;
    }

    Node* newNode = createNode(newData);
    newNode->next = current;

    if (current == *head) {
        *head = newNode;
        return;
    }

    newNode->prev = current->prev;
    current->prev = newNode;
    newNode->prev->next = newNode;
}

// Step 4: Insert at the tail (end) of the list
void insertAtTail(Node** head, int data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) return;

    // If list is empty, new node becomes the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Traverse to the last node
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Link the new node
    current->next = newNode;
    newNode->prev = current;
}

// Step 5: Print the list forward
void printForward(Node* head) {
    printf("Forward: ");
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Print the list backward
void printBackward(Node* head) {
    if (head == NULL) {
        printf("Backward: \n");
        return;
    }

    // First, go to the last node
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Now traverse backward using prev pointers
    printf("Backward: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

// Step 6: Delete a node with a specific value
void deleteNode(Node** head, int data) {
    Node* current = *head;

    // Find the node to delete
    while (current != NULL && current->data != data) {
        current = current->next;
    }

    // Node not found
    if (current == NULL) {
        printf("Node with value %d not found\n", data);
        return;
    }

    // Update links around the node to be deleted
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        // Deleting the head node
        *head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    // CRITICAL: Free the memory (unlike Swift, this doesn't happen automatically!)
    free(current);
    printf("Deleted node with value %d\n", data);
}

// Step 7: Free the entire list (MUST DO THIS in C to avoid memory leaks!)
void freeList(Node** head) {
    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);  // Free each node
        current = next;
    }

    *head = NULL;
    printf("List freed from memory\n");
}

int main(int argc, const char * argv[]) {
    printf("=== Doubly Linked List Demo ===\n\n");

    // Initialize an empty list (in Swift: var head: Node? = nil)
    Node* head = NULL;

    // Test 1: Insert at head
    printf("1. Inserting at head: 3, 2, 1\n");
    insertAtHead(&head, 3);
    insertAtHead(&head, 2);
    insertAtHead(&head, 1);
    printForward(head);
    printBackward(head);

    // Test 2: Insert at tail
    printf("\n2. Inserting at tail: 4, 5\n");
    insertAtTail(&head, 4);
    insertAtTail(&head, 5);
    printForward(head);
    printBackward(head);

    // Test 3: Delete a middle node
    printf("\n3. Deleting node with value 3\n");
    deleteNode(&head, 3);
    printForward(head);
    printBackward(head);

    // Test 4: Delete the head
    printf("\n4. Deleting head (value 1)\n");
    deleteNode(&head, 1);
    printForward(head);
    printBackward(head);

//    printf("\n5. Insert 1 before 2\n");
//    insertBeforeNode(&head, 2, 1);
//    printForward(head);

    printf("\nInsert 3 before 4\n");
    insertBeforeNode(&head, 4, 3);
    printForward(head);

    // Test 5: Try to delete a non-existent node
    printf("\n5. Trying to delete non-existent node (value 99)\n");
    deleteNode(&head, 99);

    // Test 6: Clean up (ALWAYS do this in C!)
    printf("\n6. Cleaning up memory\n");
    freeList(&head);

    printf("\n=== Demo Complete ===\n");
    return EXIT_SUCCESS;
}


