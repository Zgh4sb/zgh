#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* add(char* num1, char* num2); // 加法
char* subtract(char* num1, char* num2); // 减法
char* multiply(char* num1, char* num2); // 乘法

void reverseString(char* str); // 字符串反转
char* removeLeadingZeros(char* str); // 移除前导零

int main() {
    printf("请输入第一个大数：");
    char num1[1000];
    scanf("%s", num1);

    printf("请输入第二个大数：");
    char num2[1000];
    scanf("%s", num2);

    char* result_add = add(num1, num2); // 加法
    char* result_subtract = subtract(num1, num2); // 减法
    char* result_multiply = multiply(num1, num2); // 乘法

    printf("\n计算结果：\n");
    printf("加法：%s\n", result_add);
    printf("减法：%s\n", result_subtract);
    printf("乘法：%s\n", result_multiply);

    /* 释放内存 */
    free(result_add);
    free(result_subtract);
    free(result_multiply);

    return 0;
}

/* 辅助函数实现 */
void reverseString(char* str) { // 字符串反转
    int length = strlen(str);
    int i, j;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

char* removeLeadingZeros(char* str) { // 移除前导零
    int i = 0;
    while (str[i] == '0') {
        i++;
    }
    if (i > 0) {
        memmove(str, str + i, strlen(str) - i + 1);
    }
    return str;
}

/* 函数实现 */
char* add(char* num1, char* num2) { // 加法
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = len1 > len2 ? len1 : len2;

    char* result = (char*)malloc((maxLen + 2) * sizeof(char));
    result[maxLen + 1] = '\0';

    int carry = 0;
    for (int i = 0; i < maxLen; i++) {
        int digit1 = i < len1 ? num1[len1 - 1 - i] - '0' : 0;
        int digit2 = i < len2 ? num2[len2 - 1 - i] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        result[maxLen - i] = (sum % 10) + '0';
        carry = sum / 10;
    }

    result[0] = carry + '0';
    return removeLeadingZeros(result);
}

char* subtract(char* num1, char* num2) { // 减法
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int maxLen = len1 > len2 ? len1 : len2;

    char* result = (char*)malloc((maxLen + 1) * sizeof(char));
    result[maxLen] = '\0';

    int borrow = 0;
    for (int i = 0; i < maxLen; i++) {
        int digit1 = i < len1 ? num1[len1 - 1 - i] - '0' : 0;
        int digit2 = i < len2 ? num2[len2 - 1 - i] - '0' : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result[maxLen - i - 1] = diff + '0';
    }

    return removeLeadingZeros(result);
}

char* multiply(char* num1, char* num2) { // 乘法
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int resultLen = len1 + len2;

    char* result = (char*)calloc(resultLen + 1, sizeof(char));
    result[resultLen] = '\0';

    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            int digit1 = num1[len1 - 1 - i] - '0';
            int digit2 = num2[len2 - 1 - j] - '0';

            int product = digit1 * digit2 + result[resultLen - i - j - 1];
            result[resultLen - i - j - 1] = product % 10;
            result[resultLen - i - j - 2] += product / 10;
        }
    }

    for (int i = 0; i < resultLen; i++) {
        result[i] += '0';
    }

    return removeLeadingZeros(result);
}
