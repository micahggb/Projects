#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the BST and AVL tree
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height; // Height of the node (for AVL tree)
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Function to get the height of a node
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the balance factor of a node
int balanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to right rotate subtree rooted with y
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    // Return new root
    return x;
}

// Function to left rotate subtree rooted with x
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    // Return new root
    return y;
}

// Function to insert a node into BST
struct Node* insertBST(struct Node* node, int data) {
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insertBST(node->left, data);
    else if (data > node->data)
        node->right = insertBST(node->right, data);
    else // Duplicate keys not allowed
        return node;

    return node;
}

// Function to balance the AVL tree
struct Node* balanceAVL(struct Node* node) {
    // Update height of current node
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Get balance factor of this node
    int balance = balanceFactor(node);

    // Left Left Case
    if (balance > 1 && balanceFactor(node->left) >= 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && balanceFactor(node->right) <= 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to convert BST to AVL tree
struct Node* convertBSTtoAVL(struct Node* node) {
    if (node == NULL)
        return NULL;

    // Perform inorder traversal and insert nodes into AVL tree
    struct Node* root = NULL;
    root = insertBST(root, node->data);
    root->left = convertBSTtoAVL(node->left);
    root->right = convertBSTtoAVL(node->right);

    return balanceAVL(root);
}

// Function to print pre-order traversal of a tree
void preOrder(struct Node* node) {
    if (node != NULL) {
        printf("%d ", node->data);
        preOrder(node->left);
        preOrder(node->right);
    }
}

// Function to free memory allocated for the tree
void freeTree(struct Node* node) {
    if (node == NULL)
        return;

    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    int keys[] = {1, 2, 3, 4, 5};
    int n = sizeof(keys) / sizeof(keys[0]);

    printf("Micah Juiye hlh816 Spring-2024\n");

    // Create BST
    struct Node* rootBST = NULL;
    for (int i = 0; i < n; i++)
        rootBST = insertBST(rootBST, keys[i]);

    // Print BST pre-order traversal
    printf("BST Pre-order traversal: ");
    preOrder(rootBST);
    printf("\n");

    // Convert BST to AVL tree
    struct Node* rootAVL = convertBSTtoAVL(rootBST);

    // Print AVL tree pre-order traversal
    printf("Balanced AVL Pre-order traversal: ");
    preOrder(rootAVL);
    printf("\n");

    // Free memory allocated for trees
    freeTree(rootBST);
    freeTree(rootAVL);

    return 0;
}