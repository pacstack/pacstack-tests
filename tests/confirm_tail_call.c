/*************************************************************************************
 * Copyright (c) 2019 Xiaoyang Xu, Masoud Ghaffarinia, Wenhao Wang, and Kevin Hamlen *
 * The University of Texas at Dallas                                                 *
 * Copyright (c) 2020 Aalto University Secure Systems Group                          *
 *                                                                                   *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of   *
 * this software and associated documentation files (the "Software"), to deal in     *
 * the Software without restriction, including without limitation the rights to      *
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of  *
 * the Software, and to permit persons to whom the Software is furnished to do so,   *
 * subject to the following conditions:                                              *
 *                                                                                   *
 * The above copyright notice and this permission notice shall be included in all    *
 * copies or substantial portions of the Software.                                   *
 *                                                                                   *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR        *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS  *
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR    *
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER    *
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN           *
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.        *
 *************************************************************************************/
 
/* This file is part of the ConFIRM test suite, whose initial documentation can be
   found in the following publication:

   Xiaoyang Xu, Masoud Ghaffarinia, Wenhao Wang, Kevin W. Hamlen, and Zhiqiang Lin.
   "ConFIRM: Evaluating Compatibility and Relevance of Control-flow Integrity 
   Protections for Modern Software."  In Proceedings of the 28th USENIX Security
   Symposium, August 2019. 
   
   Modified for pacstack-tests by Thomas Nyman <thomas.nyman@aalto.fi> */

#include "confirm_setup.h"

static int zero_count = 0;
static int one_count = 0;
static int two_count = 0;
static int three_count = 0;
const int divisor = 4;

NANOSECOND start_time;
NANOSECOND end_time;
NANOSECOND total_time;

void helper();
void case0();
void case1();
void case2();
void case3();

int main()
{
    // Initialize random seed
    srand((unsigned int)time(NULL));
    // Record starting time
    start_time = get_wall_time();

    // Call a function that ends with a tail-call in an intensive loop.
    for (long long int i = 0; i < MAX_LOOP * INDCTS; i++)
    {
        helper();
    }

    // Record ending time
    end_time = get_wall_time();
    total_time = end_time - start_time;

    // Print time elapsed in the loop.
    printf("total time in nanoseconds is %llu\n", (long long unsigned int) total_time);
    
    // Print counts so that a compiler doesn't optimize too much.
    printf("%d numbers have remainder of zero modulo %d.\n", zero_count, divisor);
    printf("%d numbers have remainder of one modulo %d.\n", one_count, divisor);
    printf("%d numbers have remainder of two modulo %d.\n", two_count, divisor);
    printf("%d numbers have remainder of three modulo %d.\n", three_count, divisor);
}

void helper()
{
    void(*fptr) ();
    int r = rand();
    int remainder = r % divisor;

    if (remainder == 0)
        fptr = case0;
    if (remainder == 1)
        fptr = case1;
    if (remainder == 2)
        fptr = case2;
    if (remainder == 3)
        fptr = case3;

    // Tail-call using a function pointer. 
    fptr();
}

void case0()
{
    zero_count += 1;
}

void case1()
{
    one_count += 1;
}

void case2()
{
    two_count += 1;
}

void case3()
{
    three_count += 1;
}

