#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<bool> visited(100001, false);
int n, m;

void dfs(const vector<vector<uint16_t>>& adj, int start)
{
    stack<int> stack;
    stack.push(start);
    visited[start] = true;
    while(!stack.empty()){
        int now = stack.top(); stack.pop();
        //actually visit here
        auto it = adj[now].begin();
        for(int i=1; i<=n; i++){
            if(now == i) continue;
            if(it != adj[now].end() && *it == i) {
                it++;
                continue;
            }
            if(visited[i]) continue;

            stack.push(i);
            visited[i] = true;
        }
    }
}

int dfs_helper(const vector<vector<uint16_t>>& adj)
{
    int group = 0;
    for(int i = 1; i<=n; i++){
        if(visited[i])
            continue;

        dfs(adj, i);
        ++group;
    }
    return group-1;
}

int main()
{
//    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin >> n >> m;
    vector<vector<uint16_t>> adj(n+1);

    for(int i = 0; i<m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for(int i = 1; i<=n; i++){
        sort(adj[i].begin(), adj[i].end());
    }

    cout << dfs_helper(adj);

}