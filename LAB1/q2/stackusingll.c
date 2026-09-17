#include <stdio.h>
#include <stdlib.h>

// Structure for a linked list node
struct Node {
    int data;
    struct Node* next;
};

// Global pointer representing the top of the stack
struct Node* top = NULL;

// Function to push an element onto the stack
void push(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Stack Overflow (Out of memory)\n");
    } else {
        newNode->data = val;
        newNode->next = top;
        top = newNode;
        printf("Pushed value %d into the stack\n", val);
    }
}

// Function to pop a single element from the stack
void pop() {
    if (top == NULL) {
        printf("Stack Underflow\n");
    } else {
        struct Node* temp = top;
        printf("%d value popped from stack\n", top->data);
        top = top->next;
        free(temp);
    }
}

// Function to pop 'n' elements from the stack
void multipop(int n) {
    if (top == NULL) {
        printf("Stack Underflow\n");
        return;
    }

    int poppedCount = 0;
    // Pop elements until the count is reached or the stack becomes empty
    while (top != NULL && poppedCount < n) {
        struct Node* temp = top;
        printf("%d value popped from stack\n", top->data);
        top = top->next;
        free(temp);
        poppedCount++;
    }

    if (poppedCount < n) {
        printf("Stack became empty. Cleared remaining elements.\n");
    }
}

// Function to display all elements in the stack
void display() {
    if (top == NULL) {
        printf("Stack is Empty\n");
    } else {
        struct Node* temp = top;
        printf("Stack elements: ");
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    int choice;
    int num, x;

    while (1) {
        printf("\nChoose Operation to perform on the stack\n");
        printf("[1] Push Element\n");
        printf("[2] Pop Element\n");
        printf("[3] Multipop Elements\n");
        printf("[4] Display\n");
        printf("[5] Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input type!\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter Value to push into stack: ");
                scanf("%d", &num);
                push(num);
                break;
            case 2:
                pop();
                break;
            case 3:
                printf("Enter number of values to pop from stack: ");
                scanf("%d", &x);
                multipop(x);
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Choose a Valid Operation\n");
        }
    }
    return 0;
}

