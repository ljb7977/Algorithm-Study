#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
    int a, b, c, n;
    scanf("%d %d %d %d", &a, &b, &c, &n);

    for(int i = 0; i <= n/a; i++){
        int t = n-i*a;
        for(int j = 0; j <= t/b; j++){
            int s = t-j*b;
            if(s%c == 0){
                printf("1");
                return 0;
            }
        }
    }
    printf("0");
    return 0;
}
