#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int parent[200010];
int root[200010];
vector<int> child[200010];

void dfs(int node, int r)
{
    for(auto &i : child[node]){
        root[i] = r;
        dfs(i, r);
    }
}

void update(int n)
{
    child[parent[n]].erase(find(child[parent[n]].begin(), child[parent[n]].end(), n));
    parent[n] = 0;
    dfs(n, n);
}

int main() {
    int n, q, i;
//    freopen("input.txt", "r", stdin);

    scanf("%d %d", &n, &q);
    root[1]=1;
    for(i=1;i<=n-1;i++){
        int a;
        scanf("%d", &a);
        parent[i+1] = a;
        child[a].push_back(i+1);
        root[i+1] = 1;
    }

    for(i=0;i<n-1+q;i++){
        int x, b, c, d;
        scanf("%d", &x);
        if(x == 0){
            scanf("%d", &b);

            root[b] = b;
            update(b);
        } else if (x == 1){
            scanf("%d %d", &c, &d);
            if(root[c] == root[d]){
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }

    return 0;
}