#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b)
{
     while(b > 0){
         int temp = b;
         b = a % b;
         a = temp;
     }
     return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        if (gcd(a, b) == 1) {
            cout << "Finite\n";
        } else {
            cout << "Infinite\n";
        }
    }

    return 0;
}
