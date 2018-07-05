#include <cstdio>
#include <algorithm>

int T[510][510];
int D[510][510];

using namespace std;

int main() {
//    freopen("input.txt", "r", stdin);
    int n, i;
    scanf("%d", &n);

    for(i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            scanf("%d", &T[i][j]);
        }
    }

    D[0][0] = T[0][0];

    for(i=1;i<n;i++){
        for(int j = 0;j<=i;j++){
            if(j == 0){
                D[i][j] = D[i-1][j]+T[i][j];
            } else if (j == i){
                D[i][j] = D[i-1][j-1]+T[i][j];
            } else {
                D[i][j] = max(D[i-1][j-1], D[i-1][j])+T[i][j];
            }
        }
    }

    int m=0;
    for(i=0;i<n;i++){
        m = max(m, D[n-1][i]);
    }
    printf("%d", m);
    return 0;
}