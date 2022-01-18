#include <iostream>
#include <queue>
#include <mutex>

using namespace std;

class Test {
public:
    int val;

    explicit Test(int val):
        val(val)
    {
        cout << "Test " << val << " constructor called" << endl;
    }

    ~Test()
    {
        cout << "Test " << val << " dtor at " << this << " called" << endl;
    }

    Test(const Test& t):
        val(t.val)
    {
        cout << "Test copy ctor called. val: " << val << endl;
    }

//    Test(Test&& t) noexcept :
//    val(t.val)       // explicit move of a member of class type
//    {
//        cout << "Test move ctor called. val: " << val << endl;
//    }
};

int main() {
    queue<Test> Q;

    Q.emplace(1);
    Q.emplace(2);
    Q.emplace(3);

//    Test t = Q.front();
//    Test &t_ref = Q.front();
//
//    cout << &Q.front() << endl;
//    Q.pop();
//
//    cout << &t << endl;
//    cout << &t_ref << endl;
//    cout << t_ref.val << endl;
//    cout << &Q.front() << endl;

    std::mutex lock;
    lock.lock();
    Test t(0);
    if(!Q.empty()) {
        t = Q.front();
        Q.pop();
        lock.unlock();
    }
    lock.unlock();
    //use t here

    return 0;
}
