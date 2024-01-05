#include <stdio.h>

void findMCoins(int coins[], int n, int amount) {
    int coinCount = 0; //记录使用的硬币数量

    printf("找零数目: %d\n", amount);

    for (int i = 0; i < n; i++) {
        while (amount >= coins[i]) { // 当目标金额大于等于当前面额的硬币时，使用当前面额的硬币
            amount -= coins[i]; // 扣除当前面额的硬币
            coinCount++; 
            printf("使用 %d cent 硬币\n", coins[i]); // 输出使用的硬币面额
        }
    }

    printf("总共硬币使用量: %d\n", coinCount); // 统计总共使用的硬币数量
}

int main() {
    int coins[] = {25, 10, 5, 1}; // 定义硬币面额数组
    int n = sizeof(coins) / sizeof(coins[0]); // 计算硬币面额数组的长度

    int amount;
    printf("输入金钱总额: ");
    scanf("%d", &amount); // 输入金钱总额

    findMCoins(coins, n, amount); 

    return 0;
}

