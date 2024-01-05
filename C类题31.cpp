#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char data); // �����ڵ㺯������
Node* buildTree(); // ��������������
void findPath(Node* root, char target, char path[], int depth); // ����·����������

int main() {
    printf("�����������������:\n");
    Node* root = buildTree(); // �������������ڵ�

    char targetNode;
    printf("\n����Ŀ��ڵ�: ");
    scanf(" %c", &targetNode);

    printf("���ҵ��ڵ� %c ��·��:\n", targetNode);
    char path[100];
    findPath(root, targetNode, path, 0); // ����Ŀ��ڵ��·��

    free(root); // �ͷŶ������ڴ�

    return 0;
}

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // ����ڵ��ڴ�
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* buildTree() {
    char data;
    scanf(" %c", &data);

    if (data == 'N') {
        return NULL; // ���ؿսڵ�
    }

    Node* root = createNode(data); // �������ڵ�

    printf("���� %c ��������:\n", data);
    root->left = buildTree(); // ����������

    printf("���� %c ��������:\n", data);
    root->right = buildTree(); // ����������

    return root;
}

void findPath(Node* root, char target, char path[], int depth) {
    if (root == NULL) {
        printf("%c �������С�\n", target);
        return;
    }

    path[depth] = root->data;
    depth++;

    if (root->data == target && root->left == NULL && root->right == NULL) {
        printf("·��: ");
        for (int i = 0; i < depth; i++) {
            printf("%c ", path[i]);
        }
        printf("\n");
    }

    findPath(root->left, target, path, depth); // �ݹ����������
    findPath(root->right, target, path, depth); // �ݹ����������
}

