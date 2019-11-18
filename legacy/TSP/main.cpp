#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

double graph[10][10];
bool visit[10];
int n;

vector<int> path;

double process(double length)
{
    int i;
    double ret=(double)0xFFFFFFFF;
    if(path.size() == n)
        return length;
    for(i=0; i<n; i++){
        if(visit[i]) continue;
        int here = path.back();
        path.push_back(i);
        visit[i] = true;
        ret = min(ret, process(length+graph[here][i]));
        visit[i] = false;
        path.pop_back();
    }
    return ret;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int i, c, j, k;
    double dist;
    scanf("%d", &c);
    for(i=0; i<c; i++){
        for(j=0; j<10; j++){
            visit[j]=false;
            while(path.size()>0) path.pop_back();
            for(k=0; k<10; k++)
                graph[j][k] = 0;
        }
        scanf("%d", &n);

        for(j=0; j<n; j++){
            for(k=0; k<n; k++){
                scanf("%lf", &dist);
                graph[j][k] = dist;
            }
        }
        double ret = 0xFFFFFFFF;
        for(j=0; j<n; j++){
            path.push_back(j);
            visit[j]=true;
            ret = min(ret, process(0));
            visit[j]=false;
            path.pop_back();
        }
        printf("%.10lf\n", ret);
    }
    return 0;
}
