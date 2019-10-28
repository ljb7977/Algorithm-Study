#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

char S[50][51];
char result[51];

int main() {
    int i, j, n, len;
//    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%s", S[i]);
    }

    len = strlen(S[0]);

    for(j=0;j<len;j++){
        bool check = true;
        for(i=0;i<n-1;i++){
            if (S[i][j] != S[i+1][j]){
                check = false;
                break;
            }
        }
        result[j] = check ? S[i][j] : '?';
    }

    printf("%s", result);
    return 0;
}