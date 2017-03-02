#include<stdio.h>
#include<stdlib.h>
void heapify(int *f, int n)
{
	int i = n/2;
	for (i = n/2+1;i>=0; i--){
		while (i<n){
			int left = 2*i+1, right = 2*i+2, largest= i, temp;
			if(left < n && f[largest] < f[left]){
			 	largest = left;
			 }
			if(right < n && f[largest] < f[right]){
			 	largest = right;
			 }
			if( i != largest){
				temp = f[i];
				f[i] = f[largest];
				f[largest] = temp;
				i = largest;
			 }else{
			 	break;
			 }
		}
		 
	}
	
	
}

int * allocate_array( int argc, char * argv[])
{
	int i;
	int *arr = malloc((argc-1)*sizeof(int));
	for (i = 0; i<argc-1;++i){
		arr[i] = atoi(argv[i+1]);
	}
	return arr;
}

int test_heap( int * f, int n)
{
	int i;
	int child_A, child_B;

	for( i = 0; i < n; i++ )
	{
		child_A = ( 2 * i ) + 1;
		child_B = ( 2 * i ) + 2;

		if( child_A < n )
			if( f[i] < f[child_A] )
				return -1;
		
		if( child_B < n )
			if( f[i] < f[child_B] )
				return -1;
	}

	return 1;
}

int main(int argc, char * argv[])
{
	int result;
	int i;
	int n = argc - 1;
	int * arr = allocate_array( argc, argv );

	heapify( arr, n );
	result = test_heap( arr, n );

	for( i = 0; i < n; i++ )
		printf("%d ", arr[i]);
	printf("\n");

	if( result == 1 )
		printf("Heap test success!\n");
	else
		printf("Heap test failed.\n");

	free(arr);

	return 0;
}
