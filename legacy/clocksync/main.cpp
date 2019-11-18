#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int clocks[16];
char linked[10][17]=
{
    "xxx.............",
    "...x...x.x.x....",
    "....x.....x...xx",
    "x...xxxx........",
    "......xxx.x.x...",
    "x.x...........xx",
    "...x..........xx",
    "....xx.x......xx",
    ".xxxxx..........",
    "...xxx...x...x.."
};

void push(int num)
{
    for(int i=0; i<16; i++)
        if(linked[num][i]=='x'){
            clocks[i] += 3;
            if(clocks[i] == 15) clocks[i]=3;
        }
}

int process(int depth)
{
    int i, ret=1000000;
    if(depth==10){
        for(i=0; i<16; i++) if(clocks[i] != 12) break;
        if(i==16) return 0;
        else return 1000000;
    }
    for(i=0; i<4; i++){
        ret = min(ret, i+process(depth+1));
        push(depth);
    }
    return ret;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int c, i, j, ret;
    scanf("%d", &c);
    for(i=0; i<c; i++){
        for(j=0; j<16; j++) scanf("%d", &clocks[j]);
        ret = process(0);
        if(ret == 1000000) printf("-1\n");
        else printf("%d\n", ret);
    }

    return 0;
}
