#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

struct vector2 {
    double x, y;
    explicit vector2(double x_=0, double y_=0): x(x_), y(y_){}

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

int main() {
//    freopen("input.txt", "r", stdin);
    vector<vector2> points;
    int n, i;
    scanf("%d", &n);
    for(i=0;i<n;i++){
        int x, y;
        scanf("%d %d", &x, &y);
        points.emplace_back(x, y);
    }
    polygon hull = convexHull(points);
    n = hull.size();
    printf("%d", n);
//    for(i=0;i<n;i++){
//        printf("%d %d\n", (int)hull[i].x, (int)hull[i].y);
//    }

    return 0;
}