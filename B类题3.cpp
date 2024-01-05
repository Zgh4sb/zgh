#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 100
#define MAX_M 100

int maze[MAX_N][MAX_M];
int visited[MAX_N][MAX_M];
int N, M;

// 递归算法
int recursive_shortest_path(int row, int col, int end_row, int end_col)
{
    // 判断当前位置是否为终点
    if (row == end_row && col == end_col) {
        return 0;
    }
    
    // 标记当前位置已经访问过
    visited[row][col] = 1;
    
    // 定义四个方向的移动向量
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    int min_steps = 0x7fffffff;
    
    // 递归遍历四个方向
    for (int i = 0; i < 4; i++) {
        int new_row = row + directions[i][0];
        int new_col = col + directions[i][1];
        
        // 判断新位置是否越界，并且是可走的路
        if (new_row >= 0 && new_row < N && new_col >= 0 && new_col < M && maze[new_row][new_col] == 0 && visited[new_row][new_col] == 0) {
            int steps = recursive_shortest_path(new_row, new_col, end_row, end_col);
            
            // 更新最小步数
            if (steps != -1) {
                min_steps = (steps + 1 < min_steps) ? steps + 1 : min_steps;
            }
        }
    }
    
    // 恢复当前位置的标记
    visited[row][col] = 0;
    
    // 如果没有找到路径，则返回-1
    if (min_steps == 0x7fffffff) {
        return -1;
    }
    
    return min_steps;
}

// BFS算法
typedef struct {
    int row;
    int col;
    int steps;
} Node;

int bfs_shortest_path(int start_row, int start_col, int end_row, int end_col)
{
    // 定义四个方向的移动向量
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // 创建一个队列，用于广度优先搜索
    Node queue[N * M];
    int head = 0, tail = 0;
    queue[tail++] = (Node){start_row, start_col, 0};
    
    // 标记起点已访问
    visited[start_row][start_col] = 1;
    
    while (head < tail) {
        Node current = queue[head++];
        
        // 判断当前位置是否为终点
        if (current.row == end_row && current.col == end_col) {
            return current.steps;
        }
        
        for (int i = 0; i < 4; i++) {
            int new_row = current.row + directions[i][0];
            int new_col = current.col + directions[i][1];
            
            // 判断新位置是否越界，并且是可走的路
            if (new_row >= 0 && new_row < N && new_col >= 0 && new_col < M && maze[new_row][new_col] == 0 && visited[new_row][new_col] == 0) {
                queue[tail++] = (Node){new_row, new_col, current.steps + 1};
                visited[new_row][new_col] = 1;
            }
        }
    }
    
    // 如果没有找到路径，则返回-1
    return -1;
}

int main()
{
    // 读取输入数据
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &maze[i][j]);
        }
    }
    memset(visited, 0, sizeof(visited));
    int start_row, start_col, end_row, end_col;
    scanf("%d %d %d %d", &start_row, &start_col, &end_row, &end_col);
    start_row--; start_col--; end_row--; end_col--;
    
    // 使用递归算法求解最短路径
    int recursive_steps = recursive_shortest_path(start_row, start_col, end_row, end_col);
    
    // 使用BFS算法求解最短路径
    memset(visited, 0, sizeof(visited));
    int bfs_steps = bfs_shortest_path(start_row, start_col, end_row, end_col);
    
    // 输出结果
    printf("递归结果：%d\nBFS结果：%d\n", recursive_steps, bfs_steps);
    
    return 0;
}
