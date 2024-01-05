#include <stdio.h>
#include <stdlib.h>
#define MAX_N 100
#define MAX_M 100

typedef struct {
    int start;
    int end;
    int duration;
} Arrow;

int N, M;
Arrow arrows[MAX_M];
int in_degree[MAX_N];
int out_degree[MAX_N];
int earliest_start[MAX_N];
int latest_start[MAX_N];

void find_critical_paths(int node, int path[], int depth)
{
    path[depth] = node;
    
    // 到达终点节点，输出路径
    if (node == N - 1) {
        for (int i = 0; i <= depth; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
        return;
    }
    
    for (int i = 0; i < M; i++) {
        if (arrows[i].start == node) {
            find_critical_paths(arrows[i].end, path, depth + 1);
        }
    }
}

void topological_sort()
{
    int queue[MAX_N];
    int head = 0, tail = 0;
    
    // 将入度为0的节点加入队列
    for (int i = 0; i < N; i++) {
        if (in_degree[i] == 0) {
            queue[tail++] = i;
        }
    }
    
    while (head < tail) {
        int current_node = queue[head++];
        
        for (int i = 0; i < M; i++) {
            if (arrows[i].start == current_node) {
                int next_node = arrows[i].end;
                
                // 更新最早开始时间
                if (earliest_start[next_node] < earliest_start[current_node] + arrows[i].duration) {
                    earliest_start[next_node] = earliest_start[current_node] + arrows[i].duration;
                }
                
                // 更新入度
                in_degree[next_node]--;
                
                // 如果入度为0，加入队列
                if (in_degree[next_node] == 0) {
                    queue[tail++] = next_node;
                }
            }
        }
    }
}

int main()
{
    // 读取输入数据
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &(arrows[i].start), &(arrows[i].end), &(arrows[i].duration));
        in_degree[arrows[i].end]++;
        out_degree[arrows[i].start]++;
    }
    
    // 初始化最早开始时间和最晚开始时间
    for (int i = 0; i < N; i++) {
        earliest_start[i] = 0;
        latest_start[i] = 0x7fffffff;
    }
    
    // 拓扑排序
    topological_sort();
    
    // 更新最晚开始时间
    for (int i = N - 1; i >= 0; i--) {
        int current_node = i;
        for (int j = 0; j < M; j++) {
            if (arrows[j].end == current_node) {
                int prev_node = arrows[j].start;
                
                // 更新最晚开始时间
                if (latest_start[prev_node] > latest_start[current_node] - arrows[j].duration) {
                    latest_start[prev_node] = latest_start[current_node] - arrows[j].duration;
                }
            }
        }
    }
    
    // 找到关键路径
    int path[MAX_N];
    find_critical_paths(0, path, 0);
    
    return 0;
}
