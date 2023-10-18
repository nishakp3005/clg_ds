#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode* create_node(int val) {
  TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
  node->val = val;
  node->left = NULL;
  node->right = NULL;
  return node;
}

TreeNode* buildTreeHelper(int* inorder, int inorderStart, int inorderEnd, int* postorder, int postorderStart, int postorderEnd) {
  if (inorderStart > inorderEnd || postorderStart > postorderEnd) {
    return NULL;
  }

  // The last element in postorder is the root of the current subtree
  int rootValue = postorder[postorderEnd];
  TreeNode* root = create_node(rootValue);

  // Find the index of the root in inorder to split the inorder and postorder arrays
  int inorderIndex = inorderStart;
  while (inorder[inorderIndex] != rootValue) {
    inorderIndex++;
  }

  // Build the right subtree first (because it appears before the left subtree in postorder)
  root->right = buildTreeHelper(inorder, inorderIndex + 1, inorderEnd, postorder, postorderStart + (inorderIndex - inorderStart), postorderEnd - 1);
  root->left = buildTreeHelper(inorder, inorderStart, inorderIndex - 1, postorder, postorderStart, postorderStart + (inorderIndex - inorderStart) - 1);

  return root;
}

TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
  if (inorderSize == 0 || postorderSize == 0) {
    return NULL;
  }

  return buildTreeHelper(inorder, 0, inorderSize - 1, postorder, 0, postorderSize - 1);
}

// Helper function to print the tree (in-order traversal)
void inOrderTraversal(TreeNode* node) {
  if (node) {
  inOrderTraversal(node->left);
  printf("%d ", node->val);
  inOrderTraversal(node->right);
  }
}

int main() {
  int postorder[] = {9, 15, 7, 20, 3};
  int inorder[] = {9, 3, 15, 20, 7};
  int size = sizeof(postorder) / sizeof(postorder[0]);

  TreeNode* root = buildTree(inorder, size, postorder, size);

  // Print the resulting tree using in-order traversal
  inOrderTraversal(root);

  return 0;
}
