#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>

using namespace std;

int x[100010], y[100010];

set<int> x_set, y_set;

int main() {
    int n, i;
    scanf("%d", &n);

    for(i=0;i<n;i++){
        scanf("%d %d", &x[i], &y[i]);
    }

    sort(x, x+n);
    sort(y, y+n);

    for(i=1;i<n;i++){
        if(x[i-1] == x[i]){
            x_set.insert(x[i]);
        }
    }
    for(i=1;i<n;i++){
        if(y[i-1] == y[i]){
            y_set.insert(y[i]);
        }
    }

    printf("%d", x_set.size()+y_set.size());

    return 0;
}