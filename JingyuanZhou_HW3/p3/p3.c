#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define NUM 68

typedef struct _bin{
	int lower;
	int upper;
}bin;

double *all[1000];
int length[1000];

double x_max = -DBL_MAX;
double x_min = DBL_MAX;

int m; //number of bins
int n_b; //number of values in each bin

void read_file(char* file) {
    int len;
    double data;
    FILE *f = fopen(file, "r");
    for(int i = 0; i < NUM; i++) {
        if(fscanf(f, "%d", &len) == EOF) break;
        //printf("line %d with %d data\n", i, len);
        length[i] = len;
        all[i] = malloc(len * sizeof(double));
        for(int j = 0; j < len; j++) {
            if(fscanf(f, "%lf", &data) == EOF) break;
            if(data > x_max){
            	 x_max = data;
            }
            if(data < x_min){
            	x_min = data;
            }
            all[i][j] = data;
        }
    }
    fclose(f);
    return;
}

bin ** generate_bin(double *arr, int m, int arr_index){
	bin **grid = (bin **)malloc(m*sizeof(bin*));
	bin *b;
	for (int i=0; i<m; i++){
		b = (bin *)malloc(sizeof(bin));
		b->lower = length[arr_index]-1;
		b->upper = 0;
		grid[i] = b;
	}
	
	//printf("True value of size %d\n", length[arr_index]);
	//for each element in the array
	for (int i=0; i< length[arr_index]; i++){
		//printf("Array element %f\n", arr[i]);
		//search through each bin
		for (int j=0;j<m;j++){
			//printf("we are here element# %d, bin# %d\n",i, j);
			//if we find the bin, break from the for loop
			//printf("bin number %d, lower %f, upper %f\n", j, x_min + j*n_b, x_min + (j+1)*n_b);

			if (arr[i]>= x_min + j*n_b && arr[i]<= x_min + (j+1)*n_b){

				if (grid[j]->lower == length[arr_index]-1){
					grid[j]->lower = i;
				// }
				
				// if (arr[i]< arr[grid[j]->lower]){
				// 	grid[j]->lower = i;
					//printf("Bin %d set lower as %d\n", j, i);
				}else if (arr[i]>=arr[grid[j]->upper]){
					grid[j]->upper = i;
					// if (j<m-1 && i<length[arr_index]-2){
					// 	grid[j+1]->lower = i+1;
					// }
					
					//printf("Bin %d set upper as %d\n", j, i);
				}

				break;
			}
		}
	}
	return grid;
}

// return index of value in A greater than q that is closest to q
int binary_search(double *A, double q, int min, int max)
{
  int mid;
  if (max == 0) return 0;
  // make sure we are not reading off the end of A
  if(q < A[min]) return 0;
  else if(q > A[max]) return max;

  // start binary search
  while(max >= min){
    mid = min + floor((max-min) / 2.0);
    if(q < A[mid]) max = mid - 1;
    else if(q > A[mid]) min = mid + 1;
    else return mid;
  }
  return max + 1;
}

//return index of the value in A
int bin_search (double *A, double q, int m, int arr_index){

	bin **grid = generate_bin(A,m,arr_index);

	int num = q/n_b;
	int index = binary_search(A, q, grid[num]->lower, grid[num]->upper);
	for(int i = 0; i < m; i++) {
		free(grid[i]);
	}
	return index;

}

double randD(double a, double b) {
    srand((unsigned)time(NULL));  
    double range = a - b, res;
    if(range == 0) return a;
    res = rand() / (double)RAND_MAX;
    return res * range + b;   
 }


int main() {

    read_file("arrays.txt");
    time_t begin, end;
    double time;
    int memory;

    //finding the best number of bins
	//m=50; //set the number of bins
    //n_b = (int)(x_max-x_min)/m+1; //number of values in each bin

    int  a[] = {5,10,30,50,75,150};
    double random_num[] = {6.71874999999999942E-011, 2.74226600000000009E-008,
    						2.25682400000000013E-005, 2.34949900000000005E-005,
    						7.81575199999999997E-005, 1.08882999999999994E-004};

    for (int j = 0; j<6; j++){
    	//printf("%d\n", a[j]);
		begin = clock();
		m = a[j];
		n_b = (int)(x_max-x_min)/m+1; 
		for (int i= 0; i<NUM; i++){
			bin_search(all[i], random_num[0], m,i);
		}
		
	
		end = clock();
		printf("Time with %d numbers of bins: %ld\n", a[j], (end-begin));
    }


	for(int i = 0; i < NUM; i++) {
		free(all[i]);
	}


}
