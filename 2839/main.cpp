#include <iostream>

using namespace std;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  int min_bag = INT32_MAX;
  for(int i = 0; i*5 <= n; ++i){
    if((n - i*5) % 3 == 0){
      min_bag = min(i+(n - i*5)/3, min_bag);
    }
  }
  if(min_bag == INT32_MAX){
    cout << -1;
    return 0;
  }

  cout << min_bag;
  return 0;
}
