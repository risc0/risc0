// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_UTIL_EXCEPTION_HPP__
#define __SPPARK_UTIL_EXCEPTION_HPP__

#include <cstdio>
#include <cstring>
#include <string>
#include <stdexcept>

class sppark_error : public std::runtime_error {
    int _code;

    template<typename... Types>
    inline std::string fmt_errno(int errnum, const char* fmt, Types... args)
    {
        const size_t ERRLEN = 48;
        size_t len = std::snprintf(nullptr, 0, fmt, args...);
        std::string ret(len + ERRLEN, '\0');
        std::snprintf(&ret[0], len + 1, fmt, args...);
        auto errmsg = &ret[len];
#if defined(_WIN32)
        (void)strerror_s(errmsg, ERRLEN, errnum);
#elif defined(_GNU_SOURCE)
        auto errstr = strerror_r(errnum, errmsg, ERRLEN);
        if (errstr != errmsg)
            strncpy(errmsg, errstr, ERRLEN - 1);
#else
        (void)strerror_r(errnum, errmsg, ERRLEN);
#endif
        ret.resize(len + std::strlen(errmsg));
        return ret;
    }

public:
    sppark_error(int err, const std::string& reason) : std::runtime_error{reason}
    {   _code = err;   }
    sppark_error(int err, const char* msg = "") : std::runtime_error{fmt_errno(err, "%s", msg)}
    {   _code = err;   }
    template<typename... Types>
    sppark_error(int err, const char* fmt, Types... args) : std::runtime_error{fmt_errno(err, fmt, args...)}
    {   _code = err;   }
    inline int code() const
    {   return _code;   }
};

template<typename... Types>
inline std::string fmt(const char* fmt, Types... args)
{
    size_t len = std::snprintf(nullptr, 0, fmt, args...);
    std::string ret(++len, '\0');
    std::snprintf(&ret.front(), len, fmt, args...);
    ret.resize(--len);
    return ret;
}

#endif
