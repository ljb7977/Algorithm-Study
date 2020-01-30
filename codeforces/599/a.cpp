#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
//    freopen("input.txt", "r", stdin);
    int k, n;
    scanf("%d", &k);
    for(int t = 0; t < k; t++){
        scanf("%d", &n);
        vector<int> planks(n);
        for(int i = 0; i<n; i++){
            scanf("%d", &planks[i]);
        }

        sort(planks.begin(), planks.end());
        int max_size = -1;
        for(int i = 0; i < n; i++){
            max_size = max(max_size, min(planks[i], n-i));
//            if(planks[i] > max && n-i >= planks[i]){
//                max = planks[i];
//            }
        }
        printf("%d\n", max_size);
    }
    return 0;
}