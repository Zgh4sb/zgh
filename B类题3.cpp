#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 100
#define MAX_M 100

int maze[MAX_N][MAX_M];
int visited[MAX_N][MAX_M];
int N, M;

// �ݹ��㷨
int recursive_shortest_path(int row, int col, int end_row, int end_col)
{
    // �жϵ�ǰλ���Ƿ�Ϊ�յ�
    if (row == end_row && col == end_col) {
        return 0;
    }
    
    // ��ǵ�ǰλ���Ѿ����ʹ�
    visited[row][col] = 1;
    
    // �����ĸ�������ƶ�����
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    int min_steps = 0x7fffffff;
    
    // �ݹ�����ĸ�����
    for (int i = 0; i < 4; i++) {
        int new_row = row + directions[i][0];
        int new_col = col + directions[i][1];
        
        // �ж���λ���Ƿ�Խ�磬�����ǿ��ߵ�·
        if (new_row >= 0 && new_row < N && new_col >= 0 && new_col < M && maze[new_row][new_col] == 0 && visited[new_row][new_col] == 0) {
            int steps = recursive_shortest_path(new_row, new_col, end_row, end_col);
            
            // ������С����
            if (steps != -1) {
                min_steps = (steps + 1 < min_steps) ? steps + 1 : min_steps;
            }
        }
    }
    
    // �ָ���ǰλ�õı��
    visited[row][col] = 0;
    
    // ���û���ҵ�·�����򷵻�-1
    if (min_steps == 0x7fffffff) {
        return -1;
    }
    
    return min_steps;
}

// BFS�㷨
typedef struct {
    int row;
    int col;
    int steps;
} Node;

int bfs_shortest_path(int start_row, int start_col, int end_row, int end_col)
{
    // �����ĸ�������ƶ�����
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // ����һ�����У����ڹ����������
    Node queue[N * M];
    int head = 0, tail = 0;
    queue[tail++] = (Node){start_row, start_col, 0};
    
    // �������ѷ���
    visited[start_row][start_col] = 1;
    
    while (head < tail) {
        Node current = queue[head++];
        
        // �жϵ�ǰλ���Ƿ�Ϊ�յ�
        if (current.row == end_row && current.col == end_col) {
            return current.steps;
        }
        
        for (int i = 0; i < 4; i++) {
            int new_row = current.row + directions[i][0];
            int new_col = current.col + directions[i][1];
            
            // �ж���λ���Ƿ�Խ�磬�����ǿ��ߵ�·
            if (new_row >= 0 && new_row < N && new_col >= 0 && new_col < M && maze[new_row][new_col] == 0 && visited[new_row][new_col] == 0) {
                queue[tail++] = (Node){new_row, new_col, current.steps + 1};
                visited[new_row][new_col] = 1;
            }
        }
    }
    
    // ���û���ҵ�·�����򷵻�-1
    return -1;
}

int main()
{
    // ��ȡ��������
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
    
    // ʹ�õݹ��㷨������·��
    int recursive_steps = recursive_shortest_path(start_row, start_col, end_row, end_col);
    
    // ʹ��BFS�㷨������·��
    memset(visited, 0, sizeof(visited));
    int bfs_steps = bfs_shortest_path(start_row, start_col, end_row, end_col);
    
    // ������
    printf("�ݹ�����%d\nBFS�����%d\n", recursive_steps, bfs_steps);
    
    return 0;
}
