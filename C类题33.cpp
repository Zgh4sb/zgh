#include <stdio.h>
#include <stdlib.h>

struct Node {
    char data; // 数据
    float freq; // 频率
    struct Node* left; // 左子节点
    struct Node* right; // 右子节点
};

struct HuffmanCode {
    char data; // 数据
    char* code; // 哈夫曼编码
};

// 创建节点
struct Node* createNode(char data, float freq) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 构建哈夫曼树
struct Node* buildHuffmanTree(struct Node** nodes, int n) {
    while (n > 1) {
        int min1 = 0, min2 = 1;
        if (nodes[min1]->freq > nodes[min2]->freq) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }

        for (int i = 2; i < n; i++) {
            if (nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->freq < nodes[min2]->freq) {
                min2 = i;
            }
        }

        struct Node* newNode = createNode('\0', nodes[min1]->freq + nodes[min2]->freq);
        newNode->left = nodes[min1];
        newNode->right = nodes[min2];

        nodes[min1] = newNode;
        nodes[min2] = nodes[n - 1];
        n--;
    }

    return nodes[0];
}

// 生成哈夫曼编码
void generateHuffmanCode(struct Node* root, char* code, int index, struct HuffmanCode* huffmanCodes) {
    if (root->left) {
        code[index] = '0';
        generateHuffmanCode(root->left, code, index + 1, huffmanCodes);
    }

    if (root->right) {
        code[index] = '1';
        generateHuffmanCode(root->right, code, index + 1, huffmanCodes);
    }

    if (!root->left && !root->right) {
        huffmanCodes[root->data - 'A'].data = root->data;
        huffmanCodes[root->data - 'A'].code = (char*)malloc((index + 1) * sizeof(char));
        for (int i = 0; i <= index; i++) {
            huffmanCodes[root->data - 'A'].code[i] = code[i];
        }
        huffmanCodes[root->data - 'A'].code[index + 1] = '\0';
    }
}

int main() {
    float frequencies[5];
    printf("输入字符 'A' 到 'E' 的频率:\n");
    for (int i = 0; i < 5; i++) {
        printf("'%c' 的频率: ", 'A' + i);
        scanf("%f", &frequencies[i]);
    }

    struct Node** nodes = (struct Node**)malloc(5 * sizeof(struct Node*));
    for (int i = 0; i < 5; i++) {
        nodes[i] = createNode('A' + i, frequencies[i]);
    }

    struct Node* root = buildHuffmanTree(nodes, 5);

    char code[100];
    struct HuffmanCode huffmanCodes[5];
    for (int i = 0; i < 5; i++) {
        huffmanCodes[i].code = NULL;
    }

    generateHuffmanCode(root, code, 0, huffmanCodes);

    printf("哈夫曼编码:\n");
    for (int i = 0; i < 5; i++) {
        printf("'%c': %s\n", huffmanCodes[i].data, huffmanCodes[i].code);
        free(huffmanCodes[i].code);
    }

    free(nodes);

    return 0;
}

