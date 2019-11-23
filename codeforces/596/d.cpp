#include <bits/stdc++.h>

using namespace std;

map<int, int> factor(int n, int k)
{
    int t=2;

    map<int, int> ans;

    while(n > 1){
        if(t*t>n){
            ++ans[n];
            break;
        }
        if(n%t == 0){
            n/=t;
            ++ans[t];
        } else {
            ++t;
        }
    }

    map<int, int> filtered;
    for(auto & an : ans){
        if(an.second % k != 0){
            filtered.emplace(an.first, an.second%k);
        }
    }
    return filtered;
}

int main ()
{
//    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<map<int, int>> P(n);
    for(int i = 0; i<n; i++){
        cin >> a[i];
        P[i] = factor(a[i], k);
    }

    map<map<int, int>, vector<int>> factor_to_num;
    for(int i = 0; i < n; ++i){
//        cout << i << ": ";
        factor_to_num[P[i]].push_back(a[i]);
//        for(auto t: P[i]){
//
//            cout << "(" << t.first << ", " << t.second << "), ";
//        }
//        cout << "\n";
    }

//    for(const auto& factor_list: factor_to_num){
//        for(auto factor: factor_list.first){
//            cout << "(" << factor.first << ", " << factor.second << "), ";
//        }
//        cout << ": [";
//        for(auto num: factor_list.second){
//            cout << num << ", ";
//        }
//        cout << "]\n";
//    }

    long long ans = 0;
    long long s = factor_to_num[map<int, int>()].size();
    ans += s*(s-1);

    factor_to_num.erase(map<int, int>());
    for(const auto& factor_list: factor_to_num){
        map<int, int> target_map;
        for(const auto& factor: factor_list.first){
            target_map[factor.first] = k-factor.second;
        }
        if(target_map == factor_list.first){
            ans += factor_to_num[target_map].size() * (factor_to_num[target_map].size()-1);
        } else {
            ans += factor_list.second.size() * factor_to_num[target_map].size();
        }
    }

    cout << ans/2;

    return 0;
}