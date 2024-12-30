#ifndef RAND_H
#define RAND_H
/*
Implement Mersenne Twister algorithm for generating random numbers
The basis of Mersenne Twister algorithm stems from the Linear Feedback Shift Register. 
Given an n bits array, a Linear Feedback Shift Register, at each step, performs 
a shift right of 1 bit. The most significant bit is filled in as a XOR of certain positions 
in a string (polynomial in GF(2)). If the polynomial is irreducible and primitive, the 
period of the sequence reaches the maximum length of 2^n -1. Note that a sequence of all 0s will just lead to 0.
The algorithm operates on a 624 elements, each with 32 bits. The 32 bits from positions [1, 31] are not used,
thus, n = 624 * 32 - 31 = 19937. The period of the sequence is 2^19937 -1, a prime number (Mersenne prime number) - thus the name.

*/
#endif