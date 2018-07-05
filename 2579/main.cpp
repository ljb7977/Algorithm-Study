#include <cstdio>
#include <algorithm>

int D[310][2], score[310];

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
        D[i][0] = max(D[i-2][0], D[i-2][1])+score[i];
        D[i][1] = D[i-1][0]+score[i];
    }

    printf("%d", max(D[n][0], D[n][1]));

    return 0;
}