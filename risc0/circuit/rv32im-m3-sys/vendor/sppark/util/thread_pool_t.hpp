// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef __SPPARK_UTIL_THREAD_POOL_T_HPP__
#define __SPPARK_UTIL_THREAD_POOL_T_HPP__

#if __cplusplus < 201103L && !(defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)
# error C++11 or later is required.
#endif

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <deque>
#include <functional>
#include <cstdlib>
#include <cstring>
#ifdef _GNU_SOURCE
# include <sched.h>
#endif

class semaphore_t {
private:
    size_t counter;
    std::mutex mtx;
    std::condition_variable cvar;

public:
    semaphore_t() : counter(0) {}

    void notify()
    {
        std::unique_lock<std::mutex> lock(mtx);
        counter++;
        cvar.notify_one();
    }

    void wait()
    {
        std::unique_lock<std::mutex> lock(mtx);
        cvar.wait(lock, [&] { return counter != 0; });
        counter--;
    }
};

class thread_pool_t {
private:
    std::vector<std::thread> threads;

    std::mutex mtx;                     // Inter-thread synchronization
    std::condition_variable cvar;
    std::atomic<bool> done;

    typedef std::function<void()> job_t;
    std::deque<job_t> fifo;

    void init(unsigned int num_threads)
    {
        if (num_threads == 0) {
            num_threads = std::thread::hardware_concurrency();
#ifdef _GNU_SOURCE
            cpu_set_t set;
            if (sched_getaffinity(0, sizeof(set), &set) == 0) {
                size_t i, n;
                for (n = 0, i = num_threads; i--;)
                    n += CPU_ISSET(i, &set);
                if (n != 0)
                    num_threads = n;
            }
#endif
        }

        threads.reserve(num_threads);

        for (unsigned int i = 0; i < num_threads; i++)
            threads.push_back(std::thread([this]() { while (execute()); }));
    }
public:
    thread_pool_t(unsigned int num_threads = 0) : done(false)
    {   init(num_threads);   }

    thread_pool_t(const char* affinity_env) : done(false)
    {
#ifdef _GNU_SOURCE
        while ((affinity_env = getenv(affinity_env))) {
            if (affinity_env[0] != '0')
                break;
            char base = affinity_env[1];
            if (base == 'x')
                base = 16;
            else if (base == 'b')
                base = 2;
            else if (base >= '0' && base < '8')
                base = 8;
            else
                break;

            size_t len = strlen(affinity_env += 1 + (base != 8));
            if (len == 0)
                break;

            cpu_set_t oset, nset;
            CPU_ZERO(&oset);
            CPU_ZERO(&nset);

            if (sched_getaffinity(0, sizeof(oset), &oset) != 0)
                break;

            unsigned int num_threads = 0;
            for (int cpu = 0; cpu < CPU_SETSIZE && len--;) {
                char nibble = nibble_from_hex(affinity_env[len]);
                for (char mask = 1; mask < base; mask <<= 1, cpu++) {
                    if (nibble & mask) {
                        CPU_SET(cpu, &nset);
                        num_threads++;
                    }
                }
            }

            if (sched_setaffinity(0, sizeof(nset), &nset) != 0)
                break;
            init(num_threads);
            sched_setaffinity(0, sizeof(oset), &oset);

            return;
        }
#else
        (void)affinity_env;
#endif
        init(0);
    }

    virtual ~thread_pool_t()
    {
        done = true;
        cvar.notify_all();
        for (auto& tid : threads)
            tid.join();
    }

    size_t size() const { return threads.size(); }

    template<class Workable> void spawn(Workable work)
    {
        std::unique_lock<std::mutex> lock(mtx);
        fifo.emplace_back(work);
        cvar.notify_one();  // wake up a worker thread
    }

private:
    bool execute()
    {
        job_t work;
        {
            std::unique_lock<std::mutex> lock(mtx);

            while (!done && fifo.empty())
                cvar.wait(lock);

            if (done && fifo.empty())
                return false;

            work = fifo.front(); fifo.pop_front();
        }
        work();

        return true;
    }

public:
    // call work(size_t idx) with idx=[0..num_items) in parallel, e.g.
    // pool.par_map(20, [&](size_t i) { std::cout << i << std::endl; });
    template<class Workable>
    void par_map(size_t num_items, size_t stride, Workable work,
                 size_t max_workers = 0)
    {
        size_t num_steps = (num_items + stride - 1) / stride;
        size_t num_workers = std::min(size(), num_steps);
        if (max_workers > 0)
            num_workers = std::min(num_workers, max_workers);

        if (num_steps == num_workers)
            stride = (num_items + num_steps - 1) / num_steps;

        std::atomic<size_t> counter(0);
        std::atomic<size_t> done(num_workers);
        semaphore_t barrier;

        while (num_workers--) {
            spawn([&, num_items, stride, num_steps]() {
                size_t idx;
                while ((idx = counter.fetch_add(1, std::memory_order_relaxed))
                            < num_steps) {
                    size_t off = idx * stride, n = stride;
                    if (off + n > num_items)
                        n = num_items - off;
                    while (n--)
                        work(off++);
                }
                if (--done == 0)
                    barrier.notify();
            });
        }

        barrier.wait();
    }
    template<class Workable>
    void par_map(size_t num_items, Workable work, size_t max_workers = 0)
    {   par_map(num_items, 1, work, max_workers);   }

#ifdef _GNU_SOURCE
    static char nibble_from_hex(char c)
    {
        int mask, ret;

        mask = (('a'-c-1) & (c-1-'f')) >> 31;
        ret  = (10 + c - 'a') & mask;
        mask = (('A'-c-1) & (c-1-'F')) >> 31;
        ret |= (10 + c - 'A') & mask;
        mask = (('0'-c-1) & (c-1-'9')) >> 31;
        ret |= (c - '0') & mask;
        mask = ((ret-1) & ~mask) >> 31;
        ret |= 16 & mask;

        return (char)ret;
    }
#endif
};

template<class T> class channel_t {
private:
    std::deque<T> fifo;
    std::mutex mtx;
    std::condition_variable cvar;

public:
    void send(const T& msg)
    {
        std::unique_lock<std::mutex> lock(mtx);
        fifo.push_back(msg);
        cvar.notify_one();
    }

    T recv()
    {
        std::unique_lock<std::mutex> lock(mtx);
        cvar.wait(lock, [&] { return !fifo.empty(); });
        auto msg = fifo.front(); fifo.pop_front();
        return msg;
    }
};

template<typename T> class counter_t {
    struct inner {
        std::atomic<T> val;
        std::atomic<size_t> ref_cnt;
        inline inner(T v) { val = v, ref_cnt = 1; };
    };
    inner *ptr;
public:
    counter_t(T v=0) { ptr = new inner(v); }
    counter_t(const counter_t& r)
    {   (ptr = r.ptr)->ref_cnt.fetch_add(1, std::memory_order_relaxed);   }
    ~counter_t()
    {
        if (ptr->ref_cnt.fetch_sub(1, std::memory_order_seq_cst) == 1)
            delete ptr;
    }
    counter_t& operator=(const counter_t& r) = delete;
    size_t ref_cnt() const  { return ptr->ref_cnt; }
    T operator++(int) const { return ptr->val.fetch_add(1, std::memory_order_relaxed); }
    T operator++() const    { return ptr->val++ + 1; }
    T operator--(int) const { return ptr->val.fetch_sub(1, std::memory_order_relaxed); }
    T operator--() const    { return ptr->val-- - 1; }
};
#endif  // __THREAD_POOL_T_HPP__
