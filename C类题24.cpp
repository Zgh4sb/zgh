#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// KMP�㷨ʵ���ַ�������
int kmp_search(const char *text, const char *pattern) {
    int len_text = strlen(text); // ��ȡĿ���ַ�������
    int len_pattern = strlen(pattern); // ��ȡģʽ�ַ�������

    int *lps = (int *)malloc(sizeof(int) * len_pattern); // ����洢�����ǰ��׺���ȵ�����
    int i = 1, j = 0;

    // ����ģʽ�ַ����������ǰ��׺����
    while (i < len_pattern) {
        if (pattern[i] == pattern[j]) {
            j++;
            lps[i] = j;
            i++;
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0;
    j = 0;
    // ʹ��KMP�㷨�����ַ���ƥ��
    while (i < len_text) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == len_pattern) {
            free(lps);
            return i - j; // ����ƥ��λ�õ���ʼ����
        } else if (i < len_text && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    return -1; // δ�ҵ�ƥ��
}

int main() {
    char text[100]; // Ŀ���ַ���
    char pattern[50]; // ģʽ�ַ���

    printf("����Ŀ���ַ�����");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // ȥ�����з�

    printf("����ģʽ�ַ�����");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0'; // ȥ�����з�

    int result = kmp_search(text, pattern); // ����KMP�㷨�����ַ���ƥ��

    if (result != -1) {
        printf("��λ�� %d ���ҵ�ƥ��\n", result); // ���ƥ��λ��
    } else {
        printf("δ�ҵ�ƥ��\n"); // ���δ�ҵ�ƥ��
    }

    return 0;
}

