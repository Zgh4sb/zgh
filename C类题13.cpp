#include <stdio.h>

void findMCoins(int coins[], int n, int amount) {
    int coinCount = 0; //��¼ʹ�õ�Ӳ������

    printf("������Ŀ: %d\n", amount);

    for (int i = 0; i < n; i++) {
        while (amount >= coins[i]) { // ��Ŀ������ڵ��ڵ�ǰ����Ӳ��ʱ��ʹ�õ�ǰ����Ӳ��
            amount -= coins[i]; // �۳���ǰ����Ӳ��
            coinCount++; 
            printf("ʹ�� %d cent Ӳ��\n", coins[i]); // ���ʹ�õ�Ӳ�����
        }
    }

    printf("�ܹ�Ӳ��ʹ����: %d\n", coinCount); // ͳ���ܹ�ʹ�õ�Ӳ������
}

int main() {
    int coins[] = {25, 10, 5, 1}; // ����Ӳ���������
    int n = sizeof(coins) / sizeof(coins[0]); // ����Ӳ���������ĳ���

    int amount;
    printf("�����Ǯ�ܶ�: ");
    scanf("%d", &amount); // �����Ǯ�ܶ�

    findMCoins(coins, n, amount); 

    return 0;
}

