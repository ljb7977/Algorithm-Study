#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;
vector<pair<int, int> > points;
vector<pair<int, int> > bong;

bool comp(const pair<int, int>& a, const pair<int, int>& b){
    return a.first < b.first;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n, i, miny=INT_MAX, min_i, minx = INT_MAX;
    scanf("%d", &n);
    for(i=0;i<n;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        points.emplace_back(x, y);
    }

    vector<int> stack;
    bool save = false;
    int saved;

    for(i=0; i<n; i++){
        pair<int, int> p1 = points[i], p2 =  points[(i+1)%n];

        if(p1.second < 0 && p2.second > 0){
            stack.push_back(p1.first);
        } else if(p1.second > 0 && p2.second < 0){
            if(stack.empty()){
                saved = p1.first;
                save = true;
            } else {
                stack.push_back(p1.first);
                if(stack[0] > stack[1])
                    swap(stack[0], stack[1]);

                bong.emplace_back(stack[0], stack[1]);
                stack.pop_back();
                stack.pop_back();
            }
        }
    }

    if(save){
        if(stack[0] > saved)
            swap(stack[0], saved);
        bong.emplace_back(stack[0], saved);
    }

    sort(bong.begin(), bong.end(), comp);

    int a=0, b=0;
    bool inc = false;
    int mx = -INT_MAX;
    n = bong.size();
    for(i=0;i<n;i++){
        if(bong[i].first > mx){
            a++;
            mx = bong[i].second;
        }
        if(i == n-1 || bong[i+1].first > bong[i].second){
            b++;
        }
    }

    printf("%d %d", a, b);

    return 0;
}