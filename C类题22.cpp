#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// �ж������Ƿ�Ϊ�Ϸ��ĳ�ջ����
bool isValidOutSequence(char sequence[], int length) {
    char stack[MAX_SIZE]; // ����ջ
    int top = -1; // ջ��ָ���ʼ��Ϊ-1

    for (int i = 0; i < length; i++) {
        if (sequence[i] == 'a') { // �����ǰ�ַ���a��������ջ
            stack[++top] = 'a';
        } else {
            while (top >= 0 && stack[top] == 'e') { // ���ջ��Ԫ����e������������ջ��Ԫ��ֱ����ΪeΪֹ
                top--;
            }
            if (top >= 0 && stack[top] == sequence[i] - 1) { // ���ջ��Ԫ�����뵱ǰ�ַ�ƥ���a�����䵯��
                top--;
            } else { // ���򣬵�ǰ���в��ǺϷ��ĳ�ջ����
                return false;
            }
        }
    }

    return top == -1; // ���ջΪ�գ��������ǺϷ��ĳ�ջ���У����򣬲��ǺϷ��ĳ�ջ����
}

int main() {
    char sequence[MAX_SIZE];
    int length;

    printf("������һ���ַ�����: ");
    scanf("%s", sequence);

    length = 0;
    while (sequence[length] != '\0') {
        length++;
    }

    if (isValidOutSequence(sequence, length)) {
        printf("���� \"%s\" ���ǺϷ��ĳ�ջ���С�\n", sequence);
    } else {
        printf("���� \"%s\" �ǺϷ��ĳ�ջ���С�\n", sequence);
    }

    return 0;
}

