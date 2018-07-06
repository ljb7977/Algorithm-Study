#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int files[1010];

int main() {
    long long num = 0;
    int n, i, c;
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d", &files[i]);
    }
    scanf("%d", &c);

    for(i=0;i<n;i++){
        num += files[i]/c;
        if(files[i]%c != 0)
            num++;
    }
    printf("%lld", num*c);
    return 0;
}