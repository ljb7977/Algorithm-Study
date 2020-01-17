#include <cstdio>
#include <vector>
#include <set>

using namespace std;

constexpr int MAX_N=1000001;

bool find(const set<int>& s, int employee)
{
    return s.find(employee) != s.end();
}

vector<int> solve(int P[], int n)
{
    vector<int> ans;

    set<int> is_in;
    set<int> is_entered_today;

    for(int i=0; i<n; ++i){
        int employee = P[i];
        if(employee > 0) { //in
            if(find(is_entered_today, employee)) return {}; //entered but already in office
            is_in.insert(employee);
            is_entered_today.insert(employee);
        } else { //out
            employee = -employee;
            if(!find(is_in, employee)) return {}; //invalid
            is_in.erase(employee);
            if(is_in.empty()){
                is_entered_today.clear();
                ans.push_back(i);
            }
        }
    }
    if(!is_in.empty()) return {};
    return ans;
}

int main()
{
//    freopen("input.txt", "r", stdin);
    int n, P[100001];
    scanf("%d", &n);
    for(int i=0; i<n; ++i){
        scanf("%d", &P[i]);
    }

    vector<int> ans = solve(P, n);
    if(ans.empty()){
        printf("-1");
        return 0;
    }

    printf("%d\n", ans.size());
    int prev = -1;
    for(auto t : ans){
        printf("%d ", t-prev);
        prev = t;
    }
    return 0;
}