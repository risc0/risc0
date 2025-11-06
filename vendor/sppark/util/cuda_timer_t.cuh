// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_UTIL_CUDA_TIMER_T_CUH__
#define __SPPARK_UTIL_CUDA_TIMER_T_CUH__

#include <iostream>
#include <iomanip>
#include <sstream>

class cuda_timer_t {
    cudaEvent_t begin, end;
    cudaStream_t current_stream;
    bool started = false;
public:
    cuda_timer_t() : begin(nullptr), end(nullptr)
    {
        CUDA_OK(cudaEventCreate(&begin));
        CUDA_OK(cudaEventCreate(&end));
    }

    ~cuda_timer_t()
    {
        if (begin) cudaEventDestroy(begin);
        if (end) cudaEventDestroy(end);
    }

    inline void start(cudaStream_t stream = 0)
    {
        current_stream = stream;
        started = true;
        CUDA_OK(cudaEventRecord(begin, stream));
    }

    inline float get_elapsed()
    {
        float elapsed = -1;

        if (started) {
            started = false;

            CUDA_OK(cudaEventRecord(end, current_stream));
            CUDA_OK(cudaEventSynchronize(end));
            CUDA_OK(cudaEventElapsedTime(&elapsed, begin, end));
        }

        return elapsed;
    }

    friend std::ostream& operator<<(std::ostream& os, cuda_timer_t& timer)
    {
        float elapsed = timer.get_elapsed();

        std::stringstream ss;
        ss << std::fixed << std::setprecision(2);

        if (elapsed == -1)
            ss << "timer not started";
        else if (elapsed < 1)
            ss << elapsed * 1000 << " μs";
        else if (elapsed >= 1000)
            ss << elapsed / 1000 << " s";
        else
            ss << elapsed << " ms";

        return os << ss.str();
    }
};

#endif
