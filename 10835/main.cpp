#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int left[2010], right[2010];
int save[2010][2010];

int n;

int f(int i, int j)
{
    if(i >= n || j >= n){
        return 0;
    }
    if(save[i][j] != -1)
        return save[i][j];

    int ans = 0;
    ans = max(ans, f(i+1, j));
    ans = max(ans, f(i+1, j+1));
    if(right[j] < left[i])
        ans = max(ans, right[j]+f(i, j+1));
    save[i][j] = ans;
    return ans;
}

int main() {
    scanf("%d", &n);
    for(int i =0; i<n; i++){
        scanf("%d", &left[i]);
    }
    for(int i = 0; i< n; i++){
        scanf("%d", &right[i]);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            save[i][j] = -1;
        }
    }

    printf("%d", f(0,0));

    return 0;
}