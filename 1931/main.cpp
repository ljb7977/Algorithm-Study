#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

vector<pair<int, int> > meeting, done;

bool comp(const pair<int, int> a, const pair<int, int> b)
{
    if(a.second == b.second)
        return a.first < b.first;
    return a.second < b.second;
}

int main(){
//    freopen("input.txt", "r", stdin);
    int n, i, count=0;
    int min_ = 0;
    scanf("%d", &n);
    for(i=0;i<n;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        meeting.emplace_back(a, b);
    }
    sort(meeting.begin(), meeting.end(), comp);

    for(i=0;i<n;i++){
        if(meeting[i].first < min_)
            continue;
        min_ = meeting[i].second;
        //done.push_back(meeting[i]);
        count++;
    }
    printf("%d", count);

    return 0;
}
