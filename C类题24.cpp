#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// KMP算法实现字符串查找
int kmp_search(const char *text, const char *pattern) {
    int len_text = strlen(text); // 获取目标字符串长度
    int len_pattern = strlen(pattern); // 获取模式字符串长度

    int *lps = (int *)malloc(sizeof(int) * len_pattern); // 申请存储最长公共前后缀长度的数组
    int i = 1, j = 0;

    // 计算模式字符串的最长公共前后缀长度
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
    // 使用KMP算法进行字符串匹配
    while (i < len_text) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == len_pattern) {
            free(lps);
            return i - j; // 返回匹配位置的起始索引
        } else if (i < len_text && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    free(lps);
    return -1; // 未找到匹配
}

int main() {
    char text[100]; // 目标字符串
    char pattern[50]; // 模式字符串

    printf("输入目标字符串：");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // 去除换行符

    printf("输入模式字符串：");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0'; // 去除换行符

    int result = kmp_search(text, pattern); // 调用KMP算法进行字符串匹配

    if (result != -1) {
        printf("在位置 %d 处找到匹配\n", result); // 输出匹配位置
    } else {
        printf("未找到匹配\n"); // 输出未找到匹配
    }

    return 0;
}

