#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

int radix[10];

int power(int n){
    int m = 1;
    for(int i =0;i<n;i++){
        m *= 10;
    }
    return m;
}

int numberAt(int n, int i){
    char number[10];
    sprintf(number, "%d", n);
    return (int)(number[i]-'0');
}

int main() {
    int i, n, k;
    long long m = 9;
    int sum = 0;

    for(i = 1; i<9; i++){
        sum += i*m;
        m*=10;
        radix[i] = sum;
//        printf("%d %d\n", i, sum);
    }

    scanf("%d %d", &n, &k);

    for(i=1;i<=8;i++){
        if(radix[i] > k)
            break;
    }
    k -= radix[i-1]+1;
    int d = k/i;
    int r = k%i;

    int num = power(i-1)+d;

    if(num > n){
        printf("-1");
        return 0;
    }

    printf("%d", numberAt(num, r));

    return 0;
}
