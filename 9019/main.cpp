#include <cstdio>
#include <queue>
#include <set>
#include <cstring>

using namespace std;

int l(int n)
{
    int temp = n;
    int d1;
    d1 = temp/1000;
    temp -= d1*1000;
    temp *= 10;
    temp += d1;
    return temp;
}

int r(int n)
{
    int temp = n;
    int d4;
    d4 = temp%10;
    temp/=10;
    temp+=d4*1000;
    return temp;
}

char actions[4] = {'D', 'S', 'L', 'R'};
queue<int> Q;
int parent[10010];
char action[10010];

void bfs(int start, int dest)
{
    memset(parent, -1, sizeof(parent));
    memset(action, 0, sizeof(action));
    while(!Q.empty()) Q.pop();
    Q.push(start);
    parent[start] = start;
    while(!Q.empty()){
        int cur = Q.front(); Q.pop();
        int numbers[4] = {(cur*2)%10000, cur==0?9999:cur-1, l(cur), r(cur)};
        for(int i = 0; i < 4; i++){
            int number = numbers[i];
            if(parent[number] == -1){
                Q.push(number);
                parent[number] = cur;
                action[number] = actions[i];
                if(number == dest)
                    return;
            }
        }
    }
}

int main() {
    int n, t, dest;
    char reverse[10001];
    scanf("%d", &t);
    for(int i = 0; i<t; i++){
        scanf("%d %d", &n, &dest);
        bfs(n, dest);
        int k = 0;
        for(int j = dest; j != parent[j]; j = parent[j])
            reverse[k++] = action[j];
        for(k--;k>=0;k--)
            printf("%c", reverse[k]);
        printf("\n");
    }
    return 0;
}