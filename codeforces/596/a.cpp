#include <bits/stdc++.h>

using namespace std;

int main()
{
  ios_base::sync_with_stdio();
  cin.tie(0); cout.tie(0);

  int a, b;
  cin >> a >> b;

  if(a == 9 && b == 1){
    cout << "9 10";
    return 0;
  }

  if(b-a > 1 || b-a < 0){
    cout << "-1";
    return 0;
  }

  if(b - a == 1){
    cout << a << " " << b;
    return 0;
  }

  if(b == a){
    cout << a*10 << " " << a*10+1;
    return 0;
  }

  return 0;
}