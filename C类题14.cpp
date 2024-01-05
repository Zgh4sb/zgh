#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isWiggleSequence(int nums[], int n) {
    if (n < 2) {
        return true;
    }
    
    int prevDiff = nums[1] - nums[0];
    int count = prevDiff != 0;
    
    for (int i = 2; i < n; i++) {
        int diff = nums[i] - nums[i-1];
        if ((diff > 0 && prevDiff <= 0) || (diff < 0 && prevDiff >= 0)) {
            count++;
            prevDiff = diff;
        }
    }
    
    return count > 1;
}

int main() {
    int capacity = 10; // 设定数组的最大长度
    int *nums = (int*)malloc(capacity * sizeof(int)); // 在 C++ 中需要显式类型转换
    int n = 0;
    
    printf("请输入数字序列的元素，如果输入完毕，请输入-1:\n ");
    int num;
    while (scanf("%d", &num) == 1 && num != -1) {
        if (n == capacity) { // 如果数组已满，需要扩容
            capacity *= 2;
            nums = (int*)realloc(nums, capacity * sizeof(int)); // 在 C++ 中需要显式类型转换
        }
        nums[n++] = num;
    }
    
    if (isWiggleSequence(nums, n)) {
        printf("是摆动序列。\n");
    } else {
        printf("非摆动序列，需要删除 %d 个元素。\n", n - 2);
    }
    
    free(nums);
    return 0;
}
