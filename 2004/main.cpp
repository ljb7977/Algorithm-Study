#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int calc(int a, int b, int m)
{
    int ret=0;
    long long t = m;
    while(t <= b){
        ret += b/t-(a/t+(a%t!=0))+1;
        t*=m;
    }
    return ret;
}

int main() {
    int n, m;
    int five=0, two=0;
    scanf("%d %d", &n, &m);
    m = min(m, n-m);

    five = calc(n-m+1, n, 5)-calc(1, m, 5);
    two = calc(n-m+1, n, 2)-calc(1, m, 2);

    printf("%d", min(five, two));
    return 0;
}
