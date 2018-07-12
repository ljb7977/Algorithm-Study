#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>

#define MAX_N 1000000
using namespace std;

long long numbers[MAX_N+1];
long long tree[MAX_N+1];
int n;

long long sum(int pos)
{
    long long ret = 0;
    while(pos > 0){
        ret += tree[pos];
        pos &= (pos-1);
    }
    return ret;
}

void add(int pos, long long val)
{
    while(pos <= n){
        tree[pos] += val;
        pos += (pos & -pos);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
    int i;
    int m, k;
    scanf("%d %d %d", &n, &m, &k);
    for(i=1;i<=n;i++){
        scanf("%lld", &numbers[i]);
        add(i, numbers[i]);
    }
    for(i=0;i<m+k;i++){
        int a,b;
        long long c;
        scanf("%d %d %lld", &a, &b, &c);
        if(a == 1){
            add(b, c-numbers[b]);
            numbers[b] = c;
        } else if (a == 2){
            printf("%lld\n", sum((int)c)-sum(b-1));
        }
    }

    return 0;
}