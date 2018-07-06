#include <cstdio>
#include <algorithm>

int num[100010], D[100010];

using namespace std;

int main() {
    int n, i;
    scanf("%d", &n);
    for(i=1;i<=n;i++){
        scanf("%d", &num[i]);
    }

    for(i=1;i<=n;i++){
        if(D[i-1]+num[i] > num[i]){
            D[i] = D[i-1]+num[i];
        } else {
            D[i] = num[i];
        }
    }

    printf("%d", *max_element(D+1, D+n+1));

    return 0;
}