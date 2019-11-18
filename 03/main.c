#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int D[6], i, j, temp;
    srand(time(NULL));
    for(i=0;i<6;i++)
        D[i] = rand()%100;
    printf("init: ");
    for(i=0;i<6;i++)
        printf("%d ", D[i]);
    printf("\n");
    for(i=0;i<6;i++){
        for(j=0;j<6-i-1;j++){
            if(D[j] > D[j+1]){
                temp = D[j+1];
                D[j+1] = D[j];
                D[j] = temp;
            }
        }
        if(i < 5){
            printf("step %d: ", i+1);
            for(j=0;j<6;j++)
                printf("%d ", D[j]);
            printf("\n");
        }
    }
    printf("result: ");
    for(i=0;i<6;i++)
        printf("%d ", D[i]);
    return 0;
}