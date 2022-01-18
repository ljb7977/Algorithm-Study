#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n+1);
    vector<int> num_greater_than_me(n+1);
    for(int i = 1; i<=n ; i++){
        cin >> a[i];
    }

    for(int i = 1; i<=n; i++){
        for(int j = i; j<=n; j++){
            if(a[j] >= a[i]){
                ++num_greater_than_me[i];
            }
        }
    }

    int m;
    cin >> m;
    vector<pair<int, int>> query(m+1);
    for(int i = 1; i<=m; i++){
        int k, pos;
        cin >> k >> pos;
        query[i] = {k, pos};
    }

    vector<vector<int>> ans(n+1);
    for(int k=1; k<=n; k++){
        int k_left = k;
        for(int i = 1; i<=n; i++){
            if(num_greater_than_me[i] <= k_left){
                ans[k].push_back(a[i]);
                k_left--;
            }
        }
    }

    for(int i = 1; i<=m; i++){
        int k, pos;
        tie(k, pos) = query[i];
        cout << ans[k][pos-1] << "\n";
    }


    return 0;
}
