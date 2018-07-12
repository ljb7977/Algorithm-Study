#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

int jewel[15];
int adj[101][101];

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 0; i<k;i++){
        scanf("%d", &jewel[i]);
    }
    for(int i = 0; i<m; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adj[a][b] = adj[b][a] = c;

    }


    return 0;
}