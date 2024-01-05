#include <stdio.h>
#include <string.h>
#include<stdlib.h>
// Manacher�㷨
char* longestPalindromeManacher(char *s) {
    int n = strlen(s);
    char new_s[2*n+3];  // �������ַ���
    new_s[0] = '^';
    new_s[1] = '#';
    for (int i = 0; i < n; i++) {
        new_s[2 * i + 2] = s[i];
        new_s[2 * i + 3] = '#';
    }
    new_s[2*n+2] = '$';
    new_s[2*n+3] = '\0';

    int p[2*n+3];
    memset(p, 0, sizeof(p));
    int max_len = 0;
    int center = 0;
    int max_right = 0;
    int max_center = 0;

    for (int i = 1; i < 2*n+2; i++) {
        if (i < max_right) {
            int mirror = 2 * center - i;
            p[i] = (max_right - i) < p[mirror] ? (max_right - i) : p[mirror];
        }

        // ������չ���Ĵ�
        while (new_s[i + 1 + p[i]] == new_s[i - 1 - p[i]]) {
            p[i]++;
        }

        // ����max_right��center
        if (i + p[i] > max_right) {
            center = i;
            max_right = i + p[i];
        }

        // ��������Ĵ��ĳ��Ⱥ�����λ��
        if (p[i] > max_len) {
            max_len = p[i];
            max_center = i;
        }
    }

    int start = (max_center - max_len) / 2;
    int end = start + max_len;
    char *result = (char *)malloc((max_len + 1) * sizeof(char));
    strncpy(result, s + start, max_len);
    result[max_len] = '\0';

    return result;
}

// ����ƥ���㷨
char* longestPalindromeBruteForce(char *s) {
    int n = strlen(s);
    int max_len = 0;
    char *result = NULL;

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int len = j - i + 1;
            int is_palindrome = 1;
            for (int k = 0; k < len / 2; k++) {
                if (s[i + k] != s[j - k]) {
                    is_palindrome = 0;
                    break;
                }
            }
            if (is_palindrome && len > max_len) {
                max_len = len;
                result =(char*)realloc(result, (max_len + 1) * sizeof(char));
                strncpy(result, s + i, max_len);
                result[max_len] = '\0';
            }
        }
    }

    return result;
}

int main() {
    char s[] = "ATGCCTAGGTGAGTTAC";

    // ʹ��Manacher�㷨
    char *manacher_result = longestPalindromeManacher(s);
    printf("Manacher�㷨���: %s\n", manacher_result);
    free(manacher_result);

    // ʹ�ñ���ƥ���㷨
    char *brute_force_result = longestPalindromeBruteForce(s);
    printf("����ƥ���㷨���: %s\n", brute_force_result);
    free(brute_force_result);

    return 0;
}

