#include <bits/stdc++.h>

using namespace std;

int main() {
    int mod = 1e9+7;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    long long F[100010] = {0, 1};
    for(int i = 2; i<max(m, n)+10; i++){
        F[i] = (F[i-1]+F[i-2])%mod;
    }
    long long ans = 0;
    ans = (ans+(F[max(m, n)+1] - 1))%mod;
    ans = (ans+F[min(m, n)+1])%mod;
    ans = (ans*2)%mod;
    cout << ans;
    return 0;
}
