#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
//    freopen("input.txt", "r", stdin);
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int> P(n+1, 0);
    for(int i = 0; i < n; ++i)
        scanf("%d", &P[i]);

    sort(P.begin(), P.end()); //asc

    vector<long long> DP(n+1, 0);
    vector<long long> inc(m, 0);

    for(int k=1; k<=n; k++){
        inc[(k-1)%m] += P[k];
        DP[k] = DP[k-1] + inc[(k-1)%m];
    }
    for(int k=1; k<=n; k++)
        printf("%lld ", DP[k]);

    return 0;
}
