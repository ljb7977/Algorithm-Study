#include <cstdio>
#include <algorithm>

using namespace std;

int D[21][110];
int happiness[21];
int cost[21];

int main() {
//    freopen("input.txt", "r", stdin);
    int n;
    int i, j;
    scanf("%d", &n);
    for(i=1;i<=n;i++){
        scanf("%d", &cost[i]);
    }
    for(i=1;i<=n;i++){
        scanf("%d", &happiness[i]);
    }

    for(i=1;i<=n;i++){
        for(j=0;j<=99;j++){
            int m = 0;
            if(j >= cost[i]){
                D[i][j] = max(D[i-1][j-cost[i]]+happiness[i], D[i-1][j]);
            } else {
                D[i][j] = D[i-1][j];
            }
        }
    }

    printf("%d", D[n][99]);

    return 0;
}