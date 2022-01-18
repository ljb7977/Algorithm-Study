#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        vector<int> diff(n+1);
        vector<int> sum(n+1);
        for(int i = 0; i<n; i++){
            if(s[i] == '(') {
                diff[i+1] = 1;
            } else {
                diff[i+1] = -1;
            }
            sum[i+1] = sum[i]+diff[i+1];
        }
        if(sum[1] < 0){
            for(int i = 1; i<=n; i++){
                if(sum[i] >= 0){

                }
            }
        }
        for(int i = 0; i<=n; i++){
            cout << sum[i] << " ";
        }
        cout << '\n';
    }
    return 0;
}
