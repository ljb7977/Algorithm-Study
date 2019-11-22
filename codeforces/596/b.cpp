#include <bits/stdc++.h>

using namespace std;

int main()
{
//  freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio();
  cin.tie(0); cout.tie(0);

  int t;
  cin >> t;
  while(t--){
    map<int, int> P;
    int n, k, d;
    cin >> n >> k >> d;
    int ans = INT_MAX;
    vector<int> a(n+1);
    for(int i = 1; i <= n; i++){
      cin >> a[i];
    }
    for(int i = 1; i<=d; i++){
      ++P[a[i]];
    }
    ans = std::min(ans, (int)P.size());
    for(int i = d+1; i <= n; i++){
      --P[a[i-d]];
      ++P[a[i]];
      if(P[a[i-d]] == 0){
        P.erase(a[i-d]);
      }
      ans = std::min(ans, (int)P.size());
    }
    cout << ans << "\n";
  }
  return 0;
}
