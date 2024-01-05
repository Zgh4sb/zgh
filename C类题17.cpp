#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// 创建一个新节点
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // 分配内存给新节点
    newNode->data = data; // 设置节点数据
    newNode->next = NULL; // 将节点的下一个指针设为NULL，表示当前节点为尾节点
    return newNode; // 返回新创建的节点
}

// 在环形链表的末尾插入新节点
void insertNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data); // 创建新节点

    if (*head == NULL) { // 如果链表为空
        *head = newNode; // 将头指针指向新节点
        newNode->next = *head; // 将新节点的下一个指针指向自己，构成环形链表
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) { // 找到链表中最后一个节点
            temp = temp->next;
        }
        temp->next = newNode; // 将新节点插入到末尾
        newNode->next = *head; // 新节点指向头节点，构成环形链表
    }
}

// 从环形链表中删除指定节点
void deleteNode(struct Node** head, struct Node* target) {
    if (*head == NULL || target == NULL) { // 如果链表为空或者目标节点为空，直接返回
        return;
    }

    if (*head == target) { // 如果目标节点是头节点
        struct Node* lastNode = *head;
        while (lastNode->next != *head) { // 找到链表中最后一个节点
            lastNode = lastNode->next;
        }

        if (*head == (*head)->next) { // 如果链表只有一个节点
            free(*head); // 释放头节点内存
            *head = NULL; // 将头指针设为NULL
        } else {
            lastNode->next = (*head)->next; // 将最后一个节点指向第二个节点
            free(*head); // 释放头节点内存
            *head = lastNode->next; // 将头指针指向第二个节点
        }
    } else {
        struct Node* temp = *head;
        while (temp->next != *head && temp->next != target) { // 找到目标节点的前一个节点
            temp = temp->next;
        }

        if (temp->next == target) { // 如果找到了目标节点的前一个节点
            temp->next = target->next; // 跳过目标节点，将前一个节点指向目标节点的下一个节点
            free(target); // 释放目标节点内存
        }
    }
}

// 约瑟夫环问题求解
void josephus(struct Node** head, int k, int totalPeople) {
    if (*head == NULL) { // 如果链表为空
        printf("名单为空\n");
        return;
    }

    struct Node* current = *head;
    struct Node* next;

    printf("被淘汰人的序列: ");
    while (*head != (*head)->next) { // 当链表中还有超过一个节点时
        for (int i = 1; i < k; i++) { // 数数k次
            current = current->next;
        }

        printf("%d ", current->data); // 输出被淘汰的人的编号

        next = current->next;
        deleteNode(head, current); // 删除被淘汰的人的节点
        current = next; // 继续下一轮循环
    }

    printf("\n最后剩下来的人: %d\n", (*head)->data); // 输出最后剩下来的人的编号
}

// 打印链表
void printList(struct Node* head) {
    if (head == NULL) { // 如果链表为空
        printf("列表为空\n");
        return;
    }

    struct Node* temp = head;
    do {
        printf("%d ", temp->data); // 输出节点数据
        temp = temp->next; // 移动到下一个节点
    } while (temp != head); // 直到回到头节点

    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int totalPeople, k, inputData;

    printf("输入总人数: ");
    scanf("%d", &totalPeople); // 输入总人数

    printf("报数间隔: ");
    scanf("%d", &k); // 输入报数间隔

    printf("输出下列结果:\n");
    for (int i = 1; i <= totalPeople; i++) {
        insertNode(&head, i); // 将1到总人数的编号插入到链表中
    }

    printf("刚开始的排序名单: ");
    printList(head); // 打印初始的排序名单

    josephus(&head, k, totalPeople); // 解决约瑟夫环问题

    return 0;
}


