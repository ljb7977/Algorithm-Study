#include <cstdio>
#include <algorithm>

int D[1010]={0,1,2};

using namespace std;

int main() {
    int n, i;
    scanf("%d", &n);

    if(i == 2){
        printf("%d", D[i]);
        return 0;
    }

    for(i=3;i<=n;i++){
        D[i] = (D[i-1]+D[i-2])%10007;
    }

    printf("%d", D[n]);

    return 0;
}