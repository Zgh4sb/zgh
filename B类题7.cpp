#include <stdio.h>

int minSteps(int arr[], int n) {
    int steps = 0;
    
    // 记录每个数字当前所在的位置
    int positions[n+1];
    for (int i = 0; i < n; i++) {
        positions[arr[i]] = i+1;
    }
    
    // 从1到N遍历
    for (int i = 1; i <= n; i++) {
        if (positions[i] != i) { // 如果当前位置不是正确位置
            int index = positions[i]; // 找到数字i在当前排列中的位置
            int temp = arr[i-1]; // 交换位置
            arr[i-1] = i;
            arr[index-1] = temp;
            positions[temp] = i; // 更新数字i的当前位置
            steps++; // 步数加1
        }
    }
    
    return steps;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int result = minSteps(arr, n);
    printf("%d\n", result);
    
    return 0;
}

