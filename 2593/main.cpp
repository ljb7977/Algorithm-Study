#include <cstdio>
#include <queue>
#include <cstring>

#define M 101
#define N 100010

using namespace std;

typedef struct {
    int x;
    int y;
} elevator;

elevator E[M];
bool connected[M][M];
int dist[M];
int parent[M];
int n, m, a, b;
int min_dist = 0x7fffffff;
int min_path[M];

void save_min_path(int start){
    memset(min_path, 0, sizeof(min_path));
    int p = start;
    int i = 0;
    min_path[i++] = p;
    while(p != parent[p]){
        p = parent[p];
        min_path[i++] = p;
    }
}

bool can_elevator_go(int elevator_, int floor){
//    printf("e, f : %d %d\n", elevator_, floor);
    int x = E[elevator_].x;
    int y = E[elevator_].y;

    if(floor < x) return false;
    return (floor-x)%y == 0;
}

int bfs(int start)
{
    queue<int> Q;
    memset(dist, -1, sizeof(dist));
    memset(parent, -1, sizeof(parent));
    Q.push(start);
    dist[start] = 0;
    parent[start] = start;
    while(!Q.empty()){
        int current = Q.front(); Q.pop();
//        printf("current: %d\n", current);
        if(can_elevator_go(current, b)){
            return current;
        }
        for(int next = 1; next <= m; next ++){
            if(connected[current][next] && dist[next] == -1){
                Q.push(next);
                dist[next] = dist[current]+1;
                parent[next] = current;
            }
        }
    }
    return -1;
}

int main() {
//    freopen("input.txt", "r", stdin);
    int x, y;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d", &x, &y);
        E[i].x = x;
        E[i].y = y;
    }
    scanf("%d %d", &a, &b);
    for (int i = 1; i <= m; i++) {
        connected[i][i] = true;
        for (int j = i + 1; j <= m; j++) {
            //check whether i is connected with j
            x = E[i].x;
            y = E[i].y;
            for (int k = x; k <= n; k += y) {
                if(can_elevator_go(j, k)){ //i and j is connected;
                    connected[j][i] = connected[i][j] = true;
                    break;
                }
            }
        }
    }

    for(int i = 1; i<=m; i++){
        if(can_elevator_go(i, a)){
            int dest = bfs(i);
            if (dest == -1)
                break;
            if(dist[dest] < min_dist){
                min_dist = dist[dest];
                save_min_path(dest);
            }
        }
    }
    if (min_dist == 0x7fffffff){
        printf("-1");
        return 0;
    }
    min_dist++;
    printf("%d\n", min_dist);
    for(int i = min_dist-1; i >= 0; i--){
        printf("%d\n", min_path[i]);
    }

    return 0;
}