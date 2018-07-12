#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
using namespace std;

set<int> s;

int main() {
    int n, m;
    int count[100010];

    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; i++){
        count[i] = i-1;
    }

    for(int i = 0; i<m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        count[x]++;
        count[y]--;
    }
    for(int i = 1; i<=n; i++){
        s.insert(count[i]);
    }
    if(s.size() != n){
        printf("-1");
    } else{
        for(int i = 1; i<=n; i++){
            printf("%d ", count[i]+1);
        }
    }

    return 0;
}