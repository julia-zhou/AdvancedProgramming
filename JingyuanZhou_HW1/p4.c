#include<stdio.h>
#include<stdlib.h>

double **dmatrix(size_t m, size_t n){
	double **ptr = malloc(m*sizeof(double *));
	int i;
	for ( i = 0; i < m; ++i) {
      ptr[i] = malloc(n*sizeof(double));
   }
   return ptr;
}

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);
	double **arr = dmatrix(n,n);
	int i, j;
	for (i=0;i<n; i++){
		for (j=0;j<n; j++){
			arr[i][j] = (double)i*n+j;
		}
		
	}
	for (i=0;i<n; i++){
		for (j=0;j<n; j++){
			printf("%.1f ",arr[i][j]);
		}

		printf("\n");
	}
}


