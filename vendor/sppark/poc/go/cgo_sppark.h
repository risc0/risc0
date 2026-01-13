#ifndef __CGO_SPPARK_H__
#define __CGO_SPPARK_H__

typedef struct {
    int code;
    char *message;
} Error;

typedef struct {
    int code;
    _GoString_ message;
} GoError;

#ifndef _WIN32
__attribute__((weak))   // required with go1.18 and earlier
#endif
void toGoError(GoError *go_err, Error c_err);

#define WRAP_ERR(ret_t, func, ...) __attribute__((section("_sppark"), used)) \
	static struct { Error (*call)(__VA_ARGS__); const char *name; } \
	func = { NULL, #func }; \
	static void go_##func(GoError *go_err, __VA_ARGS__)
#if 0
// For example in the import "C" section:
//
// #include "cgo_sppark.h"
// WRAP_ERR(Error, cuda_func, type1 arg1, type2 arg2)
// {   toGoError(go_err, (*cuda_func.call)(arg1, arg2);   }
//
// and then on the Go side:
    ...
    var err C.GoError
    C.go_cuda_func(&err, arg1, arg2)
    if err.code != 0 {
        panic(err.message)
    }
    ...
#endif
#endif
