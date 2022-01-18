#include <iostream>
#include <chrono>
#include <future>
#include <vector>
#include <queue>

using namespace std;

class TestVector: public std::vector<int>
{
public:
  ~TestVector(){
    cout << "TestVector dtor at: " << this << " called\n";
  }
};

class Test
{
public:
  int val;

  Test(int val)
  :val(val)
  {
    cout << "Test ctor called. " << this << endl;
  }

  Test(const Test& t)
  :val(t.val)
  {
    cout << "Test copy ctor called. " << this << "/ source: " << &t << endl;
  }

  ~Test()
  {
    cout << "Test dtor called. " << this << endl;
  }
};

void loop(const Test& t)
{
  cout << "t in loop's address: " << &t << endl;
  for(int i = 0 ; i< 1000000000; i++);
  cout << "In loop(): t.val: " << t.val << endl;
}

void ttt()
{
  std::queue<Test> Q;
  Q.emplace(1);
  Q.emplace(2);
  Q.emplace(3);
  Q.emplace(4);

  std::mutex lck;

  Test t(0);

  {
    lock_guard<std::mutex> g(lck);
    if(!Q.empty()){
      t = Q.front(); Q.pop();
    }
  }
  cout << t.val << endl;
  //use t

}

int main()
{
  auto start = std::chrono::high_resolution_clock::now();
  long diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
  {
    Test t(1);
    cout << "t's address: " << &t << " / val : " << t.val << endl;

    start = std::chrono::high_resolution_clock::now();
    auto f = std::async(std::launch::async, &loop, t);
    t.val = 2;
    diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
  }
  cout << "Time diff: " << diff << endl;

  return 0;
}
