#include "rand.h"
#include <stdio.h>
int main(){
    struct rand r;
    uint32_t seed = 47;
    initialize_rand(&r, seed);
    uint32_t n = extract_number(&r);
    printf("random number: %u\n", n);
    return 0;
    
}