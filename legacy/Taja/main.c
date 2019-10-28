#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
	char words[50][10] = {"apple", "banana", "cat",
	"drive", "enter", "fruit", "google", "hello", "icecream",
	"jelly"
	};
	char ans[50];
	time_t base = clock();
	int t;
	int n = 0;
	int right = 0;
	int tasu = 0;
	srand(time(0));
	while((float)(clock()-base)/CLOCKS_PER_SEC <= 30){
        t = rand()%10;
        puts(words[t]);
        n++;
        gets(ans);
        tasu += strlen(ans);
        if(strcmp(words[t], ans) == 0){
            right++;
            puts("Right!");
        } else {
            puts("Wrong!");
        }
        printf("Accuracy : %.2f%%\n\n", (float)right*100/n);
	}
	printf("tasu/m : %d\n", tasu*2);
	puts("Time Over");

	return 0;
}
