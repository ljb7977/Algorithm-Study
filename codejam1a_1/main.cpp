#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int r, c;
int P[21][21];
vector<pair<int,int> > solution;
vector<pair<int,int>>::iterator it;

bool solve_helper(int depth, int now_r, int now_c)
{
    solution.emplace_back(now_r, now_c);
    P[now_r][now_c] = depth;
    if (depth >= r*c){
        //check remainder and
        return true;
    }
    for(int next_r=1; next_r<=r; next_r++){
        for(int next_c=1; next_c<=c; next_c++){
            if(next_r == now_r /|| next_c == now_c) continue;
            if(now_r-now_c == next_r-next_c || now_r+now_c == next_r+next_c) continue;
            if(P[next_r][next_c] != 0) continue;
            if(solve_helper(depth+1, next_r, next_c)) return true;
            solution.pop_back();
            P[next_r][next_c] = 0;
        }
    }
    return false;
}

bool solve(){
    for(int i = 1; i<=r; i++){
        for(int j = 1; j<=r; j++){
            memset(P, 0, 21*21);
            solution.clear();
            if(solve_helper(1, i, j))
                return true;
        }
    }
    return false;
}

void print_solution(){
    for(it = solution.begin(); it != solution.end(); it++){
        printf("%d %d\n", it->first, it->second);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    for(int i=1;i<=t;i++){
        scanf("%d %d", &r, &c);
        if(solve()){
            printf("Case #%d: POSSIBLE\n", i);
            print_solution();
        } else {
            printf("Case #%d: IMPOSSIBLE\n", i);
        }
    }
    return 0;
}