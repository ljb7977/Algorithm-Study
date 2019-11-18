#include <stdio.h>

int D[10][10];

int main() {
    int start, end, i, j;
    scanf("%d %d", &start, &end);

    for(i=start;i<=end;i++){
        for(j=1;j<=9;j++){
            D[i][j] = i*j;
        }
    }

    for(i=start;i<=end;i++){
        printf("%d단\n", i);
        for(j=1;j<=9;j++){
            printf("%d X %d = %d\n", i, j, D[i][j]);
        }
    }
    return 0;
}