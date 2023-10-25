#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct AVLNode {

    char* data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;

} AVLNode;

AVLNode* createNode(char* data){

	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    node->height = 1;
    return node;

}

void displayAVLTree(AVLNode* root){

    if(root != NULL){
        printf("%s ", root->data);
        displayAVLTree(root->left);
        displayAVLTree(root->right);
    }

    else printf("NULL ");

}

int getHeight(AVLNode* node){

    if (node == NULL) {
        return 0;
    }

    return node->height;

}

int max(int a, int b) {

    return (a > b) ? a : b;

}

// function for performing a right rotate
AVLNode* rotateRight(AVLNode* node){

    AVLNode* x = node->left;
    AVLNode* y = x->right;

    x->right = node;
    node->left = y;

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;

}

// function for performing a left rotate
AVLNode* rotateLeft(AVLNode* node){

    AVLNode* x = node->right;
    AVLNode* y = x->left;

    x->left = node;
    node->right = y;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

// get balance factor of given node
int getBalance(AVLNode* node){

    if(node == NULL) return 0;

    return getHeight(node->left)-getHeight(node->right);

}

AVLNode* min(AVLNode* node){

    AVLNode* temp = node;

    while(node != NULL) {
        temp = temp->left;
    }

    return temp;

}

// This deletes a node with 'data' into the AVL tree
// Please ensure that your function covers all 4 possible rotation cases
void deleteNode(AVLNode** root, char* data){
    if (*root == NULL) {
        return;
    }

    // Perform a standard BST delete
    if (strcmp(data, (*root)->data) < 0) {
        // The node to be deleted is in the left subtree
        deleteNode(&(*root)->left, data);
    } else if (strcmp(data, (*root)->data) > 0) {
        // The node to be deleted is in the right subtree
        deleteNode(&(*root)->right, data);
    } else {
        // Node with the data to be deleted is found

        // Node with only one child or no child
        if ((*root)->left == NULL || (*root)->right == NULL) {
            AVLNode* temp = (*root)->left ? (*root)->left : (*root)->right;

            // No child case
            if (temp == NULL) {
                temp = *root;
                *root = NULL;
            } else {
                // One child case
                **root = *temp;
            }
            free(temp->data);
            free(temp);
        } else {
            // Node with two children, get the in-order successor (smallest in the right subtree)
            AVLNode* temp = min((*root)->right);

            // Copy the in-order successor's data to this node
            free((*root)->data); // Free the current data
            (*root)->data = strdup(temp->data);

            // Delete the in-order successor
            deleteNode(&(*root)->right, temp->data);
        }
    }

    // If the tree had only one node, return
    if (*root == NULL) {
        return;
    }

    // Update the height of this node
    (*root)->height = 1 + max(getHeight((*root)->left), getHeight((*root)->right));

    // Get the balance factor to check if this node became unbalanced
    int balance = getBalance(*root);

    // Perform rotations to maintain AVL balance

    // Left Heavy
    if (balance > 1) {
        if (getBalance((*root)->left) >= 0) {
            // Left Left Case
            *root = rotateRight(*root);
        } else {
            // Left Right Case
            (*root)->left = rotateLeft((*root)->left);
            *root = rotateRight(*root);
        }
    }
    // Right Heavy
    else if (balance < -1) {
        if (getBalance((*root)->right) <= 0) {
            // Right Right Case
            *root = rotateLeft(*root);
        } else {
            // Right Left Case
            (*root)->right = rotateRight((*root)->right);
            *root = rotateLeft(*root);
        }
    }
} 

// This frees the memory used by the AVL tree
void freeAVLTree(AVLNode* root){

    if(root == NULL) return;
    
    freeAVLTree(root->left);
    freeAVLTree(root->right);
    free(root->data);
    free(root);

}

// AVLNode* insert(AVLNode* root, char* data) {
//     if (root == NULL) {
//         return createNode(data);
//     }

//     // Perform standard BST insertion
//     if (strcmp(data, root->data) < 0) {
//         root->left = insert(root->left, data);
//     } else if (strcmp(data, root->data) > 0) {
//         root->right = insert(root->right, data);
//     } else {
//         // Duplicate data is not allowed in AVL, so do nothing
//         return root;
//     }

//     // Update the height of this ancestor node
//     root->height = 1 + max(getHeight(root->left), getHeight(root->right));

//     // Get the balance factor for this ancestor node to check for balance violations
//     int balance = getBalance(root);

//     // Left Heavy
//     if (balance > 1) {
//         if (strcmp(data, root->left->data) < 0) {
//             // Left Left Case
//             return rotateRight(root);
//         } else {
//             // Left Right Case
//             root->left = rotateLeft(root->left);
//             return rotateRight(root);
//         }
//     }

//     // Right Heavy
//     if (balance < -1) {
//         if (strcmp(data, root->right->data) > 0) {
//             // Right Right Case
//             return rotateLeft(root);
//         } else {
//             // Right Left Case
//             root->right = rotateRight(root->right);
//             return rotateLeft(root);
//         }
//     }

//     return root;
// }

// // Wrapper function for inserting a node into the AVL tree
// void insertNode(AVLNode** root, char* data) {
//     *root = insert(*root, data);
// }

// int main() {
//     AVLNode* root = NULL;

//     // Insert nodes into the AVL tree
//     insertNode(&root, "apple");
//     insertNode(&root, "banana");
//     insertNode(&root, "cherry");
//     insertNode(&root, "date");
//     insertNode(&root, "grape");
//     insertNode(&root, "kiwi");
//     insertNode(&root, "mango");

//     printf("AVL Tree after insertions:\n");
//     displayAVLTree(root);
//     printf("\n");

//     // Delete a node from the AVL tree
//     printf("deleting");
//     deleteNode(&root, "banana");
//     printf("deletion done");
//     printf("AVL Tree after deleting 'banana':\n");
//     displayAVLTree(root);
//     printf("\n");

//     // Free memory used by the AVL tree
//     freeAVLTree(root);

//     return 0;
// }
