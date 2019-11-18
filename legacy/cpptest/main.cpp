#include <string>
#include <cstdio>

using namespace std;

bool ishex(string number)
{
	return number.substr(0, 2) == "0x";
}

int main()
{
	string t = "0x011";
	printf("%d", ishex(t));
    return 0;
}
