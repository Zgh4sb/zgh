#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// ����һ���½ڵ�
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // �����ڴ���½ڵ�
    newNode->data = data; // ���ýڵ�����
    newNode->next = NULL; // ���ڵ����һ��ָ����ΪNULL����ʾ��ǰ�ڵ�Ϊβ�ڵ�
    return newNode; // �����´����Ľڵ�
}

// �ڻ��������ĩβ�����½ڵ�
void insertNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data); // �����½ڵ�

    if (*head == NULL) { // �������Ϊ��
        *head = newNode; // ��ͷָ��ָ���½ڵ�
        newNode->next = *head; // ���½ڵ����һ��ָ��ָ���Լ������ɻ�������
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) { // �ҵ����������һ���ڵ�
            temp = temp->next;
        }
        temp->next = newNode; // ���½ڵ���뵽ĩβ
        newNode->next = *head; // �½ڵ�ָ��ͷ�ڵ㣬���ɻ�������
    }
}

// �ӻ���������ɾ��ָ���ڵ�
void deleteNode(struct Node** head, struct Node* target) {
    if (*head == NULL || target == NULL) { // �������Ϊ�ջ���Ŀ��ڵ�Ϊ�գ�ֱ�ӷ���
        return;
    }

    if (*head == target) { // ���Ŀ��ڵ���ͷ�ڵ�
        struct Node* lastNode = *head;
        while (lastNode->next != *head) { // �ҵ����������һ���ڵ�
            lastNode = lastNode->next;
        }

        if (*head == (*head)->next) { // �������ֻ��һ���ڵ�
            free(*head); // �ͷ�ͷ�ڵ��ڴ�
            *head = NULL; // ��ͷָ����ΪNULL
        } else {
            lastNode->next = (*head)->next; // �����һ���ڵ�ָ��ڶ����ڵ�
            free(*head); // �ͷ�ͷ�ڵ��ڴ�
            *head = lastNode->next; // ��ͷָ��ָ��ڶ����ڵ�
        }
    } else {
        struct Node* temp = *head;
        while (temp->next != *head && temp->next != target) { // �ҵ�Ŀ��ڵ��ǰһ���ڵ�
            temp = temp->next;
        }

        if (temp->next == target) { // ����ҵ���Ŀ��ڵ��ǰһ���ڵ�
            temp->next = target->next; // ����Ŀ��ڵ㣬��ǰһ���ڵ�ָ��Ŀ��ڵ����һ���ڵ�
            free(target); // �ͷ�Ŀ��ڵ��ڴ�
        }
    }
}

// Լɪ���������
void josephus(struct Node** head, int k, int totalPeople) {
    if (*head == NULL) { // �������Ϊ��
        printf("����Ϊ��\n");
        return;
    }

    struct Node* current = *head;
    struct Node* next;

    printf("����̭�˵�����: ");
    while (*head != (*head)->next) { // �������л��г���һ���ڵ�ʱ
        for (int i = 1; i < k; i++) { // ����k��
            current = current->next;
        }

        printf("%d ", current->data); // �������̭���˵ı��

        next = current->next;
        deleteNode(head, current); // ɾ������̭���˵Ľڵ�
        current = next; // ������һ��ѭ��
    }

    printf("\n���ʣ��������: %d\n", (*head)->data); // ������ʣ�������˵ı��
}

// ��ӡ����
void printList(struct Node* head) {
    if (head == NULL) { // �������Ϊ��
        printf("�б�Ϊ��\n");
        return;
    }

    struct Node* temp = head;
    do {
        printf("%d ", temp->data); // ����ڵ�����
        temp = temp->next; // �ƶ�����һ���ڵ�
    } while (temp != head); // ֱ���ص�ͷ�ڵ�

    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int totalPeople, k, inputData;

    printf("����������: ");
    scanf("%d", &totalPeople); // ����������

    printf("�������: ");
    scanf("%d", &k); // ���뱨�����

    printf("������н��:\n");
    for (int i = 1; i <= totalPeople; i++) {
        insertNode(&head, i); // ��1���������ı�Ų��뵽������
    }

    printf("�տ�ʼ����������: ");
    printList(head); // ��ӡ��ʼ����������

    josephus(&head, k, totalPeople); // ���Լɪ������

    return 0;
}


