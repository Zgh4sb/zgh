#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#define MAX_VERTICES 1000
#define MAX_EDGES 1000

// 边结构体
typedef struct {
    int source;
    int destination;
    int weight;
} Edge;

int bellmanFord(int vertices, int edges, Edge edge[], int source, int distances[]) {
    // 初始化距离数组
    for (int i = 1; i <= vertices; i++) {
        distances[i] = INT_MAX;
    }
    distances[source] = 0;

    // 进行V-1次松弛操作
    for (int i = 1; i <= vertices - 1; i++) {
        for (int j = 0; j < edges; j++) {
            int u = edge[j].source;
            int v = edge[j].destination;
            int w = edge[j].weight;
            if (distances[u] != INT_MAX && distances[u] + w < distances[v]) {
                distances[v] = distances[u] + w;
            }
        }
    }

    // 检查是否存在负权重环
    for (int i = 0; i < edges; i++) {
        int u = edge[i].source;
        int v = edge[i].destination;
        int w = edge[i].weight;
        if (distances[u] != INT_MAX && distances[u] + w < distances[v]) {
            return -1;
        }
    }

    return 0;
}

int main() {
    int vertices, edges;
    scanf("%d %d", &vertices, &edges);

    Edge edge[MAX_EDGES];
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &edge[i].source, &edge[i].destination, &edge[i].weight);
    }

    int source;
    scanf("%d", &source);

    int distances[MAX_VERTICES];
    int result = bellmanFord(vertices, edges, edge, source, distances);

    if (result == -1) {
        printf("存在负权重环\n");
    } else {
        for (int i = 1; i <= vertices; i++) {
            if (distances[i] == INT_MAX) {
                printf("INF\n");
            } else {
                printf("%d\n", distances[i]);
            }
        }
    }

    return 0;
}

