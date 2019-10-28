#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
using namespace std;

bool graph[1010][1010];
bool visit[1010];
bool discover[1010];

int n, m, v;

queue<int> Q;
stack<int> S;

void bfs(int v)
{
    int i, j;
    Q.push(v);
    discover[Q.front()]=1;
    while(!Q.empty()){
        printf("%d ", Q.front());
        for(i=1;i<=n;i++){
            if(graph[Q.front()][i]){
                if(!discover[i]){
                    Q.push(i);
                    discover[i]=1;
                }
            }
        }
        Q.pop();
    }
}

void dfs(int v)
{
    int i, t;
    S.push(v);
    while(!S.empty()){
        t=S.top();
        if(!visit[t]){
            printf("%d ", t);
            visit[t]=1;
        }
        i=1;
        while(i<=n){
            if(graph[t][i]){
                if(!visit[i]){
                    S.push(i);
                    break;
                }
            }
            i++;
        }
        if(i>n)
            S.pop();
    }
}

int main ()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d %d", &n, &m, &v);
    int i;

    for(i=0; i<m; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
        graph[b][a] = 1;
    }

    dfs(v);
    printf("\n");
    bfs(v);

    return 0;
}
