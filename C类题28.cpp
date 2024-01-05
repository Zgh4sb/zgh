#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* createTree() {
    int value;
    scanf("%d", &value);
    if (value == -1) {
        return NULL;
    }

    struct Node* node = createNode(value);
    node->left = createTree();
    node->right = createTree();
    return node;
}

int isFullTree(struct Node* root) {
    if (root == NULL) {
        return 1;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    if (root->left != NULL && root->right != NULL) {
        return isFullTree(root->left) && isFullTree(root->right);
    }

    return 0;
}

int isCompleteTree(struct Node* root, int index, int node_count) {
    if (root == NULL) {
        return 1;
    }

    if (index >= node_count) {
        return 0;
    }

    return isCompleteTree(root->left, 2 * index + 1, node_count) && isCompleteTree(root->right, 2 * index + 2, node_count);
}

// countNodes 函数定义移出main函数，确保它在全局作用域中
void countNodes(struct Node* node, int* node_count) {
    if (node == NULL) {
        return;
    }
    (*node_count)++;
    countNodes(node->left, node_count);
    countNodes(node->right, node_count);
}

int main() {
    printf("请按照从上到下、从左到右的顺序依次输入二叉树的节点值（-1表示该位置上为空）：\n");

    struct Node* root = createTree();

    int node_count = 0;
    countNodes(root, &node_count);

    if (isFullTree(root)) {
        printf("该二叉树是满二叉树。\n");
    } else {
        printf("该二叉树不是满二叉树。\n");
    }

    if (isCompleteTree(root, 0, node_count)) {
        printf("该二叉树是完全二叉树。\n");
    } else {
        printf("该二叉树不是完全二叉树。\n");
    }

    // Add code here to free the allocated memory of the binary tree to prevent memory leaks.

    return 0;
}
