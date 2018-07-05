#include <cstdio>
#include <algorithm>

using namespace std;

int R[1010], G[1010], B[1010];
int DR[1010], DG[1010], DB[1010];

int main() {
    int n, i;
    scanf("%d", &n);

    for(i=1;i<=n;i++){
        scanf("%d %d %d", &R[i], &G[i], &B[i]);
    }

    for(i=1;i<=n;i++){
        DR[i] = min(DG[i-1], DB[i-1])+R[i];
        DG[i] = min(DR[i-1], DB[i-1])+G[i];
        DB[i] = min(DR[i-1], DG[i-1])+B[i];
    }

    int m = min(DR[n], DG[n]);
    m = min(m, DB[n]);

    printf("%d", m);

    return 0;
}