#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int n;
long long getNum(int i, int j)
{
    long long num = 0;
    long long t = i+j-1;
    if(t > n){
        num = (long long)n*(n+1)/2;
        t = 2*n-t;
        num += (long long)n*(n-1)/2-t*(t+1)/2;

        if(t%2 == 1){ //up
            num += n-i+1;
        } else { //down
            num += n-j+1;
        }
    } else {
        num = t*(t-1)/2;
        if(t%2 == 1){ //up
            num += j;
        } else { //down
            num += i;
        }
    }
    return num;
}

int main() {
    int i=1, j=1, k;
    long long sum = 1;
    scanf("%d %d\n", &n, &k);

    for(int t=0;t<k;t++){
        char c;
        scanf("%c", &c);
        switch(c){
            case 'U':
                i--;
                break;
            case 'D':
                i++;
                break;
            case 'L':
                j--;
                break;
            case 'R':
                j++;
                break;
        }
        sum += getNum(i, j);
    }
    printf("%lld", sum);

    return 0;
}