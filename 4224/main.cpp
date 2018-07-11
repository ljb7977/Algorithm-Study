#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

int dx[8] = {1, 2, 2, 1, -1, -2, -1, -2};
int dy[8] = {2, 1, -1, -2, 2, 1, -2, -1};

int n;

int backtrack(int x, int y, bool visited[700][700],
              vector<pair<int, int> >& stack, int depth)
{
    visited[x][y] = true;
    stack.emplace_back(x, y);
    if(depth == n*n){
        //print stack;
        for(auto i:stack){
            printf("%d %d\n", i.first, i.second);
        }
        exit(0);
    }
    for(int i = 0; i<8;i++)
        if(x+dx[i] >= 0 && x+dx[i] < n && y+dy[i] >= 0 && y+dy[i] < n)
            if(!visited[x+dx[i]][y+dy[i]])
                backtrack(x+dx[i], y+dy[i], visited, stack, depth+1);

    stack.pop_back();
    visited[x][y] = false;
}

int main() {
    int x, y;
    bool visited[700][700];
    vector<pair<int, int> > stack;
    scanf("%d", &n);
    scanf("%d %d", &x, &y);

    backtrack(x, y, visited, stack, 1);
    printf("-1");
    return 0;
}