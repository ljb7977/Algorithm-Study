#include <cstdio>
#include <cstring>

bool isFriend[10][10];
bool chk[10];
int n;

int process()
{
    int i, ans=0, first=-1;
    for(i=0; i<n; i++){
        if(chk[i]!=1){
            first = i;
            break;
        }
    }
    if(first==-1) return 1;

    for(i=first+1; i<n; i++){
        if(!chk[i] && isFriend[first][i]){
            chk[i]=chk[first]=1;
            ans+=process();
            chk[i]=chk[first]=0;
        }
    }
    return ans;
}

int main()
{
    int c, m, i, j, a, b, k;
    scanf("%d", &c);
    for(i=0; i<c; i++)
    {
        scanf("%d %d", &n, &m);
        for(j=0; j<10; j++)
            for(k=0; k<10; k++)
                isFriend[j][k]=0;
        for(j=0; j<m; j++){
            scanf("%d %d", &a, &b);
            isFriend[a][b]=1;
            isFriend[b][a]=1;
        }
        memset(chk, 0, n);
        printf("%d\n", process());
    }
    return 0;
}
