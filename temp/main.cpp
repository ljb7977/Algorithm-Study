//count to 10
#include <iostream>
#include <string>

int main()
{
  int i = 0;
  
  beginning:
  if (i < 10) {
      std::cout << ++i << std::endl;
      goto beginning;
  }
  else goto end;

  end:
  return 0;
}