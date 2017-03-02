#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *text[500];
void alphabetize(char **text, int nlines){
	int i,j;
	char *temp;

	for(i=0; i < nlines-1 ; i++){
        for(j=i+1; j< nlines; j++)
        {
            if(strcmp(text[i],text[j]) > 0)
            {
                temp = text[i];
                text[i]= text[j];
                text[j] = temp;
                
            }
        }

	}
}
	 


int main(int argc, char *argv[]){
	
	size_t num;
	int i=0;
	int n = 0;
	for (i=0; i<500; i++){
		text[i] = malloc(sizeof(char)*200);
	}
	while (getline(&text[n], &num, stdin) != -1){
		n++;
	} 
	for (i=0; i<n;i++){
   	printf("%s", text[i]);
   }


   alphabetize(text, n);

   for (i=0; i<n;i++){
   	printf("%s", text[i]);
   }
   return 0;
}
