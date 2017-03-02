#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
	int num,a,b,c,d,res;

	num = atoi(argv[1]);
	
	a =  num>>24;
	b = ((num<<8)>>24)<<8;
	c = ((num<<16)>>24)<<16;
	d = num<<24;

	res = a|b|c|d;

	printf("%d\n", res);

	return 0;

}


