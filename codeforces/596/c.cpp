#include <bits/stdc++.h>

using namespace std;

int tobinary(int n)
{
  int cnt = 0;
  while(n > 0){
    cnt += n & 1;
    n >>= 1;
  }
  return cnt;
}

int main()
{
//  freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio();
  cin.tie(0); cout.tie(0);

  int n, p;
  cin >> n >> p;

  for(int i = 1; n - p*i > 0; ++i){
    if(tobinary(n - p*i) == i){
      cout << i;
      return 0;
    }
  }
  return 0;
}
