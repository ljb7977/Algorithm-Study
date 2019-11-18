#include <cstdio>
#include <cstdlib>
#include <cstring>

int board[20][20], w, h;

int blocktype[4][3][2]={
{{0,0},{1,0},{0,1}},
{{0,0},{1,0},{1,1}},
{{0,0},{1,1},{0,1}},
{{0,0},{1,0},{1,-1}},
};

bool setblock(int x, int y, int type, int delta)
{
    int i, dx, dy;
    bool ok=true;
    for(i=0; i<3; i++){
        dx=x+blocktype[type][i][1];
        dy=y+blocktype[type][i][0];
        if(dx<0 || dx>=w || dy<0 || dy>=h) ok=false;
        else {
            board[dy][dx]+=delta;
            if(board[dy][dx]>1) ok=false;
        }
    }
    return ok;
}

int cover()
{
    int x=-1, y=-1, i, j, ans=0;
    for(i=0; i<h; i++){
        for(j=0; j<w; j++){
            if(board[i][j]==0){
                y=i;
                x=j;
                break;
            }
        }
        if(y!=-1) break;
    }
    if(y==-1) return 1;
    for(i=0; i<4; i++){
        if(setblock(x,y,i,1)) ans+=cover();
        setblock(x,y,i,-1);
    }
    return ans;
}

int main()
{
    int c, i, j, total;
    char temp;
    scanf("%d", &c);
    for(;c>0;c--){
        total=0;
        scanf("%d %d\n", &h, &w);
        for(i=0; i<h; i++){
            for(j=0; j<w; j++){
                scanf("%c", &temp);
                if(temp=='#') board[i][j]=1;
                else if (temp=='.'){
                    board[i][j]=0;
                    total++;
                }
            }
            scanf("\n");
        }
        if(total==0){
            printf("1\n");
            continue;
        }
        if(total%3!=0){
            printf("0\n");
            continue;
        }
        printf("%d\n", cover());
    }
    return 0;
}
