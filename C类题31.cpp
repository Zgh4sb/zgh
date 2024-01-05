#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char data); // 创建节点函数声明
Node* buildTree(); // 构建树函数声明
void findPath(Node* root, char target, char path[], int depth); // 查找路径函数声明

int main() {
    printf("请输入二叉树的数据:\n");
    Node* root = buildTree(); // 构建二叉树根节点

    char targetNode;
    printf("\n输入目标节点: ");
    scanf(" %c", &targetNode);

    printf("查找到节点 %c 的路径:\n", targetNode);
    char path[100];
    findPath(root, targetNode, path, 0); // 查找目标节点的路径

    free(root); // 释放二叉树内存

    return 0;
}

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // 分配节点内存
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* buildTree() {
    char data;
    scanf(" %c", &data);

    if (data == 'N') {
        return NULL; // 返回空节点
    }

    Node* root = createNode(data); // 创建根节点

    printf("输入 %c 的左子树:\n", data);
    root->left = buildTree(); // 构建左子树

    printf("输入 %c 的右子树:\n", data);
    root->right = buildTree(); // 构建右子树

    return root;
}

void findPath(Node* root, char target, char path[], int depth) {
    if (root == NULL) {
        printf("%c 不在树中。\n", target);
        return;
    }

    path[depth] = root->data;
    depth++;

    if (root->data == target && root->left == NULL && root->right == NULL) {
        printf("路径: ");
        for (int i = 0; i < depth; i++) {
            printf("%c ", path[i]);
        }
        printf("\n");
    }

    findPath(root->left, target, path, depth); // 递归查找左子树
    findPath(root->right, target, path, depth); // 递归查找右子树
}

