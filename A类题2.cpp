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
    int status; // 0��ʾ�ղۣ�1��ʾ��ʹ�òۣ�-1��ʾɾ����
    struct hash_slot* next;
} HashSlot;

// ��ϣ����1
int hashFunction1(const char* tel) {
    int sum = 0;
    for (int i = 0; tel[i] != '\0'; i++) {
        sum += tel[i];
    }
    return sum % TABLE_SIZE;
}

// ��ϣ����2
int hashFunction2(const char* tel) {
    int hash = 0;
    int len = strlen(tel);
    for (int i = 0; i < len; i++) {
        hash = (hash * 31 + tel[i]) % TABLE_SIZE;
    }
    return hash;
}

// ����̽�ⷨ����
void linearProbingInsert(HashSlot table[], const UserInfo* user, int (*hashFunction)(const char*)) {
    int hash = hashFunction(user->tel);
    int i = hash;
    int count = 0;
    while (table[i].status == 1 && strcmp(table[i].data.tel, user->tel) != 0) {
        i = (i + 1) % TABLE_SIZE;
        count++;
        if (i == hash) {
            printf("ɢ�б��������޷����������ݡ�\n");
            return;
        }
    }
    if (table[i].status == 0 || table[i].status == -1) {
        table[i].data = *user;
        table[i].status = 1;
        printf("����ɹ���\n");
    } else {
        printf("�绰�����Ѵ��ڣ�����ʧ�ܡ�\n");
    }
}

// ƽ��̽�ⷨ����
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
            printf("ɢ�б��������޷����������ݡ�\n");
            return;
        }
    }
    if (table[i].status == 0 || table[i].status == -1) {
        table[i].data = *user;
        table[i].status = 1;
        printf("����ɹ���\n");
    } else {
        printf("�绰�����Ѵ��ڣ�����ʧ�ܡ�\n");
    }
}

// ����������
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
    printf("����ɹ���\n");
}

// ����̽�ⷨ����
void linearProbingSearch(const HashSlot table[], const char* tel, int (*hashFunction)(const char*)) {
    int hash = hashFunction(tel);
    int i = hash;
    int count = 0;
    while (table[i].status != 0) {
        if (table[i].status == 1 && strcmp(table[i].data.tel, tel) == 0) {
            printf("���ҳɹ����û���Ϣ��\n");
            printf("�绰���룺%s\n", table[i].data.tel);
            printf("�û�����%s\n", table[i].data.name);
            printf("סַ��%s\n", table[i].data.address);
            printf("�Ƚϴ�����%d\n", count + 1);
            return;
        }
        i = (i + 1) % TABLE_SIZE;
        count++;
        if (i == hash) {
            printf("δ�ҵ�ƥ��ĵ绰���롣\n");
            return;
        }
    }
    printf("δ�ҵ�ƥ��ĵ绰���롣\n");
}

// ƽ��̽�ⷨ����
void quadraticProbingSearch(const HashSlot table[], const char* tel, int (*hashFunction)(const char*)) {
    int hash = hashFunction(tel);
    int i = hash;
    int count = 0;
    int step = 1;
    while (table[i].status != 0) {
        if (table[i].status == 1 && strcmp(table[i].data.tel, tel) == 0) {
            printf("���ҳɹ����û���Ϣ��\n");
            printf("�绰���룺%s\n", table[i].data.tel);
            printf("�û�����%s\n", table[i].data.name);
            printf("סַ��%s\n", table[i].data.address);
            printf("�Ƚϴ�����%d\n", count + 1);
            return;
        }
        i = (i + step * step) % TABLE_SIZE;
        count++;
        step++;
        if (i == hash) {
            printf("δ�ҵ�ƥ��ĵ绰���롣\n");
            return;
        }
    }
    printf("δ�ҵ�ƥ��ĵ绰���롣\n");
}

// ����������
void chainingSearch(const HashSlot table[], const char* tel, int (*hashFunction)(const char*)) {
    int hash = hashFunction(tel);
    const HashSlot* slot = &table[hash];
    while (slot != NULL) {
        if (slot->status == 1 && strcmp(slot->data.tel, tel) == 0) {
            printf("���ҳɹ����û���Ϣ��\n");
            printf("�绰���룺%s\n", slot->data.tel);
            printf("�û�����%s\n", slot->data.name);
            printf("סַ��%s\n", slot->data.address);
            return;
        }
        slot = slot->next;
    }
    printf("δ�ҵ�ƥ��ĵ绰���롣\n");
}

int main() {
    HashSlot table[TABLE_SIZE];

    // ��ʼ��ɢ�б�
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].status = 0;
        table[i].next = NULL;
    }

    // �û���¼
    UserInfo users[] = {
        {"1234567890", "������", "Beijing"},
        {"9876543210", "������", "Shanghai"},
        {"1111111111", "�Ⱦ͸�", "Guangzhou"},
        {"2222222222", "����", "Shenzhen"},
        {"3333333333", "����", "Chengdu"}
    };
    int userCount = sizeof(users) / sizeof(users[0]);

    // ʹ������̽�ⷨ�����û���¼
    for (int i = 0; i < userCount; i++) {
        linearProbingInsert(table, &users[i], hashFunction1);
    }

    // ʹ��ƽ��̽�ⷨ�����û���¼
    for (int i = 0; i < userCount; i++) {
        quadraticProbingInsert(table, &users[i], hashFunction2);
    }

    // ʹ�������������û���¼
    for (int i = 0; i < userCount; i++) {
        chainingInsert(table, &users[i], hashFunction1);
    }

    // ʹ������̽�ⷨ�����û���¼
    for (int i = 0; i < userCount; i++) {
        linearProbingSearch(table, users[i].tel, hashFunction1);
    }

    // ʹ��ƽ��̽�ⷨ�����û���¼
    for (int i = 0; i < userCount; i++) {
        quadraticProbingSearch(table, users[i].tel, hashFunction2);
    }

    // ʹ�������������û���¼
    for (int i = 0; i < userCount; i++) {
        chainingSearch(table, users[i].tel, hashFunction1);
    }
    

    return 0;
}

