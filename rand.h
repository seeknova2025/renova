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
uint32_t randint32(struct rand *r) {
    if (r->index == 0) {
        generate_numbers(r);
    }

    uint32_t y = r->states[r->index];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680;
    y ^= (y << 15) & 0xefc60000;
    y ^= (y >> 18);

    r->index = (r->index + 1) % 624; // Increment and wrap around
    return y;
}

/*we combine two 32-bit random numbers generated by Mersenne Twister
algorithm to form a 64-bit random number*/
uint64_t randint64(struct  rand *r){
    uint32_t high = randint32(r);
    uint32_t low = randint32(r);
    return ((uint64_t) high << 32) | low; 
}

/*generate a 32-bit floating point number in the range of [0,1]
Probably a better one is to choose just 24 bits according to IEEE 754. 
 */
float randfloat32(struct rand *r){
    uint32_t n = randint32(r);
    return n/(float)UINT32_MAX;
}

/*Generate a 64-bit floating point number in the range of [0,1]
Probably a better one is to choose just 53 bits according to IEEE 754 
*/
double randfloat64(struct rand *r){
    uint64_t n = randint64(r);
    return n/(double)UINT64_MAX;
}



#endif