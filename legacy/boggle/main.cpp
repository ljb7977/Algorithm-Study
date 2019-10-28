#include <cstdio>
#include <cstdlib>
#include <cstring>

char tile[5][5];
bool isPossible[5][5], tempPossible[5][5];
char word[15];
int dx[8]={1,1,1,0,0,-1,-1,-1}, dy[8]={1,0,-1,1,-1,1,0,-1};

void input()
{
    int i;
    for(i=0; i<5; i++){
        scanf("%s", tile+i);
    }
}

int process()
{
    int i, j, k, l;
    scanf("%s", word);
    k=strlen(word)-1;
    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if(tile[i][j]==word[k]){
                isPossible[i][j]=1;
            } else {
                isPossible[i][j]=0;
            }
        }
    }
    k--;
    for( ; k>=0; k--){
        for(i=0; i<5; i++){
            for(j=0; j<5; j++){
                tempPossible[i][j]=isPossible[i][j];
                isPossible[i][j]=0;
            }
        }
        for(i=0; i<5; i++){
            for(j=0;j<5;j++){
                if(tile[i][j]==word[k]){
                    for(l=0;l<8;l++){
                        if(i+dx[l]>=5 || i+dx[l]<0 || j+dy[l]>=5 || j+dy[l]<0) continue;
                        if(tempPossible[i+dx[l]][j+dy[l]]){
                            isPossible[i][j] = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void output()
{
    int i, j;
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(isPossible[i][j]==1){
                printf("%s YES\n", word);
                return;
            }
        }
    }
    printf("%s NO\n", word);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int i, c, n, j;
    scanf("%d", &c);
    for(i=0; i<c;i++){
        input();
        scanf("%d", &n);
        for(j=0;j<n;j++){
            process();
            output();
        }
    }
    return 0;
}
