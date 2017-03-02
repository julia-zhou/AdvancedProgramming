#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void work_kernel_dynamic(double **U, int m, int n)
{
	int i,j;
	double a = 1.0, b = 0.5, c;

	for( i=1; i < (m-1); i++)
		for( j=1; j < (n-1); j++)
		{
			c = ( a * (U[i+1][j] + U[i-1][j]) ) +
		            ( b * (U[i][j+1] + U[i][j-1]) ) +
	                    ( (1 - (2*a) - (2*b)) * U[i][j] );
		}

	return;
}
int M;
int N;
void work_kernel_static(double U[M][N], int m, int n)
{
	int i,j;
	double a = 1.0, b = 0.5, c;

	for( i=1; i < (m-1); i++)
		for( j=1; j < (n-1); j++)
		{
			c = ( a * (U[i+1][j] + U[i-1][j]) ) +
		            ( b * (U[i][j+1] + U[i][j-1]) ) +
	                    ( (1 - (2*a) - (2*b)) * U[i][j] );
		}

	return;
}



int main(int argc, char * argv[])
{
	
	int m = 1000;
	int n = 1000;
	int i,j;
	
	clock_t begina, enda, beginb, endb,beginc, endc;
	double time_a, time_b,time_c;
	M = 1000;
	N = 1000;

	/* Declare and allocate your arrays A,B,C */
	/*A*/
	double A[m][n];
	
	i = 0;
	while(i < m) {
		j = 0;
		while(j < n){
			A[i][j] = 0;
			j++;
		}
		i++;
	}
	/*B*/
	double **B = malloc(m*sizeof(double *));

	

	for(i = 0 ; i < m ; i++) {
		*(B + i) = malloc(n * sizeof(double));
	}
	
	

   /*C*/
    double **C = malloc(m*sizeof(double *));
	
	for(i = 0 ; i < m ; i++) {
		*(C + i) = malloc(n * sizeof(double));
	}

	
	/* time A */
	begina = clock();

	work_kernel_static( A, m, n);
	enda = clock();
    time_a = (double)(enda - begina) / CLOCKS_PER_SEC;
	
	/* time B */
	beginb = clock();
	work_kernel_dynamic( B, m, n);
	endb = clock();
    time_b = (double)(endb - beginb) / CLOCKS_PER_SEC;

	/* time C */
	beginc = clock();
	work_kernel_dynamic( C, m, n);
	endc = clock();
	time_c = (double)(endc - beginc) / CLOCKS_PER_SEC;

	/* Print out timing to stdout in seconds for each array */
	printf("Timing array A: %f\n", time_a);
	printf("Timing array B: %f\n", time_b);
	printf("Timing array C: %f\n", time_c);
	
	/* Free memory*/
	
	free(C);
	free(B);

	
	return 0;

}
