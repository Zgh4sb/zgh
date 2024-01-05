#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct Node {
    int data;
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
            tail = newNode;
        }
    }
    
    return head;
}

// 将链表分成奇数位置和偶数位置两个链表
void splitList(Node *L, Node **L1, Node **L2) {
    Node *odd = NULL; // 奇数位置链表头指针
    Node *even = NULL; // 偶数位置链表头指针
    Node *oddPtr = NULL; // 奇数位置链表尾指针
    Node *evenPtr = NULL; // 偶数位置链表尾指针
    int count = 1;

    while (L != NULL) {
        // 根据位置奇偶性将节点插入对应的链表
        if (count % 2 == 1) { // 奇数位置
            if (odd == NULL) {
                odd = L;
                oddPtr = L;
            } else {
                oddPtr->next = L;
                oddPtr = oddPtr->next;
            }
        } else { // 偶数位置
            if (even == NULL) {
                even = L;
                evenPtr = L;
            } else {
                evenPtr->next = L;
                evenPtr = evenPtr->next;
            }
        }

        L = L->next;
        count++;
    }

    // 给两个链表的尾节点指针置空
    if (oddPtr != NULL) {
        oddPtr->next = NULL;
    }
    if (evenPtr != NULL) {
        evenPtr->next = NULL;
    }

    // 返回结果
    *L1 = odd;
    *L2 = even;
}

// 打印链表
void printList(Node *L) {
    while (L != NULL) {
        printf("%d ", L->data);
        L = L->next;
    }
    printf("\n");
}

// 释放链表所占内存
void freeList(Node *L) {
    Node *tmp;
    while (L != NULL) {
        tmp = L;
        L = L->next;
        free(tmp);
    }
}

// 测试函数
int main() {
    // 创建链表
    Node *list = createList();

    // 分割链表为奇数位置和偶数位置两个链表
    Node *oddList, *evenList;
    splitList(list, &oddList, &evenList);

    // 打印结果
    printf("L1: ");
    printList(oddList);
    printf("L2: ");
    printList(evenList);

    // 释放链表所占内存
    freeList(oddList);
    freeList(evenList);

    return 0;
}
