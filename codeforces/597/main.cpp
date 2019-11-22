#include <iostream>

using namespace std;

bool solve(int a, int b)
{
    if(a < b){
        swap(a, b);
    }
    //now a >= b
    if(a == b)
        return false;

    if(b == 1)
        return false;


}

int gcd(int a, int b){
    while(b > 0){
        int temp = a%b;
        a = b;
        b = a%b;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    while(t--){
        int a, b;
        cin >> a >> b;

//        solve(a, b);
        cout << gcd(a, b);
    }
    return 0;
}