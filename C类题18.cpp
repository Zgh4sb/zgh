#include<stdio.h> 
#include <stdlib.h>
#include <stdbool.h>

// 节点的定义
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// 创建新节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->data = data;
    newNode->prev = newNode->next = newNode;
    return newNode;
}

// 插入新节点到链表
void insertNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!(*head)) {
        *head = newNode;
        return;
    }
    newNode->prev = (*head)->prev;
    newNode->next = *head;
    (*head)->prev->next = newNode;
    (*head)->prev = newNode;
}

// 显示链表
void displayList(Node* head) {
    if (!head) {
        return;
    }
    Node* current = head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("\n");
}

// 检查节点是否在链表中
bool contains(Node* head, int data) {
    if (!head) {
        return false;
    }
    Node* current = head;
    do {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    } while (current != head);
    return false;
}

// 计算两个链表的交集
Node* intersection(Node* headA, Node* headB) {
    Node* result = NULL;
    Node* currentA = headA;
    if (!headA || !headB) {
        return NULL;
    }
    do {
        if (contains(headB, currentA->data)) {
            insertNode(&result, currentA->data);
        }
        currentA = currentA->next;
    } while (currentA != headA);
    return result;
}

// 计算两个链表的并集
Node* unionList(Node* headA, Node* headB) {
    Node* result = NULL;
    Node* current = headA;
    if (!headA && !headB) {
        return NULL;
    }
    if (headA) {
        do {
            insertNode(&result, current->data);
            current = current->next;
        } while (current != headA);
    }
    if (headB) {
        current = headB;
        do {
            if (!contains(result, current->data)) {
                insertNode(&result, current->data);
            }
            current = current->next;
        } while (current != headB);
    }
    return result;
}

// 主函数
int main() {
    Node* setA = NULL;
    Node* setB = NULL;
    Node* intersec = NULL;
    Node* unionSet = NULL;

    // 手动输入数据
    printf("输入集合A的元素，-1结束:\n");
    while (true) {
        int data;
        scanf("%d", &data);
        if (data == -1) break;
        insertNode(&setA, data);
    }

    printf("输入集合B的元素，-1结束:\n");
    while (true) {
        int data;
        scanf("%d", &data);
        if (data == -1) break;
        insertNode(&setB, data);
    }

    // 显示初始集合
    printf("集合A: ");
    displayList(setA);
    printf("集合B: ");
    displayList(setB);

    // 计算交集和并集
    intersec = intersection(setA, setB);
    unionSet = unionList(setA, setB);

    // 显示结果
    printf("交集: ");
    displayList(intersec);
    printf("并集: ");
    displayList(unionSet);

    // 释放内存
    // (这里省略)

    return 0;
}
