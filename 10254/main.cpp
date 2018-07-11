#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

struct vector2 {
    int x_i, y_i;
    double x, y;
    explicit vector2(double x_=0, double y_=0): x_i(x_), y_i(y_), x(x_), y(y_){}

    bool operator == (const vector2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    bool operator < (const vector2& rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }
    vector2 operator + (const vector2& rhs) const{
        return vector2(x+rhs.x, y+rhs.y);
    }
    vector2 operator - (const vector2& rhs) const{
        return vector2(x-rhs.x, y-rhs.y);
    }
    vector2 operator * (double rhs) const{
        return vector2(x*rhs, y*rhs);
    }
    double norm() const {
        return hypot(x, y);
    }
    vector2 normalize() const{
        return vector2(x/norm(), y/norm());
    }
    double dot(const vector2& rhs) const{
        return x*rhs.x + y*rhs.y;
    }
    double cross(const vector2& rhs) const{
        return x*rhs.y - rhs.x * y;
    }
};

typedef vector<vector2> polygon;

double ccw(vector2 a, vector2 b){
    return a.cross(b);
}

double ccw(vector2 p, vector2 a, vector2 b){
    return ccw(a-p, b-p);
}

vector2 pivot;

bool cmp(const vector2& a, const vector2& b)
{
    double val = ccw(pivot, a, b);
    if(val > 0) return true;
    else if (val < 0) return false;
    return a < b;
}

polygon convexHull(vector<vector2>& points)
{
    int n = points.size();
    vector<vector2> st;
    vector<vector2>::iterator it;
    pivot = *min_element(points.begin(), points.end());

    sort(points.begin(), points.end(), cmp);

    st.push_back(points[0]);
    st.push_back(points[1]);

    for(int i = 2; i<n; i++){
        while(st.size() >=2 && ccw(st[st.size()-2], st.back(), points[i]) <= 0){
            st.pop_back();
        }
        st.push_back(points[i]);
    }
    return st;
}

vector<vector2> diameter(const polygon& p)
{
    int n = p.size();
    int left = min_element(p.begin(), p.end())-p.begin();
    int right = max_element(p.begin(), p.end())-p.begin();

    vector2 calipersA(0, 1);
    double ret = (p[right]-p[left]).norm();
    vector<vector2> max_points = {p[right], p[left]};
    vector<vector2> toNext(n);
    for(int i=0;i<n;i++){
        toNext[i] = (p[(i+1)%n]-p[i]).normalize();
    }
    int a = left, b = right;
    while(a != right || b != left){
        double cosThetaA = calipersA.dot(toNext[a]);
        double cosThetaB = -calipersA.dot(toNext[b]);
        if(cosThetaA > cosThetaB){
            calipersA = toNext[a];
            a++;
            a%=n;
        } else {
            calipersA = toNext[b] * -1.0;
            b++;
            b%=n;
        }
        if((p[a]-p[b]).norm() > ret){
            max_points[0] = p[a];
            max_points[1] = p[b];
            ret = (p[a]-p[b]).norm();
        }
    }
    return max_points;
}

int main() {
//    freopen("input.txt", "r", stdin);
    int t, i, n, j;
    scanf("%d", &t);
    for(i=0;i<t;i++){
        scanf("%d", &n);
        vector<vector2> dots(n);
        for(j=0;j<n;j++){
            int x, y;
            scanf("%d %d", &x, &y);
            dots[j] = vector2(x, y);
        }
        polygon p = convexHull(dots);
        vector<vector2> maxp = diameter(p);
        printf("%d %d %d %d\n", maxp[0].x_i, maxp[0].y_i,
               maxp[1].x_i, maxp[1].y_i);
    };

    return 0;
}
