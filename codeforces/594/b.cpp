#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i <n; ++i){
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    long long sum_short = 0, sum_long = 0;

    for(int i = 0; i < n/2; i++){
        sum_short += a[i];
    }
    for(int i = n/2; i<n; i++){
        sum_long += a[i];
    }
    cout << sum_short*sum_short + sum_long*sum_long;
    return 0;
}
