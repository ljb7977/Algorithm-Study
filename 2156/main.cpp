#include <cstdio>
#include <algorithm>

int D[10010][2], score[10010];

using namespace std;

int main() {
    int n, i;
    scanf("%d", &n);
    for(i=1;i<=n;i++){
        scanf("%d", &score[i]);
    }

    D[1][0] = score[1];
    D[2][0] = score[2];
    D[2][1] = score[1]+score[2];

    for(i=3;i<=n;i++){
        D[i][0] = max({D[i-3][0], D[i-3][1], D[i-2][0], D[i-2][1]})+score[i];
        D[i][1] = D[i-1][0]+score[i];
    }

    int m = 0;
    for(i=1;i<=n;i++){
        m = max({m, D[i][0], D[i][1]});
    }

    printf("%d", m);

    return 0;
}