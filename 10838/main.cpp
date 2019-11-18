#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

int n, k;
int parent[100010]={-1};
int color[300010], real_color[300010];

struct query{
    int r, a, b, c;
} Q[300010];

int LCA(int a, int b)
{
    bool visit[100010] = {false};
    if(a == b)
        return a;
    while(1){
        if(a != -1){
            if(visit[a])
                return a;
            visit[a] = true;
            a = parent[a];
        }
        if(b != -1){
            if(visit[b])
                return b;
            visit[b] = true;
            b = parent[b];
        }
    }
}

int _count(int a, int b)
{
    int CA = LCA(a, b), cnt=0;
    bool visited_color[300010] = {false};

    for(int i =a ; i!=CA; i = parent[i]){
        if(!visited_color[real_color[i]]){
            cnt++;
            visited_color[real_color[i]] = true;
        }
    }
    for(int i = b; i!=CA; i = parent[i]){
        if(!visited_color[real_color[i]]){
            cnt++;
            visited_color[real_color[i]] = true;
        }
    }
    return cnt;
}

int main() {
//    freopen("input.txt", "r", stdin);
    int i, color_num=1;
    scanf("%d%d",&n,&k);
    for(i=0;i<k;i++){
        scanf("%d %d %d", &Q[i].r, &Q[i].a, &Q[i].b);
        if(Q[i].r == 1){
            scanf("%d", &Q[i].c);
            color[color_num++]=Q[i].c;
        }
    }
    sort(color, color+color_num);

    for(i=0;i<k;i++){
        switch(Q[i].r){
            case 1: {
                int CA = LCA(Q[i].a, Q[i].b);
                int c = lower_bound(color, color + color_num, Q[i].c) - color;
                for (int j = Q[i].a; j != CA; j = parent[j])
                    real_color[j] = c;

                for (int j = Q[i].b; j != CA; j = parent[j])
                    real_color[j] = c;
                break;
            }
            case 2:
                {
                    parent[Q[i].a] = Q[i].b;
                    break;
                }
            case 3:
                printf("%d\n", _count(Q[i].a, Q[i].b));
                break;
        }
    }

    return 0;
}