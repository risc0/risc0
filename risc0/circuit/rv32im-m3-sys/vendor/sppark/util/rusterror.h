// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_UTIL_RUSTERROR_H__
#define __SPPARK_UTIL_RUSTERROR_H__

#ifdef __cplusplus
# include <string>
# include <cstring>
#else
# include <string.h>
#endif
#ifdef _MSC_VER
# define strdup _strdup
#endif

struct RustError { /* to be returned exclusively by value */
    int code;
    char *message;
#ifdef __cplusplus
    RustError(int e = 0) : code(e)
    {   message = nullptr;   }
    RustError(int e, const std::string& str) : code(e)
    {   message = str.empty() ? nullptr : strdup(str.c_str());   }
    RustError(int e, const char *str) : code(e)
    {   message = str==nullptr ? nullptr : strdup(str);   }
    // no destructor[!], Rust takes care of the |message|

    using by_value = struct {
        int code;
        char *message;
    };
    operator by_value() const { return {code, message}; }
#endif
};
#ifdef _MSC_VER
# undef strdup
#endif
#ifndef __cplusplus
typedef struct RustError RustError;
#endif

#endif
