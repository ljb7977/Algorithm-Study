#include <cstdio>
#include <algorithm>

using namespace std;

long long zero[50]={1}, one[50]={0, 1};

int main() {
    int t, i;

    for(i=2;i<=40;i++){
        zero[i]=zero[i-1]+zero[i-2];
        one[i]=one[i-1]+one[i-2];
    }

    scanf("%d", &t);

    for(i=0;i<t;i++){
        int n;
        scanf("%d", &n);
        printf("%d %d\n", zero[n], one[n]);
    }

    return 0;
}