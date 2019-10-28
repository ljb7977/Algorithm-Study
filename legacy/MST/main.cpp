#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

char S[60], S2[60], D[60];

int main()
{
    int n, i, m ,j;
    scanf("%d", &n);
    for(i=0; i<n; i++){
        strcpy(S2, S);
        scanf("%s", S);
        if(i==0) {
            m=strlen(S);
            continue;
        }
        for(j=0; j<m; j++){
            if(S[j] == S2[j]){
                D[j] = S[j];
            }
            else {
                D[j] = '?';
            }
        }
    }
    printf("%s", D);
    return 0;
}
