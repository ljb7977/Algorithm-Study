#include <cstdio>
#include <algorithm>

int x[1000000];

using namespace std;

int main() {
    int n, i;
    scanf("%d", &n);

    x[1] = 0;

    for(i=2;i<=n;i++){
        int t = x[i-1];
        if(i%2 == 0){
            t = min(t, x[i/2]);
        }
        if(i%3 == 0){
            t = min(t, x[i/3]);
        }
        x[i] = t+1;
    }
    printf("%d", x[n]);

    return 0;
}