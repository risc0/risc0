
/*============================================================================

This C source file is part of the SoftFloat IEEE Floating-Point Arithmetic
Package, Release 3e, by John R. Hauser.

Copyright 2011, 2012, 2013, 2014, 2015 The Regents of the University of
California.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions, and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions, and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 3. Neither the name of the University nor the names of its contributors may
    be used to endorse or promote products derived from this software without
    specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS", AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ARE
DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=============================================================================*/

#include <stdbool.h>
#include <stdint.h>
#include "platform.h"
#include "internals.h"
#include "specialize.h"
#include "softfloat.h"

#include <inttypes.h>
#include <stdio.h>

bfloat16_t f32_to_bf16( float32_t a )
{
    union ui32_f32 uA;
    uint_fast32_t uiA;
    bool sign;
    int_fast16_t exp;
    uint_fast32_t frac;
    struct commonNaN commonNaN;
    uint_fast16_t uiZ, frac16;
    union ui16_bf16 uZ;

    /*------------------------------------------------------------------------
    *------------------------------------------------------------------------*/
    uA.f = a;
    uiA = uA.ui;
    sign = signF32UI( uiA );
    exp  = expF32UI( uiA );
    frac = fracF32UI( uiA );
    /*------------------------------------------------------------------------
    *------------------------------------------------------------------------*/
    // infinity or NaN cases
    if ( exp == 0xFF ) {
        if ( frac ) {
            // NaN case
            softfloat_f32UIToCommonNaN( uiA, &commonNaN );
            uiZ = softfloat_commonNaNToBF16UI( &commonNaN );
        } else {
            // infinity case
            uiZ = packToBF16UI( sign, 0xFF, 0 );
        }
        goto uiZ;
    }
    /*------------------------------------------------------------------------
    *------------------------------------------------------------------------*/
    // frac is a 24-bit mantissa, right shifted by 9
    // In the normal case, (24-9) = 15 are set 
    frac16 = frac>>9 | ((frac & 0x1FF) != 0);
    if ( ! (exp | frac16) ) {
        uiZ = packToBF16UI( sign, 0, 0 );
        goto uiZ;
    }
    /*------------------------------------------------------------------------
    *------------------------------------------------------------------------*/
    // softfloat_roundPackToBF16 exponent argument (2nd argument)
    // must correspond to the exponent of fracIn[13] bits
    // (fracIn is the 3rd and last argument) 
    uint_fast32_t mask = exp ? 0x4000 : 0x0; // implicit one mask added if input is a normal number
    // exponent for the lowest normal and largest subnormal should be equal
    // but is not in IEEE encoding so mantissa must be partially normalized
    // (by one bit) for subnormal numbers. Such that (exp - 1) corresponds
    // to the exponent of frac16[13]
    frac16 = frac16 << (exp ? 0 : 1);
    return softfloat_roundPackToBF16( sign, exp - 1, frac16 | mask );
 uiZ:
    uZ.ui = uiZ;
    return uZ.f;

}

