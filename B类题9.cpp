#include <stdio.h>

#define MAX_NODES 100

struct Edge {
    int src, dest, weight;
};

// ��������ݹ鸨������
void topologicalSortUtil(int node, int visited[], int stack[], int *top, struct Edge edges[], int edgeCount, int est[]) {
    visited[node] = 1;

    // �����뵱ǰ�ڵ������ı�
    for (int i = 0; i < edgeCount; i++) {
        if (edges[i].src == node && !visited[edges[i].dest]) {
            topologicalSortUtil(edges[i].dest, visited, stack, top, edges, edgeCount, est);
        }
    }

    stack[(*top)++] = node;
}

// ��������
void topologicalSort(int nodes, struct Edge edges[], int edgeCount, int est[]) {
    int visited[MAX_NODES] = {0};
    int stack[MAX_NODES];
    int top = 0;

    // ��ÿ��δ���ʵĽڵ������������
    for (int i = 0; i < nodes; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, stack, &top, edges, edgeCount, est);
        }
    }
}

// �������翪ʼʱ�䣨earliest start time��������ʼʱ�䣨latest start time��
void calculateTime(int nodes, struct Edge edges[], int edgeCount, int est[], int lst[]) {
    topologicalSort(nodes, edges, edgeCount, est);

    // ��ʼ������ʼʱ��Ϊ���һ���ڵ�����翪ʼʱ��
    for (int i = 0; i < nodes; i++) {
        lst[i] = est[nodes-1];
    }

    // ��������ڵ�
    for (int i = nodes-2; i >= 0; i--) {
        // �����뵱ǰ�ڵ������ı�
        for (int j = 0; j < edgeCount; j++) {
            if (edges[j].src == i) {
                int successor = edges[j].dest;
                int weight = edges[j].weight;
                // ��������ʼʱ��
                if (lst[i] > lst[successor] - weight) {
                    lst[i] = lst[successor] - weight;
                }
            }
        }
    }
}

// ����ؼ�·������
int countCriticalPaths(int nodes, struct Edge edges[], int edgeCount) {
    int est[MAX_NODES] = {0};
    int lst[MAX_NODES] = {0};
    int criticalPathCount = 0;

    calculateTime(nodes, edges, edgeCount, est, lst);

    // ����ÿ����
    for (int i = 0; i < edgeCount; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;
        // ������翪ʼʱ�������ʼʱ��֮����ڱߵ�Ȩ�أ���Ϊ�ؼ�·��
        if (est[dest] - lst[src] == weight) {
            criticalPathCount++;
        }
    }

    return criticalPathCount;
}

int main() {
    int nodes = 5;
    struct Edge edges[] = {
        {0, 1, 1},
        {0, 2, 5},
        {1, 3, 3},
        {2, 3, 7},
        {3, 4, 2}
    };
    int edgeCount = sizeof(edges) / sizeof(edges[0]);

    int criticalPathCount = countCriticalPaths(nodes, edges, edgeCount);

    printf("�ؼ�·������: %d\n", criticalPathCount);

    return 0;
}


