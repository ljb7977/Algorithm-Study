#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int main()
{
    srand(time(0));
    double n=0;
    int pick[3];
    int winning[3];
    for(int i=0;i<1000000000; i++){
        pick[0]=rand()%10;
        pick[1]=rand()%10;
        pick[2]=rand()%10;
        if(pick[0]!=pick[1] && pick[1]!=pick[2] && pick[2]!=pick[0]){
            winning[0]=rand()%10;
            winning[1]=rand()%10;
            winning[2]=rand()%10;

            if (winning[0]==pick[0] && winning[1]==pick[1] && winning[2]==pick[2]){
                n+=580.0;
            }
            else{
                sort(pick, pick+3);
                sort(winning, winning+3);
                if (winning[0]==pick[0] && winning[1]==pick[1] && winning[2]==pick[2]){
                    n+=80.0;
                }
            }
        }
        //printf("%d", n);
    }
    printf("%lf", n/1000000000.0);
    return 0;
}
