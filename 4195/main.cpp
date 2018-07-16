#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

map<string, int> namemap;
map<string, int>::iterator it;

int parent[200010];
int size[200010];

int find(int u){
    while(u != parent[u])
        u = parent[u];
    return u;
}

void merge(int u, int v)
{
    u = find(u), v = find(v);
    int size1 = size[u], size2 = size[v];
    if(u == v)
        return;
    parent[u] = v;
    size[v] = size1+size2;
}

int main() {
//    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for(int i = 0 ;i<n; i++){
        int f;
        scanf("%d", &f);
        namemap.clear();
        for(int j = 0; j<f*2; j++)
            parent[j] = j, size[j] = 1;

        for(int j = 0; j<f; j++){
            char name_c1[23], name_c2[23];
            string name1, name2;
            scanf("%s %s", name_c1, name_c2);
            name1 = name_c1;
            name2 = name_c2;
            it = namemap.find(name1);
            if(it == namemap.end()){
                namemap.emplace(name1, namemap.size());
            }
            it = namemap.find(name2);
            if(it == namemap.end()){
                namemap.emplace(name2, namemap.size());
            }
            merge(namemap[name1], namemap[name2]);
            printf("%d\n", size[find(namemap[name1])]);
        }
    }

    return 0;
}
