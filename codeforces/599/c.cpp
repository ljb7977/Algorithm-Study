#include <cstdio>
#include <set>

using namespace std;

int main()
{
    set<long long> factors;
    long long n;
    scanf("%lld", &n);

    long long k = 2;
    while(n > 1){
        if(k*k > n){
            factors.insert(n);
            break;
        }
        if(n%k == 0){
            n/=k;
            factors.insert(k);
            if(factors.size()>=2){
                break;
            }
        } else {
            k++;
        }
    }

    if(factors.size() == 1){
        printf("%lld", *factors.begin());
    } else {
        printf("1");
    }

    return 0;
}