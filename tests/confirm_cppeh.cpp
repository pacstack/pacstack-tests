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

void throwInt();
void throwBool();
static int int_catch_count = 0;
static int bool_catch_count = 0;

int main()
{
    int r;
    
    // Initialize random seed
    srand((unsigned int)time(NULL));
    
    // Throw and catch C++ exceptions in an intensive loop, to see if a CFI solution
    // being tested provides semantic transparency.
    for (long long int i = 0; i < MAX_LOOP * CPEHTS; ++i)
    {
        r = rand();        
        try
        {
            if (r % 2 == 0)
                throwInt();
            else
                throwBool();
            
        }
        catch (int e)
        {
            int_catch_count++;
        }
        catch (bool e)
        {
            bool_catch_count++;
        }
    }

    // Print results
    printf("int_catch_count is %d\n", int_catch_count);
    printf("bool_catch_count is %d\n", bool_catch_count);
    printf("C++ exception test passed.");

    return 0;
}

void throwInt()
{
    try
    {
        throw 7;
    }
    catch (bool e)
    {
        bool_catch_count++;
    }
}

void throwBool()
{
    try
    {
        throw true;
    }
    catch (int e)
    {
        int_catch_count++;
    }
}
