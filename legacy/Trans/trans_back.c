//cs20150599 Lee Ju Been

/*
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/*
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded.
 */


void transpose_3232(int M, int N, int A[N][M], int B[M][N]){
    int i, j,ii,jj, tempi, tempj;
    int temp, valid = 0;
    for(i = 0; i<M; i+=8){
        for(j =0; j<N; j+=8){
            for(ii=i; ii<i+8; ii++){
                if(valid == 1){
                    B[tempj][tempi] = temp;
                    valid = 0;
                }
                for(jj=j; jj<j+8; jj++){
                    if(ii == jj){
                        temp = A[ii][jj];
                        valid = 1;
                        tempi = ii;
                        tempj = jj;
                        continue;
                    }
                    B[jj][ii] = A[ii][jj];
                }
            }
        }
    }
    B[M-1][N-1] = A[N-1][M-1];
}

void helper(int M, int N, int A[N][M], int B[M][N], int i, int j, int ii, int jj, int ioffset, int joffset)
{
    int temp1, temp2, temp3, temp4, tempd1, tempd2, tempd3, tempd4;
    for(ii=ioffset; ii<4+ioffset; ii++){
        for(jj=joffset; jj<4+joffset; jj++){
            if(ii-ioffset == jj-joffset){
                if(jj == joffset){
                    temp1 = A[i+ii][j+jj];
                    tempd1 = i+ii;
                } else if(jj == joffset+1){
                    temp2 = A[i+ii][j+jj];
                    tempd2 = i+ii;
                } else if(jj == joffset+2){
                    temp3 = A[i+ii][j+jj];
                    tempd3 = i+ii;
                } else if(jj == joffset+3){
                    temp4 = A[i+ii][j+jj];
                    tempd4 = i+ii;
                }
                continue;
            }
            B[j+jj][i+ii] = A[i+ii][j+jj];
        }
    }

    B[tempd1-ioffset+joffset][tempd1] = temp1;
    B[tempd2-ioffset+joffset][tempd2] = temp2;
    B[tempd3-ioffset+joffset][tempd3] = temp3;
    B[tempd4-ioffset+joffset][tempd4] = temp4;
}

void transpose_6464(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, ii, jj;
    for(i = 0; i < 64; i += 8){
        for(j = 0; j < 64; j += 8){ //8*8 block
            if(i == j){
                //conflict process
                helper(M, N, A, B, i, j, ii, jj, 0, 0);
                helper(M, N, A, B, i, j, ii, jj, 0, 4);
                helper(M, N, A, B, i, j, ii, jj, 4, 0);
                helper(M, N, A, B, i, j, ii, jj, 4, 4);
            } else {
                //8*8 block
                for(ii=0; ii<4; ii++){
                    for(jj=0; jj<4; jj++){
                        B[jj+j][ii+i] = A[ii+i][jj+j];
                    }
                }
                for(ii=0; ii<4; ii++){
                    for(jj=4; jj<8; jj++){
                        B[jj+j][ii+i] = A[ii+i][jj+j];
                    }
                }
                for(ii=4; ii<8; ii++){
                    for(jj=0; jj<4; jj++){
                        B[jj+j][ii+i] = A[ii+i][jj+j];
                    }
                }
                 for(ii=4; ii<8; ii++){
                    for(jj=4; jj<8; jj++){
                        B[jj+j][ii+i] = A[ii+i][jj+j];
                    }
                }
            }
        }
    }
}

void transpose_6761(int M, int N, int A[N][M], int B[M][N]){
    int i, j, ii, jj;
    int temp, tempi, tempj;
    for(i = 0; i < N; i+=16){
        for(j = 0; j < M; j+=16){
            for(ii = 0; ii < 16 && i+ii<N; ii++){
                for(jj = 0; jj< 16 && j+jj<M; jj++){
                    if(i+ii == j+jj){
                        temp = A[i+ii][j+jj];
                        tempi = i+ii;
                        tempj = j+jj;
                    } else {
                        B[j+jj][i+ii] = A[i+ii][j+jj];
                    }
                }
                if(i == j)
                    B[tempj][tempi] = temp;
            }
        }
    }
}

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if(M == 32){
        transpose_3232(M, N, A, B);
    } else if (M == 64){
        transpose_6464(M, N, A, B);
    } else if (M == 61){
        transpose_6761(M, N, A, B);
    }
}

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}

/*
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

int main(){
    //trans()
    freopen("output.txt", "w", stdout);
    int A[64][64], B[64][64];
    int i, j;
    randMatrix(64,64,A);
    for(i = 0; i < 64; i++){
        for(j = 0; j < 64; j++){
            A[i][j]%=10;
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    transpose_submit(64, 64, A, B);
    for(i = 0; i< 64; i++){
        for(j = 0; j < 64; j++){
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    printf("%d", is_transpose(64, 64, A, B));
    return 0;
}

