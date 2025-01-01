#ifndef RAND_H
#define RAND_H
#include<stdlib.h>
/*
Implement Mersenne Twister algorithm for generating random numbers
The basis of Mersenne Twister algorithm stems from the Linear Feedback Shift Register. 
Given an n bits array, a Linear Feedback Shift Register, at each step, performs 
a shift right of 1 bit. The most significant bit is filled in as a XOR of certain positions 
in a string (polynomial in GF(2)). If the polynomial is irreducible and primitive, the 
period of the sequence reaches the maximum length of 2^n -1. Note that a sequence of all 0s will just lead to 0.
The algorithm operates on a 624 elements, each with 32 bits. The 31 bits from positions [1, 31] are not used,
thus, n = 624 * 32 - 31 = 19937. The period of the sequence is 2^19937 -1, a prime number (Mersenne prime number) - thus the name.
Of course, the Mersenne Twister is more complicated than the
LFSR as one works on the software stack, the other works on 
hardware.
*/
struct rand
{
    uint32_t states[624];
    int index;
};

void initialize_rand(struct rand *r,uint32_t seed){
    r->states[0] = seed;
    for(int i = 1; i < 624; i++){
        r->states[i] = 0x6c078965 * (r->states[i-1] ^ (r->states[i-1] >> 30)) + i;
    }
    r->index = 0;
}
void generate_numbers(struct rand *r){
    for(int i = 0; i < 624; i++){
        uint32_t y = (r->states[i] & 0x80000000) + (r->states[ (i +1) % 624] & 0x7fffffff);
        r->states[i] = r->states[(i + 397) % 624] ^ (y >> 1);
        if (y %2 != 0){
            r->states[i] ^= 0x9908b0df;
            
        }
    }

}

#endif