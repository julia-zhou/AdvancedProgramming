#include<stdio.h>
#include<stdlib.h>
#include<float.h>

/*
Reference: http://stackoverflow.com/questions/1697425/how-to-print-out-each-bit-of-a-floating-point-number
Most negative value of a float: 
-FLT_MAX = -340282346638528859811704183484516925440.000000
Max value of a float
FLT_MAX = 340282346638528859811704183484516925440.000000
*/
int bit_return(int a, int loc){
    int b = a & 1<<loc;

    if (b == 0) return 0;
    else return 1; 
}

int main(int argc, char **argv){
    
    float a = atof(argv[1]); 
    int *b;
    int i;
    b = (int*)&a;

    
    for (i = 31; i >= 0; i--){
        if (i == 31 || i == 23){
            printf("%d ",bit_return(*b,i));}
        else if (i == 0){
            printf("%d\n",bit_return(*b,i));
        }else{
            printf("%d",bit_return(*b,i));
        }
        
    }

    return 0;
}
