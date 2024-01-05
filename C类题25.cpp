#include <stdio.h>
#include <string.h>
#include <ctype.h>

void formatSentence(char *input) {
    int len = strlen(input);
    
    // 移除前导空格
    while (len > 0 && isspace(input[0])) {
        memmove(input, input + 1, len);
        len--;
    }
    
    // 移除尾部空格
    while (len > 0 && isspace(input[len - 1])) {
        input[len - 1] = '\0';
        len--;
    }
    
    // 移除句子间多余的空间 
    for (int i = 0; i < len - 1; i++) {
        if (isspace(input[i]) && isspace(input[i + 1])) {
            memmove(input + i, input + i + 1, len - i);
            len--;
            i--;
        }
    }
}

int main() {
    char input[1000];
    
    // 进行输入 
    printf("输入初始句子: ");
    fgets(input, sizeof(input), stdin);
    
    formatSentence(input);
    
    // 输出结果 
    printf("格式化后: %s\n", input);
    
    return 0;
}
