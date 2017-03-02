#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define M 10000
#define N 10000

double work_kernel_omp(double **U, double **V, int m, int n, int x)
{
    /* Fill in your code here */
    int i,j;
    double a = 1.0, b = 0.5, c;

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(x)
    for( i=1; i < (m-1); i++)
        #pragma omp parallel for num_threads(x)
        for( j=1; j < (n-1); j++)
        {
            V[i][j] = ( a * (U[i+1][j] + U[i-1][j]) ) +
                      ( b * (U[i][j+1] + U[i][j-1]) ) +
                      ( (1 - (2*a) - (2*b)) * U[i][j] );
        }
    double stop = omp_get_wtime();

    return stop-start;
}

double work_kernel_serial(double **U, double **V, int m, int n)
{
    int i,j;
    double a = 1.0, b = 0.5, c;

	double start = omp_get_wtime();

    for( i=1; i < (m-1); i++)
        for( j=1; j < (n-1); j++)
        {
            V[i][j] = ( a * (U[i+1][j] + U[i-1][j]) ) +
                      ( b * (U[i][j+1] + U[i][j-1]) ) +
                      ( (1 - (2*a) - (2*b)) * U[i][j] );
        }
	double stop = omp_get_wtime();

    return stop-start;
}

int main(int argc, char * argv[])
{

    int i,j;
    int m = M;
    int n = N;
    double time_s;
    double time_o1, time_o2, time_o3, time_o4;

    double *B_block = (double *) malloc(sizeof(double) * m * n);
    double *V_block = (double *) malloc(sizeof(double) * m * n);
    double **B = (double **) malloc(sizeof(double*) * m); 
    double **V = (double **) malloc(sizeof(double*) * m);

    for(i=0; i<m; i++){
        B[i] = B_block + n*i; 
        V[i] = B_block + n*i; 
    }

    /* Initialize arrays */
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            B[i][j] = i*n + j;
        }
    }

    /* time serial case  */
    time_s = work_kernel_serial(B, V, m, n);
    time_o1 = work_kernel_omp(B, V, m, n, 2);
    time_o2 = work_kernel_omp(B, V, m, n, 4);
    time_o3 = work_kernel_omp(B, V, m, n, 8);
    time_o4 = work_kernel_omp(B, V, m, n, 32);

	printf("Time for serial: %lf seconds\n", time_s);
    printf("Time for parallel with 2 threads: %lf seconds\n", time_o1);
    printf("Time for parallel with 4 threads: %lf seconds\n", time_o2);
    printf("Time for parallel with 8 threads: %lf seconds\n", time_o3);
    printf("Time for parallel with 32 threads: %lf seconds\n", time_o4);
    /* Free memory*/
    free(B_block);
    free(V_block);
    free(B);
    free(V);

    return 0;

}

