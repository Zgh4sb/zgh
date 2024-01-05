#include <stdio.h>

#define MAX_NODES 100

struct Edge {
    int src, dest, weight;
};

// 拓扑排序递归辅助函数
void topologicalSortUtil(int node, int visited[], int stack[], int *top, struct Edge edges[], int edgeCount, int est[]) {
    visited[node] = 1;

    // 遍历与当前节点相连的边
    for (int i = 0; i < edgeCount; i++) {
        if (edges[i].src == node && !visited[edges[i].dest]) {
            topologicalSortUtil(edges[i].dest, visited, stack, top, edges, edgeCount, est);
        }
    }

    stack[(*top)++] = node;
}

// 拓扑排序
void topologicalSort(int nodes, struct Edge edges[], int edgeCount, int est[]) {
    int visited[MAX_NODES] = {0};
    int stack[MAX_NODES];
    int top = 0;

    // 对每个未访问的节点进行拓扑排序
    for (int i = 0; i < nodes; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, stack, &top, edges, edgeCount, est);
        }
    }
}

// 计算最早开始时间（earliest start time）和最晚开始时间（latest start time）
void calculateTime(int nodes, struct Edge edges[], int edgeCount, int est[], int lst[]) {
    topologicalSort(nodes, edges, edgeCount, est);

    // 初始化最晚开始时间为最后一个节点的最早开始时间
    for (int i = 0; i < nodes; i++) {
        lst[i] = est[nodes-1];
    }

    // 逆序遍历节点
    for (int i = nodes-2; i >= 0; i--) {
        // 遍历与当前节点相连的边
        for (int j = 0; j < edgeCount; j++) {
            if (edges[j].src == i) {
                int successor = edges[j].dest;
                int weight = edges[j].weight;
                // 更新最晚开始时间
                if (lst[i] > lst[successor] - weight) {
                    lst[i] = lst[successor] - weight;
                }
            }
        }
    }
}

// 计算关键路径数量
int countCriticalPaths(int nodes, struct Edge edges[], int edgeCount) {
    int est[MAX_NODES] = {0};
    int lst[MAX_NODES] = {0};
    int criticalPathCount = 0;

    calculateTime(nodes, edges, edgeCount, est, lst);

    // 遍历每条边
    for (int i = 0; i < edgeCount; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;
        // 如果最早开始时间和最晚开始时间之差等于边的权重，则为关键路径
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

    printf("关键路径数量: %d\n", criticalPathCount);

    return 0;
}


