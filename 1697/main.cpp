#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

queue<int> Q;
int n, k;
int visited[100010];
bool P[101][101];

void bfs(int start, int end)
{
    Q.push(start);
    while(!Q.empty()){
        int cur = Q.front(); Q.pop();
        int cand[3] = {cur-1, cur+1, cur*2};
        for (int i=0;i<3;i++){
            int next = cand[i];
            if(next < 0 || next > 100000)
                continue;
            if(visited[next] != -1)
                continue;
            visited[next] = visited[cur] + 1;
            Q.push(next);
        }
    }
}


int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d %d", &n, &k);
    memset(visited, -1, sizeof(visited));
    visited[n] = 0;
    bfs(n, k);
    printf("%d", visited[k]);
    return 0;
}