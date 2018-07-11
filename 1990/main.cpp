#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

vector<int> T;
vector<int>::iterator it, low, up;

bool notprime[100000000];

bool isPalin(int n)
{
    char str[20];
    int i, len;
    bool ret = true;
    sprintf(str, "%d", n);
    len = strlen(str);
    for(i=0;i<len/2;i++){
        if(str[i] != str[len-1-i]){
            ret = false;
            break;
        }
    }
    return ret;
}

int main() {
    int a, b, n, i;
    scanf("%d %d", &a, &b);

    for(i=2;i<=10000;i++){
        if(!notprime[i]){
            for(int j=i*2;j<=100000000;j+=i){
                notprime[j]=true;
            }
        }
    }
    for(i=2;i<=100000000;i++){
        if(!notprime[i]){
            if(isPalin(i)){
                T.push_back(i);
            }
        }
    }

    low = lower_bound(T.begin(), T.end(), a);
    up = upper_bound(T.begin(), T.end(), b);

    for(it = low; it != up; it++){
        printf("%d\n", *it);
    }
    printf("-1");

    return 0;
}
