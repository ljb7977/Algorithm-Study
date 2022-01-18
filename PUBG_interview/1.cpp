#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Point3D {
    int x, y, z;
};

int sumOfSquares(const Point3D& p)
{
    return p.x*p.x + p.y*p.y + p.z*p.z;
}

int solution(vector<Point3D>& A){
    set<int> r_squares;
    for(const Point3D& point: A){
        r_squares.insert(sumOfSquares(point));
    }
    return r_squares.size();
}

int main() {
    vector<Point3D> v = {
            {10000, 10000, 10000},
            {-10000, -10000, -10000},
//            {-2, 1, -6},
//            {1, -2, 2},
//            {1, 1, 1},
//            {4, -4, 3}
    };
    cout << solution(v) << endl;

    return 0;
}
