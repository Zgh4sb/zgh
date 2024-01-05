#include <stdio.h>

int minSteps(int arr[], int n) {
    int steps = 0;
    
    // ��¼ÿ�����ֵ�ǰ���ڵ�λ��
    int positions[n+1];
    for (int i = 0; i < n; i++) {
        positions[arr[i]] = i+1;
    }
    
    // ��1��N����
    for (int i = 1; i <= n; i++) {
        if (positions[i] != i) { // �����ǰλ�ò�����ȷλ��
            int index = positions[i]; // �ҵ�����i�ڵ�ǰ�����е�λ��
            int temp = arr[i-1]; // ����λ��
            arr[i-1] = i;
            arr[index-1] = temp;
            positions[temp] = i; // ��������i�ĵ�ǰλ��
            steps++; // ������1
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

