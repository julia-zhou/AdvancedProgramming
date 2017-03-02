#include<stdio.h>
#include<stdlib.h>
#define MAX_LINES 1000
#define MAX_CHAR_PER_LINE 1000
char text[MAX_LINES][MAX_CHAR_PER_LINE];

int read_file (int argc, char *argv[]){
	
	FILE *input;
	size_t num = 1000;
	int i=0;
	input = fopen(argv[1],"r");
	while (fgets(text[i], num, input) != NULL){
		i++;
	}
	fclose(input);
	return i;
	
}

int main(int argc, char *argv[]){
	int n = read_file(argc, argv);
	int i;
	for (i=0; i<n;i++){
   		printf("%s", text[i]);
    }
}
