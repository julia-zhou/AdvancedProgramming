#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_LINES 1000

typedef struct repeat{
    char* c;
    int freq;
}Repeat;
Repeat list[1000];
int wordnum=0;

void check(char *a, int n){
	int k,j, t= 0;


	for (k=0; k<n-1;k++){
		if(a[k] == a[k+1]){
			
			for(j=0; j<wordnum; j++){
				if (strcmp(list[j].c,a)== 0){
					list[j].freq++;
					t =1;
					break;
				}	
			}
			if(t == 0){
				
				list[wordnum].c = malloc(sizeof(char) * 500);
				strcpy(list[wordnum].c, a);
				
				list[wordnum++].freq = 1;
			}
			break;
		}
	}
}

int main(int argc, char *argv[]){
	FILE *input;
	char c = 0;
	char words[1000];
	int i=0;

	input = fopen(argv[1],"r");

	while (!feof(input)){
		while(!isalpha(c) && !feof(input)) c = fgetc(input);
		while(isalpha(c) && !feof(input)){
			words[i++] = c;
			c = fgetc(input);
		}
		words[i] = '\0';
		
		check(words,i);
		i = 0;

	}
	fclose(input);

    for (i=0; i<wordnum;i++){
    	printf("%s : %d\n",list[i].c, list[i].freq);
    }
    
    return 0;

}
