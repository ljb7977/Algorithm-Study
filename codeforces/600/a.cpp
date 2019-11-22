#include <cstdio>

constexpr int MAX_N=100010;

short A[MAX_N], B[MAX_N], sub[MAX_N];

bool solve(int n)
{
    for(int j=0; j<n; j++){
        sub[j] = B[j]-A[j];
    }

    bool started=false, ended=false;
    int candidate = -1;

    for(int j=0; j<n; j++){
        if(sub[j] < 0)
            return false;

        if(sub[j] > 0){
            if(!started){
                started = true;
                candidate = sub[j];
                continue;
            } else {
                if(candidate != sub[j]){
                    return false;
                }
                if(ended){
                    return false;
                }
            }
        }

        if(sub[j] == 0){
            if(started){
                ended = true;
            }
        }
    }
    return true;
}

int main() {
//    freopen("input.txt", "r", stdin);
    int t, n;
    scanf("%d", &t);
    for(int i=0; i<t; ++i){
        scanf("%d", &n);
        for(int j=0; j<n; j++) scanf("%d", &A[j]);
        for(int j=0; j<n; j++) scanf("%d", &B[j]);

        if(solve(n)){
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}