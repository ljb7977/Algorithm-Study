#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

queue<pair<int, int>> Q;
int n, m, h;
char P[100][100];
char original[100][100];
//bool visited[110][110];
int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};

void bfs(int x, int y, char color)
{
    P[y][x] = ' ';
    Q.emplace(x, y);
    while(!Q.empty()){
        tie(x, y) = Q.front(); Q.pop();
        for (int i=0; i<4; i++){
            int new_x = x+dx[i];
            int new_y = y+dy[i];

            if(new_y < 0 || new_y >=n || new_x < 0 || new_x >= n)
                continue;

            if(P[new_y][new_x] == ' ')
                continue;

            if(color != P[new_y][new_x])
                continue;

            P[new_y][new_x] = ' ';
            Q.emplace(new_x, new_y);
        }
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int cnt = 0, cnt2= 0;

    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("\n");
        for(int j=0;j<n;j++){
            scanf("%c", &original[i][j]);
        }
    }

    memcpy(P, original, sizeof(original));

    for(int i = 0; i <n; i ++){
        for(int j=0; j<n; j++){
            if(P[i][j] != ' '){
                bfs(j, i, P[i][j]);
                cnt++;
            }
        }
    }

    memcpy(P, original, sizeof(original));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(P[i][j] == 'G')
                P[i][j] = 'R';
        }
    }

    for(int i = 0; i <n; i ++){
        for(int j=0; j<n; j++){
            if(P[i][j] != ' '){
                bfs(j, i, P[i][j]);
                cnt2++;
            }
        }
    }
    printf("%d %d", cnt, cnt2);

    return 0;
}