#include <stdio.h>
#include <stdlib.h>



int main(){
    int *vetor = (int *) calloc(10, sizeof(int));

    for(int i =0; i<10; i++){
        printf("%d", vetor[i]);
    }
    return 0;
}