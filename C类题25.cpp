#include <stdio.h>
#include <string.h>
#include <ctype.h>

void formatSentence(char *input) {
    int len = strlen(input);
    
    // �Ƴ�ǰ���ո�
    while (len > 0 && isspace(input[0])) {
        memmove(input, input + 1, len);
        len--;
    }
    
    // �Ƴ�β���ո�
    while (len > 0 && isspace(input[len - 1])) {
        input[len - 1] = '\0';
        len--;
    }
    
    // �Ƴ����Ӽ����Ŀռ� 
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
    
    // �������� 
    printf("�����ʼ����: ");
    fgets(input, sizeof(input), stdin);
    
    formatSentence(input);
    
    // ������ 
    printf("��ʽ����: %s\n", input);
    
    return 0;
}
