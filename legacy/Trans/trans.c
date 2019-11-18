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

/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
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
                        valid = 1; tempi = ii; tempj = jj;
                        continue;
                    }
                    B[jj][ii] = A[ii][jj];
                }
            }
        }
    }
    B[M-1][N-1] = A[M-1][N-1];
}


void transpose_6464(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, ii, jj;
    int temp1, temp2, temp3, temp4, tempd1, tempd2, tempd3, tempd4;
    for(i = 0; i < N; i += 8){
        for(j = 0; j < M; j += 8){ //8*8 block
            if(i == j){
                temp1 = A[i][i];
                temp2 = A[i][i+1];
                temp3 = A[i+1][i];
                temp4 = A[i+1][i+1];
                tempd1 = A[i+2][i+2];
                tempd2 = A[i+2][i+3];
                tempd3 = A[i+3][i+2];
                tempd4 = A[i+3][i+3];
                for(ii=i; ii<i+2; ii++){
                    for(jj = j+2; jj<j+4; jj++){
                    B[jj][ii] = A[ii][jj];
                    }
                }
                B[i+2][i+2] = tempd1;
                B[i+2][i+3] = tempd3;
                B[i+3][i+2] = tempd2;
                B[i+3][i+3] = tempd4;
                for(ii=i+2; ii<i+4; ii++){
                    for(jj = j; jj<j+2; jj++){
                    B[jj][ii] = A[ii][jj];
                    }
                }
                B[i][i] = temp1;
                B[i][i+1] = temp3;
                B[i+1][i] = temp2;
                B[i+1][i+1] = temp4;
                //upper left
                temp1 = A[i][i+4];
                temp2 = A[i][i+5];
                temp3 = A[i+1][i+4];
                temp4 = A[i+1][i+5];
                tempd1 = A[i+2][i+6];
                tempd2 = A[i+2][i+7];
                tempd3 = A[i+3][i+6];
                tempd4 = A[i+3][i+7];
                for(ii=i; ii<i+2; ii++){
                    for(jj = j+6; jj<j+8; jj++){
                    B[jj][ii] = A[ii][jj];
                    }
                }
                B[i+6][i+2] = tempd1;
                B[i+7][i+2] = tempd2;
                B[i+6][i+3] = tempd3;
                B[i+7][i+3] = tempd4;
                for(ii=i+2; ii<i+4; ii++){
                    for(jj = j+4; jj<j+6; jj++){
                    B[jj][ii] = A[ii][jj];
                    }
                }
                B[i+4][i] = temp1;
                B[i+5][i] = temp2;
                B[i+4][i+1] = temp3;
                B[i+5][i+1] = temp4;
                //upper right

                temp1 = A[i+4][i];
                temp2 = A[i+4][i+1];
                temp3 = A[i+5][i];
                temp4 = A[i+5][i+1];
                tempd1 = A[i+6][i+2];
                tempd2 = A[i+6][i+3];
                tempd3 = A[i+7][i+2];
                tempd4 = A[i+7][i+3];
                for(ii=i+4; ii<i+6; ii++){
                    for(jj = j+2; jj<j+4; jj++){
                    B[jj][ii] = A[ii][jj];
                    }
                }
                B[i+2][i+6] = tempd1;
                B[i+3][i+6] = tempd2;
                B[i+2][i+7] = tempd3;
                B[i+3][i+7] = tempd4;
                for(ii=i+6; ii<i+8; ii++){
                    for(jj = j; jj<j+2; jj++){
                    B[jj][ii] = A[ii][jj];
                    }
                }
                B[i][i+4] = temp1;
                B[i+1][i+4] = temp2;
                B[i][i+5] = temp3;
                B[i+1][i+5] = temp4;
                //lower left
                temp1 = A[i+4][i+4];
                temp2 = A[i+4][i+5];
                temp3 = A[i+5][i+4];
                temp4 = A[i+5][i+5];
                tempd1 = A[i+6][i+6];
                tempd2 = A[i+6][i+7];
                tempd3 = A[i+7][i+6];
                tempd4 = A[i+7][i+7];
                for(ii=i+4; ii<i+6; ii++){
                    for(jj = j+6; jj<j+8; jj++){
                    B[jj][ii] = A[ii][jj];
                    }
                }
                B[i+6][i+6] = tempd1;
                B[i+7][i+6] = tempd2;
                B[i+6][i+7] = tempd3;
                B[i+7][i+7] = tempd4;
                for(ii=i+6; ii<i+8; ii++){
                    for(jj = j+4; jj<j+6; jj++){
                    B[jj][ii] = A[ii][jj];
                    }
                }
                B[i+4][i+4] = temp1;
                B[i+5][i+4] = temp2;
                B[i+4][i+5] = temp3;
                B[i+5][i+5] = temp4;
                //lower right
        /*
                for(ii=4; ii<8; ii++){
                    for(jj=0; jj<4; jj++){
                        if(ii-4 == jj){
                            if(jj == 0){
                                temp1 = A[i+ii][j+jj];
                                tempd1 = i+ii;
                            } else if(jj == 1){
                                temp2 = A[i+ii][j+jj];
                                tempd2 = i+ii;
                            } else if(jj == 2){
                                temp3 = A[i+ii][j+jj];
                                tempd3 = i+ii;
                            } else if(jj == 3){
                                temp4 = A[i+ii][j+jj];
                                tempd4 = i+ii;
                            }
                            continue;
                        }
                        B[j+jj][i+ii] = A[i+ii][j+jj];
                    }
                }

                B[tempd1-4][tempd1] = temp1;
                B[tempd2-4][tempd2] = temp2;
                B[tempd3-4][tempd3] = temp3;
                B[tempd4-4][tempd4] = temp4;
                for(ii=4; ii<8; ii++){
                    for(jj=4; jj<8; jj++){
                        if(ii == jj){
                            if(jj == 4){
                                temp1 = A[i+ii][j+jj];
                                tempd1 = i+ii;
                            } else if(jj == 5){
                                temp2 = A[i+ii][j+jj];
                                tempd2 = i+ii;
                            } else if(jj == 6){
                                temp3 = A[i+ii][j+jj];
                                tempd3 = i+ii;
                            } else if(jj == 7){
                                temp4 = A[i+ii][j+jj];
                                tempd4 = i+ii;
                            }
                            continue;
                        }
                        B[j+jj][i+ii] = A[i+ii][j+jj];
                    }
                }

                B[tempd1][tempd1] = temp1;
                B[tempd2][tempd2] = temp2;
                B[tempd3][tempd3] = temp3;
                B[tempd4][tempd4] = temp4;
*/

                } else {
                //8*8 block
                for(ii=0; ii<4; ii++){
                    for(jj=0; jj<4; jj++){
                        B[jj+j][ii+i] = A[ii+i][jj+j];
                    }
                } //upper left
                /*
                for(ii=0; ii<4; ii++){
                    for(jj=4; jj<8; jj++){
                        B[j+jj][i+ii] = A[ii+i][jj+j];
                    }
                } //upper right
                */
                temp1 = A[i][j+4];
                temp2 = A[i][j+5];
                temp3 = A[i][j+6];
                temp4 = A[i][j+7];
                tempd1 = A[i+1][j+4];
                tempd2 = A[i+1][j+5];
                tempd3 = A[i+1][j+6];
                tempd4 = A[i+1][j+7];

                for(ii=4; ii<8; ii++){
                    for(jj=0; jj<4; jj++){
                        B[j+jj][i+ii] = A[ii+i][jj+j];
                    }
                } //lower left

                 for(ii=4; ii<8; ii++){
                    for(jj=4; jj<8; jj++){
                        B[j+jj][i+ii] = A[ii+i][jj+j];
                    }
                }//lower right
                B[j+4][i] = temp1;
                B[j+5][i] = temp2;
                B[j+6][i] = temp3;
                B[j+7][i] = temp4;
                B[j+4][i+1] = tempd1;
                B[j+5][i+1] = tempd2;
                B[j+6][i+1] = tempd3;
                B[j+7][i+1] = tempd4;
                //upper right

                temp1 = A[i+2][j+4];
                temp2 = A[i+2][j+5];
                temp3 = A[i+2][j+6];
                temp4 = A[i+2][j+7];
                tempd1 = A[i+3][j+4];
                tempd2 = A[i+3][j+5];
                tempd3 = A[i+3][j+6];
                tempd4 = A[i+3][j+7];

                B[j+4][i+2] = temp1;
                B[j+5][i+2] = temp2;
                B[j+6][i+2] = temp3;
                B[j+7][i+2] = temp4;
                B[j+4][i+3] = tempd1;
                B[j+5][i+3] = tempd2;
                B[j+6][i+3] = tempd3;
                B[j+7][i+3] = tempd4;
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
				if(i==j)
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
	} else if (M== 61){
		transpose_6761(M, N, A, B);
	}
}

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

