#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

queue<pair<int, int>> Q;
int n, m;
int visited[101][101];
bool P[101][101];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};

void bfs(pair<int, int> start)
{
    Q.push(start);
    while(!Q.empty()){
        pair<int, int> cur = Q.front(); Q.pop();
        int x, y; tie(y, x) = cur;
        for(int i=0;i<4;i++){
            int new_x = x+dx[i];
            int new_y = y+dy[i];
            if(new_x >= m || new_x < 0 || new_y >= n || new_y < 0)
                continue;
            if(!P[new_y][new_x])
                continue;
            if(visited[new_y][new_x] != -1)
                continue;
            visited[new_y][new_x] = visited[y][x] + 1;
            Q.emplace(new_y, new_x);
        }
    }
}


int main() {
//    freopen("input.txt", "r", stdin);
    char c;
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++){
        scanf("%c", &c);
        for(int j = 0; j < m; j++){
            scanf("%c", &c);
            P[i][j] = c - '0';
        }
    }
    memset(visited, -1, sizeof(visited));
    visited[0][0] = 1;
    bfs(make_pair(0, 0));
    printf("%d", visited[n-1][m-1]);
    return 0;
}