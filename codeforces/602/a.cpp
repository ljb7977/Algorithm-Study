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
        cin >> n;
        vector<int> starts(n);
        vector<int> ends(n);
        for(int i =0 ; i <n; i++){
            cin >> starts[i] >> ends[i];
        }
        if(n == 1){
            cout << "0\n";
            continue;
        }
        sort(starts.begin(), starts.end(), greater<int>());
        sort(ends.begin(), ends.end());
        cout << max(0, starts[0]-ends[0]) << "\n";
    }
    return 0;
}
