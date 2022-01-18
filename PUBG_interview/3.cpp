#include <iostream>

using namespace std;

int solution(int n) {
    int d[30];
    int l = 0;
    while (n > 0) {
        d[l] = n % 2;
        n /= 2;
        l++;
    }
    for (int p = 1; p <= l / 2; ++p) {
        bool ok = true;
        for (int i = 0; i < l - p; ++i) {
            if (d[i] != d[i + p]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            return p;
        }
    }
    return -1;
}

int main() {
    cout << solution(18);
    return 0;
}
