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
        printf("%s", root->data);
        displayAVLTree(root->left);
        displayAVLTree(root->right);
    }

    else printf("NULL");

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
    
    AVLNode* r = *root;

    if(strcmp(data, r->data) < 0) deleteNode(&r->left, data);

    else if(strcmp(data, r->data) > 0) deleteNode(&r->right, data);

    else{

        // 0 child
        if(r->left == NULL && r->right == NULL) {
            AVLNode* temp = r;
            r = NULL;
            free(temp->data);
            free(temp);
        }

        // 1 left child
        else if(r->left != NULL && r->right == NULL){
            AVLNode* temp = r->left;
            free(r->data);
            free(r);
            *root = temp;
        }

        // 1 right child
        else if(r->left == NULL && r->right != NULL){
            AVLNode* temp = r->right;
            free(r->data);
            free(r);
            *root = temp;
        }

        // 2 child
        else{
            AVLNode* minNode = min(r->right); 
            r->data = minNode->data;
            deleteNode(&r->right , minNode->data);
        }
    }

    //BALANCING TREE

    if(*root == NULL) return;

    (*root)->height = 1 + max(getHeight((*root)->left), getHeight((*root)->right));
    int balance = getBalance(*root);

    if (balance > 1) {

        if (getBalance((*root)->left) >= 0) {
            // Left Left Case

            *root = rotateRight(*root);

        } 
        else {

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
            
        } 
        else {

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