#include <bits/stdc++.h>
using namespace std;

vector<bool> visited(100001, false);

int n = 5;

void dfs(const vector<vector<int>>& adj, int start)
{
    queue<int> Q;
    Q.push(start);
    visited[start] = true;
    while(!Q.empty()){
//        cout << "Q size: " << Q.size() << "\n";
        int now = Q.front(); Q.pop();
//        visited[now] = true;
        cout << "visited: " << now << "\n";

        for(auto next : adj[now]){
            if(visited[next]) continue;

            visited[next] = true;
            Q.push(next);
        }
    }
}

int main()
{
    vector<vector<int>> adj(6);
    adj[1] = {2, 3};
    adj[2] = {1, 3, 4, 5};
    adj[3] = {1, 2};
    adj[4] = {2, 5};
    adj[5] = {2, 4};

    dfs(adj, 1);

    return 0;
}