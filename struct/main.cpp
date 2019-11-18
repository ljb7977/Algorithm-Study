#include <cstdio>
#include <queue>
#include <algorithm>
#include <tuple>
#include <climits>

using namespace std;


vector<pair<int, int>> adj[20001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
vector<int> dist(20001, INT_MAX);

int V, E;

void djikstra(int start)
{
    int now, cost;
    Q.emplace(0, start);
    dist[start] = 0;

    while(!Q.empty()){
        tie(cost, now) = Q.top(); Q.pop();

        if(cost > dist[now]) continue;

        for(auto next : adj[now]){
            int edge_cost, next_vertex;
            tie(edge_cost, next_vertex) = next;
            if(edge_cost + dist[now] < dist[next_vertex]){
                dist[next_vertex] = dist[now] + edge_cost;
                Q.emplace(dist[next_vertex], next_vertex);
            }
        }
    }
}

int main()
{
//    freopen("input.txt", "r", stdin);
    int k;
    scanf("%d %d", &V, &E);
    scanf("%d", &k);
    for(int i=0; i<E; ++i){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if(adj[u].end() == find(adj[u].begin(), adj[u].end(), make_pair(w, v))){
            adj[u].emplace_back(w, v);
        }
    }

    djikstra(k);

    for(int i = 1; i <= V; ++i){
        if(dist[i] == INT_MAX)
            printf("INF\n");
        else
            printf("%d\n", dist[i]);
    }
}