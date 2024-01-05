#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// 创建链表
Node *createList() {
    int num;
    printf("请输入整数序列（以0结束输入）：");
    Node *head = NULL;
    Node *tail = NULL;

    while (scanf("%d", &num) == 1 && num != 0) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = num;
        newNode->next = NULL;
        
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    return head;
}

// 判断是否是子序列的递归函数
int isSubsequence(Node *A, Node *B) {
    // 如果 B 为空，表示已经遍历完 B 所有元素，返回 1
    if (B == NULL) {
        return 1;
    }
    
    // 如果 A 为空，但 B 不为空，表示 A 遍历完了但 B 还有剩余元素，返回 0
    if (A == NULL) {
        return 0;
    }
    
    // 如果当前 A 和 B 的节点值相等，继续判断下一个节点
    if (A->data == B->data) {
        return isSubsequence(A->next, B->next);
    }
    
    // 如果当前 A 和 B 的节点值不相等，继续判断 A 的下一个节点
    return isSubsequence(A->next, B);
}

// 测试函数
int main() {
    // 创建链表 A
    Node *A = createList();

    // 创建链表 B
    Node *B = createList();

    // 判断 B 是否是 A 的子序列
    if (isSubsequence(A, B)) {
        printf("是子序列");
    } else {
        printf("不是子序列");
    }

    // 释放链表所占内存
    Node *tmp;
    while (A != NULL) {
        tmp = A;
        A = A->next;
        free(tmp);
    }
    while (B != NULL) {
        tmp = B;
        B = B->next;
        free(tmp);
    }

    return 0;
}
