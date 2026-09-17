#include <stdio.h>
#include <stdlib.h>

// Structural representation of a Fibonacci Heap Node
typedef struct FibNode {
    int key;
    int degree;
    struct FibNode* parent;
    struct FibNode* child;
    struct FibNode* left;
    struct FibNode* right;
    int mark; // 0 for false, 1 for true
} FibNode;

// Structural representation of a Fibonacci Heap
typedef struct FibonacciHeap {
    FibNode* min_node;
    int total_nodes;
} FibonacciHeap;

// Global helper to instantiate an empty heap
FibonacciHeap* create_heap() {
    FibonacciHeap* heap = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
    heap->min_node = NULL;
    heap->total_nodes = 0;
    return heap;
}

// Global helper to instantiate a standalone node
FibNode* create_node(int key) {
    FibNode* node = (FibNode*)malloc(sizeof(FibNode));
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->mark = 0;
    return node;
}

// a) Insert(x) - Insert a new node in O(1) time
void insert(FibonacciHeap* heap, int key) {
    FibNode* node = create_node(key);
    
    if (heap->min_node == NULL) {
        heap->min_node = node;
    } else {
        // Splice the node into the root list
        node->right = heap->min_node;
        node->left = heap->min_node->left;
        heap->min_node->left->right = node;
        heap->min_node->left = node;
        
        // Update global minimum pointer
        if (node->key < heap->min_node->key) {
            heap->min_node = node;
        }
    }
    heap->total_nodes++;
}

// a) Find-Min() - Return the minimum key in O(1) time
int find_min(FibonacciHeap* heap) {
    if (heap->min_node == NULL) {
        return -1; // Flag indicating empty heap
    }
    return heap->min_node->key;
}

// a) Union(H1, H2) - Merge two Fibonacci Heaps in O(1) time
FibonacciHeap* union_heaps(FibonacciHeap* h1, FibonacciHeap* h2) {
    FibonacciHeap* h3 = create_heap();
    h3->min_node = h1->min_node;
    
    if (h1->min_node != NULL && h2->min_node != NULL) {
        // Trace and save the boundary elements
        FibNode* h1_min_left = h1->min_node->left;
        FibNode* h2_min_left = h2->min_node->left;
        
        // Interlock structural boundaries 
        h1->min_node->left = h2_min_left;
        h2_min_left->right = h1->min_node;
        
        h2->min_node->left = h1_min_left;
        h1_min_left->right = h2->min_node;
        
        // Evaluate the accurate minimum pointer
        if (h2->min_node->key < h1->min_node->key) {
            h3->min_node = h2->min_node;
        }
    } else if (h2->min_node != NULL) {
        h3->min_node = h2->min_node;
    }
    
    h3->total_nodes = h1->total_nodes + h2->total_nodes;
    return h3;
}

// Recursive helper for printing structural depths
void display_tree(FibNode* node, int depth) {
    if (node == NULL) return;
    
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    if (depth > 0) {
        printf("└── ");
    } else {
        printf("• ");
    }
    printf("Node Key: %d (Degree: %d)\n", node->key, node->degree);
    
    if (node->child != NULL) {
        FibNode* curr_child = node->child;
        do {
            display_tree(curr_child, depth + 1);
            curr_child = curr_child->right;
        } while (curr_child != node->child);
    }
}

// b) Display the heap structure before and after each operation
void display(FibonacciHeap* heap, const char* name) {
    printf("=== %s Structure ===\n", name);
    if (heap->min_node == NULL) {
        printf("Heap is empty.\n");
        printf("==============================\n\n");
        return;
    }
    
    printf("Total Nodes: %d\n", heap->total_nodes);
    int min_val = find_min(heap);
    if (min_val != -1) {
        printf("Verified Min Key: %d\n", min_val);
    }
    
    printf("Root list node elements:\n");
    FibNode* curr = heap->min_node;
    do {
        display_tree(curr, 0);
        curr = curr->right;
    } while (curr != heap->min_node);
    printf("==============================\n\n");
}

// Testing Harness
int main() {
    printf("--- Demonstrating Fibonacci Heap Operations ---\n\n");
    
    // Setup Heap 1
    FibonacciHeap* H1 = create_heap();
    printf("Creating Heap 1 and inserting elements...\n");
    insert(H1, 15);
    display(H1, "H1 after Insert(15)");
    
    insert(H1, 7);
    display(H1, "H1 after Insert(7)");
    
    insert(H1, 24);
    display(H1, "H1 after Insert(24)");
    
    // Setup Heap 2
    FibonacciHeap* H2 = create_heap();
    printf("Creating Heap 2 and inserting elements...\n");
    insert(H2, 9);
    display(H2, "H2 after Insert(9)");
    
    // Execution of Union
    printf("Performing Union(H1, H2)...\n");
    FibonacciHeap* H3 = union_heaps(H1, H2);
    display(H3, "Merged Heap H3");
    
    // Clean up allocated structures
    free(H1);
    free(H2);
    free(H3);
    
    return 0;
}
