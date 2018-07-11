#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>

using namespace std;

set<int> numbers;
long long fact[21]={1LL};
int seq[21];

void permute(int n, long long k)
{
    if(n == 1){
        printf("%d ", *numbers.begin());
        return;
    }

    int j = (k-1)/fact[n-1];
    int num = *next(numbers.begin(), j);
    printf("%d ", num);
    numbers.erase(num);
    k -= j*fact[n-1];
    permute(n-1, k);
}

void nth(int n)
{
    int i, d;
    long long m = 0;
    for(i=0;i<n;i++){
        d = distance(numbers.begin(), numbers.find(seq[i]));
        numbers.erase(seq[i]);
        m += fact[n-i-1]*d;
    }
    printf("%lld", m+1);
}

int main() {
    long long k;
    int n, i, mode;

    for(i=1;i<=20;i++){
        fact[i] = fact[i-1]*i;
    }

    scanf("%d %d", &n, &mode);
    for(i=1;i<=n;i++) numbers.insert(i);

    if(mode == 1){
        scanf("%lld", &k);
        permute(n, k);
    } else {
        for(i=0;i<n;i++){
            scanf("%d", &seq[i]);
        }
        nth(n);
    }

    return 0;
}
