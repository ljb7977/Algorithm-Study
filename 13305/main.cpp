#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int dist[100010];
int cost[100010];
long long min_cost;
long long total;

int main() {
    int n, i;
    scanf("%d", &n);
    for(i=0;i<n-1;i++){
        scanf("%d", &dist[i]);
    }
    for(i=0;i<n;i++) {
        scanf("%d", &cost[i]);

    }
    min_cost = cost[0];
    total += min_cost*dist[0];
    for(i=1;i<n-1;i++){
        min_cost = min(min_cost, (long long)cost[i]);
        total += min_cost*dist[i];
    }

    printf("%lld", total);

    return 0;
}
