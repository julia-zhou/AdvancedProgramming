#include<stdio.h>
#include<stdlib.h>

double **dmatrix(size_t m, size_t n){
	double **ptr = malloc(m*sizeof(double *));
	int i;
	ptr[0] = malloc(m*n*sizeof(double));

	for ( i = 1; i < m; i++) {
		ptr[i] = ptr[i-1]+n;
	}

   return ptr;
}

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);
	double **arr = dmatrix(n,n);
	int i, j, k;
	for (i=0;i<n; i++){
		for (j=0;j<n; j++){
			arr[i][j] = (double)i*n+j;
		}
		
	}
	printf("%s\n", "Matrix with 1D indexing:");
	for(k=0; k<n*n; k++){
		if ((k+1)%n == 0){
			printf("%.1f\n",arr[0][k]);
		}else{
			printf("%.1f ",arr[0][k]);
		}
	}

	printf("\n%s\n", "Matrix with 2D indexing:");
	for (i=0;i<n; i++){
		for (j=0;j<n; j++){
			printf("%.1f ",arr[i][j]);
		}

		printf("\n");
	}
}
