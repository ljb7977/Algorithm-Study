#include <cstdio>
#include <algorithm>

int x[10] = {0, 1, 2, 4};

using namespace std;

int main() {
    int n, i, t;
    for(i=4;i<11;i++){
        x[i] = x[i-1]+x[i-2]+x[i-3];
    }

    scanf("%d", &t);
    for(i=0;i<t;i++){
        scanf("%d", &n);

        printf("%d\n", x[n]);
    }

    return 0;
}