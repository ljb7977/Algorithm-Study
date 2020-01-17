#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int visit[N];
set<int> st;

map<pair<int,int>, int> mp;

void dfs(int u)
{
    visit[u] = 1;
    st.erase(u);
    for(auto it = st.begin() ; it != st.end() ; ){
        int v = *it;
        if(mp.count({u,v})) {
            it++;
            continue;
        }
        dfs(v);
        it = st.upper_bound(v);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n,m;
    cin>>n>>m;
    for(int i = 1; i<=n ; ++i) st.insert(i);
    for(int i = 0; i<m ; ++i){
        int u,v;
        cin>>u>>v;
        mp[{u,v}] = mp[{v,u}] = 1;
    }

    int ans = -1;
    for(int i = 1; i<=n ; ++i){
        if(visit[i]) continue;
        ans++;
        dfs(i);
    }

    cout<<ans<<endl;
    return 0;
}