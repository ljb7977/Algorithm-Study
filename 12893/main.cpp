#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int enemy[2010];

int find_root(int t)
{
    while(enemy[enemy[t]] != t){
        t = enemy[enemy[t]];
    }
    return t;
}

int main() {
//    freopen("input.txt", "r", stdin);
    int n, i, m;
    scanf("%d %d", &n, &m);
    for(i=0;i<m;i++){
        int a, b;
        scanf("%d %d", &a, &b);

        int t, s;
        if(enemy[a] == 0){
            if(enemy[b] == 0){
                enemy[a] = b;
                enemy[b] = a;
            } else {
                enemy[a] = find_root(b);
            }
        } else {
            if(enemy[b] == 0){
                enemy[b] = find_root(a);
            } else {
                s = find_root(a);
                t = find_root(b);
                if(s == t){
                    printf("0");
                    return 0;
                }
                enemy[b] = s;
                enemy[a] = t;
            }
        }
    }

    printf("1");

    return 0;
}