#include <bits/stdc++.h>

using namespace std;

vector<int> solve(const vector<int>& q, int n)
{
    set<int> s;
    for(int i = 1; i<=n; i++){
        s.insert(i);
    }

    vector<int> p(n);
    p[0] = q[0];
    s.erase(q[0]);
    for(int i = 1; i<n; i++){
        if(q[i] > q[i-1]){
            p[i] = q[i];
            s.erase(q[i]);
        } else if (q[i] == q[i-1]){
            if(*s.begin() > q[i]){
                return {-1};
            }
            p[i] = *s.begin();
            s.erase(s.begin());
        } else {

        }
    }
    return p;
}

int main() {
//    freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> q(n);
        for(int i = 0; i <n; i ++){
            cin >> q[i];
        }

        auto p = solve(q, n);
        for(int i = 0; i<p.size(); i++){
            cout << p[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}
