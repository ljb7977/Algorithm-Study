#include <cstdio>

int main() {
    long long n, f, t=0;
    scanf("%lld", &f);
    scanf("%lld", &n);

    switch(f){
        case 1:
            t = 8*n;
            break;
        case 5:
            t = 8*n+4;
            break;
        default:
            t = n*4 + (n%2? 5-f : f-1);
    }

    printf("%lld", t);

    return 0;
}