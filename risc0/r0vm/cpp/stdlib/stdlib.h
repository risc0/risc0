#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void abort(void);
void free(void* ptr);
void* malloc(size_t size);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
