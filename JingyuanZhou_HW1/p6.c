#include<stdio.h>
#include<stdlib.h>

double ***d3darr(size_t l, size_t m, size_t n) {
	
	double *one_d = malloc(l * m * n * sizeof(double));
	double **two_d = malloc(l * m * sizeof(double*));
	double ***three_d = malloc(l * sizeof(double**));

	int i , j;

	for(i = 0 ; i < l; i++) {

		//printf("%d ", i*m);
		three_d[i] = two_d + i * m;
		
		for(j = 0; j < m ; j++) {
			two_d[j] = one_d + (i * m)*(n) + (j * n);
			

		}
	}

	return three_d;
}

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);
	double ***arr = d3darr(n,n,n);
	int i, j, k, a, l;
	for (i=0;i<n; i++){
		for (j=0;j<n; j++){
			for (l=0;l<n; l++){
				arr[i][j][l] = (double)i*j*n+j*n+l;
			}
		}
		
	}
	printf("%s\n", "Matrix with 1D indexing:");
	for(k=0; k<n*n*n; k++){
		if ((k+1)%n == 0){
			printf("%.1f\n",arr[0][k]);
		}else if((k+1)%(n*n)==0){
			printf("%.1f\n\n",arr[0][k]);
		}
		else{
			printf("%.1f ",arr[0][k]);
		}
	}

	printf("%s\n", "Matrix with 3D indexing:");
	for (i=0;i<n; i++){
		for (j=0;j<n; j++){
			for (a=0;a<n; a++){
				printf("%.1f ",arr[i][j][a]);
			}
			printf("\n");
		}
		printf("\n");

		
	}
}
