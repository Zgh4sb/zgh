#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 向树中插入新节点
TreeNode* insert(TreeNode* root, int key) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (key < root->data) {
        root->left = insert(root->left, key);
    } else if (key > root->data) {
        root->right = insert(root->right, key);
    }

    return root;
}

// 查找包含指定值的路径
int findPath(TreeNode* root, int key) {
    if (root == NULL) {
        return 0;
    }

    printf("%d ", root->data);

    if (key == root->data) {
        return 1;
    } else if (key < root->data) {
        if (findPath(root->left, key)) {
            return 1;
        }
    } else {
        if (findPath(root->right, key)) {
            return 1;
        }
    }

    return 0;
}

// 销毁树
void destroyTree(TreeNode* root) {
    if (root != NULL) {
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}

int main() {
    TreeNode* root = NULL;
    int n, key;

    printf("输入树中节点的个数: ");
    scanf("%d", &n);

    printf("输入节点的值: ");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("输入要查找的值: ");
    scanf("%d", &key);

    printf("路径为 %d: ", key);
    if (findPath(root, key)) {
        printf("\n");
    } else {
        printf("未找到\n");
    }

    destroyTree(root);

    return 0;
}

