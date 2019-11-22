#include <cstdio>
#include <bits/ios_base.h>
#include <iostream>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s, t;
    int k, n;

    cin >> k;
    for(int a = 0; a < k; a++){
        cin >> n;
        cin >> s >> t;

        int cnt = 0;
        int diff[2];
        for(int i=0; i<n; i++) {
            if(s[i] != t[i]) {
                diff[cnt++] = i;
            }
        }

        if(cnt != 2){
            cout << "No\n";
            continue;
        }

        if (s[diff[0]] == s[diff[1]] && t[diff[0]] == t[diff[1]]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
