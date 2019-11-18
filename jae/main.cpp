#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

void solve(int n, int k, int l){
    int i, S[10010]={0}, Q[10010]={0};
    int D[10010][12];
    for(i=0;i<n;i++){
        scanf("%d %d", &S[i], &Q[i]);
    }

    for(int j = 0; j< 10; j++){
        D[0][j] =
    }
    for(i=1;i<n;i++){
        for(int j = 0; j<10; j++){

        }
    }

}

int main() {
    int t, i, n, l;
    scanf("%d", &t);
    for(i=0;i<t;i++){
        scanf("%d %d %d", &n, &k, %l);
        solve(n, k, l);
    }

    return 0;
}