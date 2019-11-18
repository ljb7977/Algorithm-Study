#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> tree[100001];
vector<int>::iterator it;
vector<int> subtrees[1000001];
int song_to_singer[100010];
int n, i, k, j, parent, t, p, s;

void dfs()
{
    vector<int> stack;
    int t;
    stack.push_back(1);
    while(!stack.empty()){
        t = stack.back(); stack.pop_back();
        for(it = tree[t].begin(); it != tree[t].end(); it++){
            stack.push_back(*it);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d %d %d", &n, &k, &j);
    for(i=2;i<=n;i++){
        scanf("%d", &parent);
        tree[parent].push_back(i);
    }

    for(i=0;i<n;i++){
        scanf("%d", &song_to_singer[i]);
    }

    dfs();

    for(i=0; i<k; i++){
        scanf("%d %d %d", &t, &p, &s);
    }


    return 0;
}