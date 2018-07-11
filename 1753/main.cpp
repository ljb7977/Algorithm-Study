#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<pair<short, short> > cost[20010]; //<dest, cost>

void dijk(int n, int start, int dist[])
{


    priority_queue<pair<int,int>, vector<pair<int, int> >,
            greater< pair<int, int> > > pq;

    dist[start] = 0;
    pq.emplace(0, start);

    while(!pq.empty()){
        pair<int, int> top = pq.top();
        int c = top.first;
        int from = top.second;
        pq.pop();

        if(dist[from] < c) continue;

        for (auto i : cost[from]) {
            if(i.second+c < dist[i.first]){
                dist[i.first] = i.second+c;
                pq.emplace(dist[i.first], i.first);
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int v, e, k;
    int i;
    int dist[20010];

    scanf("%d %d %d", &v, &e, &k);
    for(i=1;i<=v;i++){
        dist[i] = INT_MAX;
    }

    for(i=0;i<e;i++){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        cost[u].emplace_back(v, w);
    }
    dijk(v, k, dist);

    for(i=1;i<=v;i++){
        if(dist[i] == INT_MAX){
            printf("INF\n");
        } else {
            printf("%d\n", dist[i]);
        }
    }

    return 0;
}