#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAP_MISSING -3  /* No such element */
#define MAP_FULL -2 	/* Hashmap is full */
#define MAP_OMEM -1 	/* Out of Memory */
#define MAP_OK 0 	/* OK */

#define INITIAL_SIZE (256)
#define MAX_CHAIN_LENGTH (8)

typedef struct list_element {
    struct list_element* next;
    void* data;
}element;


element* newElement(void* data) {
    element* n = malloc(sizeof(element));
    n -> data = data;
    n -> next = NULL;
    return n;
}

element* blankElement() {
    element* n = malloc(sizeof(element));
    n -> data = NULL;
    n -> next = NULL;
    return n;
}

void freeElement(element* n) {
    if(n -> next == NULL) {
        free(n);
        return;
    }
    freeElement(n -> next);
    free(n);
}

int listadd(element* n, void* data, int(* equals)(void* a, void*b)) {
    while(n -> next) {
        if(equals(data, n -> next -> data)) return 0;
        n = n -> next;
    }
    n -> next = newElement(data);
    return 1;
}

typedef struct hashmap{
    element ** map;
    int n_b;
    int(* hashFunction)(const void* key);
    int(* equals)(void* a, void*b);
}Hashmap;

void create(Hashmap *m) {
    m -> map = malloc(sizeof(element*) * (m -> n_b));
    for(int i = 0; i < m -> n_b; i++){
    	(m -> map)[i] = blankElement();
    }
    return;
}
int add(Hashmap *m, void* data) {
    int index = m -> hashFunction(data) % (m -> n_b);
    return listadd((m -> map)[index], data,  m -> equals);
}

void freemap(Hashmap *m) {
    for(int i = 0; i < m -> n_b; i++){
    	freeElement((m -> map)[i]);
    } 
    free(m -> map);
    free(m);
}


int uniq(void *f, int n, int sz, int (*equals)(void *, void *), int (*h)(const void *key)){

	int i;
	int c_num=0; //number in the unique array


	Hashmap *mymap = malloc(sizeof(Hashmap));

    mymap -> hashFunction = h;
    mymap -> equals = equals;
    mymap -> n_b = 2000;
    create(mymap);

	for (i=0;i<n;i++){
		if (add(mymap, f+i*sz)){
			c_num ++;
		}
	}

	freemap(mymap);
 	return c_num;

}

int equal(void* a, void* b) {
    int *A = (int*) a;
    int *B = (int*) b;
    return *A == *B;
}

int h(const void* key) {
    int* a = (int*) key;
    return *a; 
}

int main() {
    
    printf("Original array is: ");
    int a[10];
    for(int i = 0; i < 10; i++) {
        a[i] = (rand()/11+23)%44;
        printf("%d ", a[i]);
        
    }
    printf("\n");
    
    int c_num = uniq(a, 10, sizeof(int), equal, h);
    printf("Number of unique values in the array is %d\n", c_num);

        
}