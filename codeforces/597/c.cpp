#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s;

    int m = 1e9+7;
    cin >> s;
    if(s.find('m')!=string::npos || s.find('w')!=string::npos){
        cout << 0;
        return 0;
    }
    vector<pair<int, int>> P(s.size()+1);
    P[1] = {1, 0};
    for(int i = 2; i<=s.size(); i++){
        P[i] = {(P[i-1].first+P[i-1].second)%m, P[i-1].first};
    }

    int count = 1;
    long long ans = 1;
    char prev='\0';
    for(int i = 0; i < s.size(); i++){
        if(s[i] == 'n'){
            if(prev == 'n'){
                count++;
            } else {
                ans *= (P[count].first+P[count].second)%m;
                ans %= m;
                count = 1;
            }
        }
        if(s[i] == 'u'){
            if(prev == 'u') count++;
            else{
                ans *= (P[count].first+P[count].second)%m;
                ans %= m;
                count = 1;
            }
        }
        prev = s[i];
    }

    ans *= (P[count].first+P[count].second)%m;
    ans %= m;
    cout << ans;

    return 0;
}
