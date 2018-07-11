#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<pair<short, short> > cost[5010]; //<dest, cost>

bool find_and_erase(vector<pair<short, short> >& D, int dest)
{
    vector<pair<short, short> >::iterator it;
    for(it = D.begin(); it != D.end(); it++){
        if((*it).first == dest){
            D.erase(it);
            return true;
        }
    }
    return false;
}

int dijk(int n, int start, int start_cost)
{
    priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >,
            greater< pair<int, pair<int, int> > > > pq;

    int dist[5010];
    vector<pair<short, short> > D[5010];

    for(int i = 1; i<=n; i++){
        dist[i] = INT_MAX;
        D[i] = cost[i];
    }

    pq.push(make_pair(start_cost, make_pair(1, start)));
    dist[start] = start_cost;

    while(!pq.empty()){
        pair<int, pair<int, int> > top = pq.top();
        int c = top.first;
        int from = top.second.first;
        int to = top.second.second;

        pq.pop();

        if(dist[to] < c) continue;

        find_and_erase(D[from], to);
        find_and_erase(D[to], from);

        for(int i = 0; i<D[to].size(); i++){
            if(D[to][i].second+c < dist[D[to][i].first]){
                dist[D[to][i].first] = D[to][i].second+c;
                pq.push(make_pair(dist[D[to][i].first], make_pair(to, D[to][i].first)));
            }
        }
    }

    return dist[1];
}

int main() {
//    freopen("input.txt", "r", stdin);
    int n, m, i;
    scanf("%d %d", &n, &m);

    for(i=0;i<m;i++){
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        cost[a].push_back(make_pair(b, c));
        cost[b].push_back(make_pair(a, d));
    }
    int mini = INT_MAX;

    for(i = 0; i<cost[1].size(); i++){
        mini = min(mini, dijk(n, cost[1][i].first, cost[1][i].second));
    }

    printf("%d", mini);

    return 0;
}