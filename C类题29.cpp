#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 创建新节点
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 判断两棵树是否相同
int areTreesIdentical(struct TreeNode* root1, struct TreeNode* root2) {
    if (root1 == NULL && root2 == NULL) {
        return 1;
    }

    if (root1 == NULL || root2 == NULL) {
        return 0;
    }

    return (root1->data == root2->data) &&
           areTreesIdentical(root1->left, root2->left) &&
           areTreesIdentical(root1->right, root2->right);
}

// 判断root2是否是root1的子树
int isSubtree(struct TreeNode* root1, struct TreeNode* root2) {
    if (root2 == NULL) {
        return 1;
    }

    if (root1 == NULL) {
        return 0;
    }

    if (areTreesIdentical(root1, root2)) {
        return 1;
    }

    return isSubtree(root1->left, root2) || isSubtree(root1->right, root2);
}

// 构建树
struct TreeNode* buildTree() {
    int data;
    scanf("%d", &data);

    if (data == -1) {
        return NULL;
    }

    struct TreeNode* root = createNode(data);

    printf("输入%d的左子节点: ", data);
    root->left = buildTree();

    printf("输入%d的右子节点: ", data);
    root->right = buildTree();

    return root;
}

int main() {
    printf("输入B1树的数据（输入-1表示空节点）: \n");
    struct TreeNode* B1 = buildTree();

    printf("输入B2树的数据（输入-1表示空节点）: \n");
    struct TreeNode* B2 = buildTree();

    if (isSubtree(B1, B2)) {
        printf("包含相同结构子树\n");
    } else {
        printf("不包含相同结构子树\n");
    }

    // 释放内存
    free(B1);
    free(B2);

    return 0;
}

