#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

int oven[300010];

vector<int> m;
vector<int>::iterator it;

int main() {
    int n, d, i, deep;
    scanf("%d %d", &d, &n);
    deep = d+1;
    m.push_back(2147483647);
    for(i=1;i<=d;i++){
        scanf("%d", &oven[i]);
        m.push_back(min(m.back(), oven[i]));
//        printf("%d ", m.back());
    }

    for(i=1;i<=n;i++){
        int dough;
        scanf("%d", &dough);

        it = lower_bound(m.begin()+1, m.begin()+deep, dough-1, cmp);
        deep = it - m.begin() - 1;
    }

    printf("%d", deep);

    return 0;
}
