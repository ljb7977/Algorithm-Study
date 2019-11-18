#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

int sieve[10010];

int main() {
    int t, n, l;
    int P[100];
    for(int i = 2; i <= 100; i++){
        if(sieve[i])
            continue;
        for(int j = 2; i*j<=10000; j++){
            sieve[i*j] = true;
        }
    }

    scanf("%d", &t);
    for(int i = 1; i<=t; i++){
        scanf("%d %d", &n, &l);
        memset(P, 0, 100);
        for(int j = 0; j<l; j++){
            scanf("%d", &P[j]);
        }
        for(int j = 2; j <= n; j++){
            if(sieve[j])
                continue;
            if(P[0] % j != 0)
                continue;
            for(int k = 0; k < l; k++){

            }
        }

    }
    return 0;
}