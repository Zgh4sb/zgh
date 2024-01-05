#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// 判断序列是否为合法的出栈序列
bool isValidOutSequence(char sequence[], int length) {
    char stack[MAX_SIZE]; // 定义栈
    int top = -1; // 栈顶指针初始化为-1

    for (int i = 0; i < length; i++) {
        if (sequence[i] == 'a') { // 如果当前字符是a，则将其入栈
            stack[++top] = 'a';
        } else {
            while (top >= 0 && stack[top] == 'e') { // 如果栈顶元素是e，则连续弹出栈顶元素直到不为e为止
                top--;
            }
            if (top >= 0 && stack[top] == sequence[i] - 1) { // 如果栈顶元素是与当前字符匹配的a，则将其弹出
                top--;
            } else { // 否则，当前序列不是合法的出栈序列
                return false;
            }
        }
    }

    return top == -1; // 如果栈为空，则序列是合法的出栈序列；否则，不是合法的出栈序列
}

int main() {
    char sequence[MAX_SIZE];
    int length;

    printf("请输入一个字符序列: ");
    scanf("%s", sequence);

    length = 0;
    while (sequence[length] != '\0') {
        length++;
    }

    if (isValidOutSequence(sequence, length)) {
        printf("序列 \"%s\" 不是合法的出栈序列。\n", sequence);
    } else {
        printf("序列 \"%s\" 是合法的出栈序列。\n", sequence);
    }

    return 0;
}

