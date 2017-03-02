#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define N 1000

float ** matrix( int n )
{
	float *data = (float *) calloc( n*n, sizeof(float) );
	float **M  = (float **) malloc( n  * sizeof(float*));

	for( int i = 0; i < n; i++ )
		M[i] = &data[i*n];

	return M;
}

void matrix_free( float ** M)
{
	free(M[0]);
	free(M);
}

void init(float ** M, int n)
{
	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++ )
			M[i][j] = (float) ( rand() % 100 );
}

double mm_omp(int n, int x)
/* Perform matrix multiplication using OpenMP */
{
    /* Fill in code here */
    // Allocate arrays
	float ** A = matrix(n);
	float ** B = matrix(n);
	float ** C = matrix(n);
	init(A,n);
	init(B,n);

	double start = omp_get_wtime();
	// Multiply
	int i, j, k;
	float s;
	#pragma omp parallel for private(i,j,k) num_threads(x)
	for( i = 0; i < n; i++ )
		#pragma omp parallel for private(j,k) num_threads(x)
		for(j = 0; j < n; j++ )
			//s = 0;
			//#pragma omp parallel for private (k) shared( s ) num_threads(x)
			for(k = 0; k < n; k++ )
				//#pragma omp atomic
				C[i][j] += A[i][k] * B[k][j];
			//C[i][j] = s;
			
	double stop = omp_get_wtime();

	matrix_free(A);
	matrix_free(B);
	matrix_free(C);

    return stop-start;
}

double mm_serial( int n )
/* Perform matrix multiplication serially */
{

	// Allocate arrays
	float ** A = matrix(n);
	float ** B = matrix(n);
	float ** C = matrix(n);
	init(A,n);
	init(B,n);

	double start = omp_get_wtime();
	// Multiply
	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++ )
			for( int k = 0; k < n; k++ )
				C[i][j] += A[i][k] * B[k][j];
	double stop = omp_get_wtime();

	matrix_free(A);
	matrix_free(B);
	matrix_free(C);

    return stop-start;

}

int main(int argc, char * argv[])
{

    int i,j;
    int n = N;

	double time = mm_serial(n);
	printf("Time for serial: %lf seconds\n", time);
	double time_o1 = mm_omp(n,2);
	double time_o2 = mm_omp(n,4);
	double time_o3 = mm_omp(n,8);
	double time_o4 = mm_omp(n,32);
	printf("Time for parallel with 2 threads: %lf seconds\n", time_o1);
	printf("Time for parallel with 4 threads: %lf seconds\n", time_o2);
	printf("Time for parallel with 8 threads: %lf seconds\n", time_o3);
	printf("Time for parallel with 32 threads: %lf seconds\n", time_o4);

    return 0;

}

