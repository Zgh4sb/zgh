#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define TABLE_SIZE 100

typedef struct {
    char tel[20];
    char name[30];
    char address[50];
} UserInfo;

typedef struct hash_slot {
    UserInfo data;
    int status; // 0表示空槽，1表示已使用槽，-1表示删除槽
    struct hash_slot* next;
} HashSlot;

// 哈希函数1
int hashFunction1(const char* tel) {
    int sum = 0;
    for (int i = 0; tel[i] != '\0'; i++) {
        sum += tel[i];
    }
    return sum % TABLE_SIZE;
}

// 哈希函数2
int hashFunction2(const char* tel) {
    int hash = 0;
    int len = strlen(tel);
    for (int i = 0; i < len; i++) {
        hash = (hash * 31 + tel[i]) % TABLE_SIZE;
    }
    return hash;
}

// 线性探测法插入
void linearProbingInsert(HashSlot table[], const UserInfo* user, int (*hashFunction)(const char*)) {
    int hash = hashFunction(user->tel);
    int i = hash;
    int count = 0;
    while (table[i].status == 1 && strcmp(table[i].data.tel, user->tel) != 0) {
        i = (i + 1) % TABLE_SIZE;
        count++;
        if (i == hash) {
            printf("散列表已满，无法插入新数据。\n");
            return;
        }
    }
    if (table[i].status == 0 || table[i].status == -1) {
        table[i].data = *user;
        table[i].status = 1;
        printf("插入成功。\n");
    } else {
        printf("电话号码已存在，插入失败。\n");
    }
}

// 平方探测法插入
void quadraticProbingInsert(HashSlot table[], const UserInfo* user, int (*hashFunction)(const char*)) {
    int hash = hashFunction(user->tel);
    int i = hash;
    int count = 0;
    int step = 1;
    while (table[i].status == 1 && strcmp(table[i].data.tel, user->tel) != 0) {
        i = (i + step * step) % TABLE_SIZE;
        count++;
        step++;
        if (i == hash) {
            printf("散列表已满，无法插入新数据。\n");
            return;
        }
    }
    if (table[i].status == 0 || table[i].status == -1) {
        table[i].data = *user;
        table[i].status = 1;
        printf("插入成功。\n");
    } else {
        printf("电话号码已存在，插入失败。\n");
    }
}

// 拉链法插入
void chainingInsert(HashSlot table[], const UserInfo* user, int (*hashFunction)(const char*)) {
    int hash = hashFunction(user->tel);
    if (table[hash].status == 0 || table[hash].status == -1) {
        table[hash].data = *user;
        table[hash].status = 1;
    } else {
        HashSlot* slot = &table[hash];
        while (slot->next != NULL) {
            slot = slot->next;
        }
        HashSlot* newSlot = (HashSlot*)malloc(sizeof(HashSlot));
        newSlot->data = *user;
        newSlot->status = 1;
        newSlot->next = NULL;
        slot->next = newSlot;
    }
    printf("插入成功。\n");
}

// 线性探测法查找
void linearProbingSearch(const HashSlot table[], const char* tel, int (*hashFunction)(const char*)) {
    int hash = hashFunction(tel);
    int i = hash;
    int count = 0;
    while (table[i].status != 0) {
        if (table[i].status == 1 && strcmp(table[i].data.tel, tel) == 0) {
            printf("查找成功，用户信息：\n");
            printf("电话号码：%s\n", table[i].data.tel);
            printf("用户名：%s\n", table[i].data.name);
            printf("住址：%s\n", table[i].data.address);
            printf("比较次数：%d\n", count + 1);
            return;
        }
        i = (i + 1) % TABLE_SIZE;
        count++;
        if (i == hash) {
            printf("未找到匹配的电话号码。\n");
            return;
        }
    }
    printf("未找到匹配的电话号码。\n");
}

// 平方探测法查找
void quadraticProbingSearch(const HashSlot table[], const char* tel, int (*hashFunction)(const char*)) {
    int hash = hashFunction(tel);
    int i = hash;
    int count = 0;
    int step = 1;
    while (table[i].status != 0) {
        if (table[i].status == 1 && strcmp(table[i].data.tel, tel) == 0) {
            printf("查找成功，用户信息：\n");
            printf("电话号码：%s\n", table[i].data.tel);
            printf("用户名：%s\n", table[i].data.name);
            printf("住址：%s\n", table[i].data.address);
            printf("比较次数：%d\n", count + 1);
            return;
        }
        i = (i + step * step) % TABLE_SIZE;
        count++;
        step++;
        if (i == hash) {
            printf("未找到匹配的电话号码。\n");
            return;
        }
    }
    printf("未找到匹配的电话号码。\n");
}

// 拉链法查找
void chainingSearch(const HashSlot table[], const char* tel, int (*hashFunction)(const char*)) {
    int hash = hashFunction(tel);
    const HashSlot* slot = &table[hash];
    while (slot != NULL) {
        if (slot->status == 1 && strcmp(slot->data.tel, tel) == 0) {
            printf("查找成功，用户信息：\n");
            printf("电话号码：%s\n", slot->data.tel);
            printf("用户名：%s\n", slot->data.name);
            printf("住址：%s\n", slot->data.address);
            return;
        }
        slot = slot->next;
    }
    printf("未找到匹配的电话号码。\n");
}

int main() {
    HashSlot table[TABLE_SIZE];

    // 初始化散列表
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].status = 0;
        table[i].next = NULL;
    }

    // 用户记录
    UserInfo users[] = {
        {"1234567890", "阿尔法", "Beijing"},
        {"9876543210", "东方镜", "Shanghai"},
        {"1111111111", "比就干", "Guangzhou"},
        {"2222222222", "大卫", "Shenzhen"},
        {"3333333333", "阿珂", "Chengdu"}
    };
    int userCount = sizeof(users) / sizeof(users[0]);

    // 使用线性探测法插入用户记录
    for (int i = 0; i < userCount; i++) {
        linearProbingInsert(table, &users[i], hashFunction1);
    }

    // 使用平方探测法插入用户记录
    for (int i = 0; i < userCount; i++) {
        quadraticProbingInsert(table, &users[i], hashFunction2);
    }

    // 使用拉链法插入用户记录
    for (int i = 0; i < userCount; i++) {
        chainingInsert(table, &users[i], hashFunction1);
    }

    // 使用线性探测法查找用户记录
    for (int i = 0; i < userCount; i++) {
        linearProbingSearch(table, users[i].tel, hashFunction1);
    }

    // 使用平方探测法查找用户记录
    for (int i = 0; i < userCount; i++) {
        quadraticProbingSearch(table, users[i].tel, hashFunction2);
    }

    // 使用拉链法查找用户记录
    for (int i = 0; i < userCount; i++) {
        chainingSearch(table, users[i].tel, hashFunction1);
    }
    

    return 0;
}

