#include <stdio.h>
#include <stdlib.h>

// 合并两个排序数组的中位数查找函数
float findMedianSortedArrays(int *a, int *b, int n) {
    int min_index = 0, max_index = n, i, j;
    float median;
    
    while (min_index <= max_index) {
        i = (min_index + max_index) / 2;
        j = n - i;
        
        if (i < n && j > 0 && b[j - 1] > a[i]) {
            min_index = i + 1;
        } else if (i > 0 && j < n && a[i - 1] > b[j]) {
            max_index = i - 1;
        } else {
            // 达到理想情况
            if (i == 0) {
                median = b[j - 1];
            } else if (j == 0) {
                median = a[i - 1];
            } else {
                median = a[i - 1] > b[j - 1] ? a[i - 1] : b[j - 1];
            }
            break;
        }
    }
    
    // 处理序列总长度为奇数的情况
    if ((n + n) % 2 == 1)
        return median;
    
    // 处理序列总长度为偶数的情况
    if (i == n) {
        return (median + b[0]) / 2.0;
    } else if (j == n) {
        return (median + a[0]) / 2.0;
    }
    return (median + (a[i] < b[j] ? a[i] : b[j])) / 2.0;
}

// 向用户提示并读取输入序列的函数
int *readSequence(int *length) {
    printf("请输入升序序列(输入非数字字符结束): ");
    
    int input, size = 0, capacity = 10;
    int *arr = (int *)malloc(capacity * sizeof(int));
    
    while (scanf("%d", &input) == 1) {
        if (size >= capacity) {
            capacity *= 2;
            arr = (int *)realloc(arr, capacity * sizeof(int));
        }
        arr[size++] = input;
    }
    while (getchar() != '\n'); // 清空输入缓冲区

    *length = size;
    return arr;
}

int main() {
    int lengthA, lengthB;
    
    printf("对于序列 A:\n");
    int *arrA = readSequence(&lengthA);
    
    printf("对于序列 B:\n");
    int *arrB = readSequence(&lengthB);
    
    if (lengthA != lengthB) {
        printf("两个序列长度不相等，无法计算中位数。\n");
        free(arrA);
        free(arrB);
        return 1;
    }

    // 计算和打印中位数
    float median = findMedianSortedArrays(arrA, arrB, lengthA);
    printf("两个序列的中位数是: %f\n", median);

    // 释放内存
    free(arrA);
    free(arrB);

    return 0;
}
