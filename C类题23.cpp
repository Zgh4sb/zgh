#include <stdio.h>

// 函数声明
void decimalToBinary(int num);
void decimalToOctal(int num);
void decimalToHexadecimal(int num);

int main() {
    int decimalNum;
    
    // 从用户那里手动输入一些数据
    printf("请输入一个十进制数: ");
    scanf("%d", &decimalNum); // 接收用户输入的十进制数
    
    printf("十进制数 %d 的转换结果如下：\n", decimalNum);
    printf("二进制: ");
    decimalToBinary(decimalNum);
    printf("\n");
    printf("八进制: ");
    decimalToOctal(decimalNum);
    printf("\n");
    printf("十六进制: ");
    decimalToHexadecimal(decimalNum);
    printf("\n");

    return 0;
}

// 函数实现
void decimalToBinary(int num) {
    if (num > 0) {
        decimalToBinary(num / 2);
        printf("%d", num % 2);
    } else if (num == 0) {
        return;
    } else {
        printf("0");
    }
}

void decimalToOctal(int num) {
    if (num > 0) {
        decimalToOctal(num / 8);
        printf("%d", num % 8);
    } else if (num == 0) {
        return;
    } else {
        printf("0");
    }
}

void decimalToHexadecimal(int num) {
    char hexDigits[] = "0123456789ABCDEF";
    if (num > 0) {
        decimalToHexadecimal(num / 16);
        printf("%c", hexDigits[num % 16]);
    } else if (num == 0) {
        return;
    } else {
        printf("0");
    }
}
