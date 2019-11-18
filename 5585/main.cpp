#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int coin[] = {500, 100, 50, 10, 5, 1};

int main() {
    int n, i;
    scanf("%d", &n);
    int sum = 0;
    n = 1000-n;
    for(i=0;i<6;i++){
        sum += n/coin[i];
        n -= n/coin[i]*coin[i];
    }
    printf("%d", sum);

    return 0;
}
