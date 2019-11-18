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
    pq.push(make_pair(0, start));
//    pq.emplace(0, start);

    while(!pq.empty()){
        pair<int, int> top = pq.top();
        int c = top.first;
        int from = top.second;
        pq.pop();

        if(dist[from] < c) continue;

        for (int i = 0; i < cost[from].size(); i++){
            pair<int, int> p = cost[from][i];
            if(p.second+c < dist[p.first]){
                dist[p.first] = p.second+c;
                pq.push(make_pair(dist[p.first], p.first));
            }
        }
    }
}

int main() {
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
        cost[u].push_back(make_pair(v, w));
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