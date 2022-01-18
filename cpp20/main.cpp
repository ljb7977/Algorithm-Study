#include <iostream>
using namespace std;

int main() {
    pair<int, float> p{1, 3.14};
    auto [i, f] = p;

    std::cout << i << f << std::endl;
    return 0;
}
