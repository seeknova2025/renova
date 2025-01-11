#include "rand.h"
#include <stdio.h>
int main(){
    struct rand r;
    uint32_t seed = 137;
    initialize_rand(&r, seed);
    for(int i = 0; i < 10; i++){
        uint32_t n = randint32(&r);
        printf("random number: %u\n", n);
    }
    //create 10 random 64bit numbers
    for (int i = 0; i < 10; i++){
        uint64_t n  = randint64(&r);
        printf("64 bits: %llu\n", n);
    }
    //create a permutation of size 10
    //void random_permutation(int *data, int n, struct rand *r){
    
    int data[10];

    for(int i = 0; i < 5; i++){

        random_permutation(data,10, &r);
        for(int j = 0; j < 10; j++){
            printf("%d ", data[j]);
        }
        printf("\n");
    }

    return 0;
    
}