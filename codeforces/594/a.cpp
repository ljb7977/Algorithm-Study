#include <bits/stdc++.h>

using namespace std;

int main() {
//    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n;
        long long P_even=0, P_odd=0, Q_even=0, Q_odd=0;
        cin >> n;
        vector<int> P(n);
        for(int i = 0; i < n; ++i){
            cin >> P[i];
            if(P[i] % 2 == 0) ++P_even;
            else ++P_odd;
        }
        int m;
        cin >> m;
        vector<int> Q(m);
        for(int i = 0; i < m; ++i){
            cin >> Q[i];
            if(Q[i] % 2 == 0) ++Q_even;
            else ++Q_odd;
        }
        cout << Q_even * P_even + Q_odd * P_odd << "\n";
    }

    return 0;
}
