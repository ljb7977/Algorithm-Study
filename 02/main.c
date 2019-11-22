#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int A[2][3], B[3][4], result[2][4]={0};
    int i, j, k;
    srand(time(NULL));
    for(i=0;i<2;i++){
        for(j=0;j<3;j++){
            A[i][j] = rand()%10;
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i=0;i<3;i++) {
        for (j = 0; j < 4; j++) {
            B[i][j] = rand() % 10;
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(i=0;i<2;i++){
        for(j=0;j<3;j++){
            for(k=0;k<4;k++){
                result[i][k] += A[i][j]*B[j][k];
            }
        }
    }
    for(i=0;i<2;i++){
        for(k=0;k<4;k++){
            printf("%d ", result[i][k]);
        }
        printf("\n");
    }

    return 0;
}