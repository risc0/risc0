// SPDX-License-Identifier: BSD-3-Clause
// See Notices.txt for copyright information
#include <stdint.h>
#include <softfloat.h>

// read/write helpers since Rust doesn't support C-style _Thread_local

uint_fast8_t softfloat_detectTininess_read_helper(void)
{
    return softfloat_detectTininess;
}

void softfloat_detectTininess_write_helper(uint_fast8_t v)
{
    softfloat_detectTininess = v;
}

uint_fast8_t softfloat_roundingMode_read_helper(void)
{
    return softfloat_roundingMode;
}

void softfloat_roundingMode_write_helper(uint_fast8_t v)
{
    softfloat_roundingMode = v;
}

uint_fast8_t softfloat_exceptionFlags_read_helper(void)
{
    return softfloat_exceptionFlags;
}

void softfloat_exceptionFlags_write_helper(uint_fast8_t v)
{
    softfloat_exceptionFlags = v;
}

uint_fast8_t extF80_roundingPrecision_read_helper(void)
{
    return extF80_roundingPrecision;
}

void extF80_roundingPrecision_write_helper(uint_fast8_t v)
{
    extF80_roundingPrecision = v;
}

