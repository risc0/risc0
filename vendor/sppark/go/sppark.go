// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

package sppark

// #cgo linux LDFLAGS: -ldl -Wl,-rpath,"$ORIGIN"
//
// #ifndef GO_CGO_EXPORT_PROLOGUE_H
// #ifdef _WIN32
// # include <windows.h>
// static char hex_from_nibble(unsigned char nibble)
// {
//     int mask = (9 - (nibble &= 0xf)) >> 31;
//     return (char)(nibble + ((('a'-10) & mask) | ('0' & ~mask)));
// }
// #else
// # include <dlfcn.h>
// #endif
// #include <string.h>
// #include <stdlib.h>
// #ifdef __SPPARK_CGO_DEBUG__
// # include <stdio.h>
// #endif
//
// #include "cgo_sppark.h"
//
// typedef struct {
//     void *ptr;
// } gpu_ptr_t;
//
// #define WRAP(ret_t, func, ...) __attribute__((section("_sppark"), used)) \
//	static struct { ret_t (*call)(__VA_ARGS__); const char *name; } \
//	func = { NULL, #func }; \
//	static ret_t go_##func(__VA_ARGS__)
//
// WRAP(gpu_ptr_t, clone_gpu_ptr_t, gpu_ptr_t *ptr)
// {   return (*clone_gpu_ptr_t.call)(ptr);   }
//
// WRAP(void, drop_gpu_ptr_t, gpu_ptr_t *ptr)
// {   (*drop_gpu_ptr_t.call)(ptr); ptr->ptr = NULL;   }
//
// WRAP(_Bool, cuda_available, void)
// {   return (*cuda_available.call)();   }
//
// WRAP(void, drop_error_message, char *ptr)
// {   (*drop_error_message.call)(ptr);   }
//
// void toGoString(_GoString_ *, char *);
//
// void toGoError(GoError *go_err, Error c_err)
// {
//     go_err->code = c_err.code;
//     if (c_err.message != NULL) {
//         toGoString(&go_err->message, c_err.message);
//         go_drop_error_message(c_err.message);
//         c_err.message = NULL;
//     }
// }
//
// typedef struct {
//     void *value;
//     const char *name;
// } dlsym_t;
//
// static _Bool go_load(_GoString_ *err, _GoString_ so_name)
// {
//     static void *hmod = NULL;
//     void *h;
//
//     if ((h = hmod) == NULL) {
//         size_t len = _GoStringLen(so_name);
//         char fname[len + 1];
//
//         memcpy(fname, _GoStringPtr(so_name), len);
//         fname[len] = '\0';
// #ifdef _WIN32
//         h = LoadLibraryA(fname);
// #else
//         h = dlopen(fname, RTLD_NOW|RTLD_GLOBAL);
// #endif
//         if ((hmod = h) != NULL) {
//             extern dlsym_t __start__sppark, __stop__sppark;
//             dlsym_t *sym;
//
//             for (sym = &__start__sppark; sym < &__stop__sppark; sym++) {
// #ifdef _WIN32
//                 sym->value = GetProcAddress(h, sym->name);
// #else
//                 sym->value = dlsym(h, sym->name);
// #endif
//                 if (sym->value == NULL) {
//                     h = NULL;
//                     break;
//                 }
// #ifdef __SPPARK_CGO_DEBUG__
//                 fprintf(stderr, "%p %s\n", sym->value, sym->name);
// #endif
//             }
//         }
//     }
//
//     if (h == NULL) {
// #ifdef _WIN32
//         char *msg = NULL;
//         unsigned int win_err = GetLastError();
//         if (FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER,
//                            NULL, win_err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//                            (char *)&msg, 0, NULL)) {
//             toGoString(err, msg);
//             LocalFree(msg);
//         } else {
//             static char buf[24] = "WIN32 Error #0x";
//             msg = buf + 15;
//             for (int i = 32; i -= 8;) {
//                 unsigned int hex;
//                 if ((hex = win_err>>i)) {
//                     *msg++ = hex_from_nibble(hex>>4);
//                     *msg++ = hex_from_nibble(hex);
//                 }
//             }
//             *msg++ = hex_from_nibble(win_err>>4);
//             *msg++ = hex_from_nibble(win_err);
//             *msg = '\0';
//             toGoString(err, buf);
//         }
//         if (hmod) FreeLibrary(hmod);
// #else
//         toGoString(err, dlerror());
//         if (hmod) dlclose(hmod);
// #endif
//         hmod = h;
//     }
//
//     return h != NULL;
// }
// #endif
import "C"

import (
    blst "github.com/supranational/blst/build"
    "io"
    "log"
    "os"
    "os/exec"
    "path/filepath"
    "runtime"
    "strconv"
    "strings"
)

//export toGoString
func toGoString(go_str *string, c_str *C.char) {
    *go_str = C.GoString(c_str)
}

var SrcRoot string

func init() {
    if _, self, _, ok := runtime.Caller(0); ok {
        SrcRoot = filepath.Dir(filepath.Dir(self))
    }
}

func Load(baseName string, options ...string) {
    goArch := runtime.GOARCH
    if goArch != "amd64" && goArch != "arm64" {
        log.Panicf("%s: unsupported GOARCH", goArch)
    }

    baseName = strings.TrimSuffix(baseName, filepath.Ext(baseName))

    var dst, src string

    if exe, err := os.Executable(); err == nil {
        dst = filepath.Join(filepath.Dir(exe), filepath.Base(baseName))
        if runtime.GOOS == "windows" {
            dst += ".dll"
        } else {
            dst += ".so"
        }
    } else {
        log.Panic(err)
    }

    if _, caller, _, ok := runtime.Caller(1); ok {
        src = filepath.Join(filepath.Dir(caller), baseName + ".cu")
    } else {
        log.Panic("passed the event horizon")
    }

    // To facilitate the edit-compile-run turnaround check if the source
    // .cu file is writable and see if it's newer than the destination
    // shared object...
    rebuild := false
    if fd, err := os.OpenFile(src, os.O_RDWR, 0); err == nil {
        src_stat, _ := fd.Stat()
        fd.Close()
        dst_stat, err := os.Stat(dst)
        rebuild = err != nil || src_stat.ModTime().After(dst_stat.ModTime())
    }

    var go_err string

    if rebuild || !bool(C.go_load(&go_err, dst)) {
        if !build(dst, src, options...) {
            log.Panic("failed to build the shared object")
        }
        go_err = ""
        if !C.go_load(&go_err, dst) {
           log.Panic(go_err)
        }
    }
}

func is_cuda_flag_supported(nvcc string, flag string) bool {
    cmd := exec.Command(nvcc, flag, "--dryrun", "-c", "-x", "cu", os.DevNull)
    _, err := cmd.Output()
    return err == nil
}

func is_rocm_flag_supported(hipcc string, flag string) bool {
    cmd := exec.Command(hipcc, flag, "-fsyntax-only", "-x", "hip", os.DevNull,
                               "-Wno-unused-command-line-argument")
    _, err := cmd.Output()
    return err == nil
}

func is_arch_native(custom_args... string) bool {
    for _, arg := range custom_args {
        if arg == "-arch=native" {
            return true
        }
    }
    return false
}

func build(dst string, src string, custom_args ...string) bool {
    nvcc, ok := os.LookupEnv("NVCC")
    if !ok {
        nvcc = "nvcc"
    }
    nvcc, _ = exec.LookPath(nvcc)

    hipcc, ok := os.LookupEnv("HIPCC")
    if !ok {
        hipcc = "hipcc"
    }
    hipcc, _ = exec.LookPath(hipcc)

    if len(nvcc) == 0 && len(hipcc) == 0 {
        log.Fatal("no CUDA or ROCm compiler found")
        return false
    }

    if len(nvcc) != 0 && len(hipcc) != 0 {
        cmd := exec.Command(nvcc, filepath.Join(SrcRoot, "rust", "src", "cuda_available.cpp"),
                                  "-o", "cuda_available.exe")
        if out, err := cmd.CombinedOutput(); err != nil {
            log.Fatal(cmd.String(), "\n", string(out))
            return false
        }
        cmd = exec.Command("./cuda_available.exe")
        if err := cmd.Run(); err != nil {
            nvcc = ""
        }
        os.Remove("cuda_available.exe")
    }

    cc, ok := os.LookupEnv("CC")
    if !ok {
        go_env_CC, err := exec.Command("go", "env", "CC").Output()
        if err != nil {
            log.Fatal("failed to execute 'go env CC': ", err)
            return false
        }
        cc = strings.TrimSpace(string(go_env_CC))
    }

    cmd := exec.Command(cc, "-O2", "-fPIC", "-c",
                            filepath.Join(blst.SrcRoot, "build", "assembly.S"),
                            filepath.Join(blst.SrcRoot, "src", "cpuid.c"))
    if out, err := cmd.CombinedOutput(); err != nil {
        log.Fatal(cmd.String(), "\n", string(out))
        return false
    }

    defer os.Remove("assembly.o")
    defer os.Remove("cpuid.o")

    var args []string

    args = append(args, "-shared", "-o", dst, src)
    args = append(args, "-I" + SrcRoot)
    args = append(args, "-I" + filepath.Join(blst.SrcRoot, "src"))
    args = append(args, "-DTAKE_RESPONSIBILITY_FOR_ERROR_MESSAGE")
    args = append(args, filepath.Join(SrcRoot, "util", "all_gpus.cpp"))

    if len(nvcc) != 0 {
        if runtime.GOOS != "windows" {
            if cxx, ok := os.LookupEnv("CXX"); ok {
                args = append(args, "-ccbin", cxx)
            }
            args = append(args, "-Xcompiler", "-fPIC,-fvisibility=hidden")
            args = append(args, "-Xlinker", "-Bsymbolic")
        }
        args = append(args, "assembly.o", "cpuid.o")
        // Application is free to pass own -arch, which will override
        // this one, with a warning though, but those are not displayed
        // by default...
        if !is_arch_native(custom_args...) {
            args = append(args, "-arch=sm_80")
            if is_cuda_flag_supported(nvcc, "-arch=sm_70") {
                args = append(args, "-gencode", "arch=compute_70,code=sm_70", "-t0")
            } else if is_cuda_flag_supported(nvcc, "-arch=sm_75") {
                args = append(args, "-gencode", "arch=compute_75,code=sm_75", "-t0")
            }
        }
        args = append(args, "-cudart=shared")
    } else {
        nvcc = hipcc
        if runtime.GOOS != "windows" {
            args = append(args, "-fPIC", "-fvisibility=hidden", "-Wl,-Bsymbolic")
        }
        args = append(args, "-include", "util/cuda2hip.hpp")
        args = append(args, "-x", "none", "assembly.o", "cpuid.o")
        // Unlike nvcc hipcc accepts multiple --offload-arch, which are
        // cumulative...
        if is_arch_native(custom_args...) {
            args = append(args, "--offload-arch=native")
        } else {
            if is_rocm_flag_supported(hipcc, "--offload-arch=gfx1200") {
                args = append(args, "--offload-arch=gfx1201,gfx1200")
            }
            if is_rocm_flag_supported(hipcc, "--offload-arch=gfx1100") {
                args = append(args, "--offload-arch=gfx1102,gfx1101,gfx1100")
            }
            args = append(args, "--offload-arch=gfx1034,gfx1032,gfx1031,gfx1030")
            args = append(args, "--offload-arch=gfx942,gfx90a,gfx908")
            args = append(args, "-parallel-jobs=" + strconv.Itoa(runtime.GOMAXPROCS(0)))
        }
        if runtime.GOOS == "windows" {
            args = append(args, "-Wl,-nodefaultlib:libcmt", "-lmsvcrt")
        }
    }

    src = filepath.Dir(src)
    for _, arg := range custom_args {
        if strings.HasPrefix(arg, "-") {
            if nvcc == hipcc && strings.HasPrefix(arg, "--offload-arch=") {
                args = append(args, arg)
            } else if nvcc != hipcc || !strings.HasPrefix(arg, "-arch=") {
                args = append(args, arg)
            }
        } else if strings.HasPrefix(arg, "?cuda-") {
            if nvcc != hipcc {
                args = append(args, arg[5:])
            }
        } else if strings.HasPrefix(arg, "?rocm-") {
            if nvcc == hipcc {
                args = append(args, arg[5:])
            }
        } else {
            file := filepath.Join(src, arg)
            if _, err := os.Stat(file); os.IsNotExist(err) {
                args = append(args, arg)
            } else {
                args = append(args, file)
            }
        }
    }

    if sccache, err := exec.LookPath("sccache"); err == nil {
        args = append([]string{nvcc}, args...)
        nvcc = sccache
    }

    cmd = exec.Command(nvcc, args...)
    if nvcc == hipcc {
        cmd.Env = append(os.Environ(), "HIP_PLATFORM=amd")
    }

    out, err := cmd.CombinedOutput()
    if err != nil {
        os.Remove("assembly.o")
        os.Remove("cpuid.o")
        log.Fatal(cmd.String(), "\n", string(out))
        return false
    }

    if cgo_cflags, ok := os.LookupEnv("CGO_CFLAGS");
        ok && strings.Contains(cgo_cflags, "__SPPARK_CGO_DEBUG__") {
        log.Print(cmd.String(), "\n", string(out))
    }

    return true
}

func Exfiltrate(optional ...string) error {
    exe, _ := os.Executable()
    dir := filepath.Dir(exe)

    var glob string
    if runtime.GOOS == "windows" {
        glob = "*.dll"
    } else {
        glob = "*.so"
    }
    files, _ := filepath.Glob(filepath.Join(dir, glob))

    if len(optional) > 0 {
        dir = optional[0]
    } else {
        dir = ""
    }

    for _, file := range files {
        finp, err := os.Open(file)
        if err != nil {
            return err
        }

        dst := filepath.Join(dir, filepath.Base(file))
        fout, err := os.OpenFile(dst,
                                 os.O_WRONLY|os.O_APPEND|os.O_CREATE, 0644)
        if err != nil {
            finp.Close()
            return err
        }

        finpStat, _ := finp.Stat()
        foutStat, _ := fout.Stat()
        fout.Close()
        if !os.SameFile(finpStat, foutStat) {
            fout, err = os.OpenFile(dst,
                                    os.O_WRONLY|os.O_TRUNC|os.O_CREATE, 0644)
            if err != nil {
                finp.Close()
                return err
            }
            log.Print("copying ", file)
            written, err := io.Copy(fout, finp)
            fout.Close()
            if err != nil {
                finp.Close()
                return err
            }
            log.Printf("copied %d bytes", written)
        }
        finp.Close()
    }

    return nil
}

type GpuPtrT struct { cgo C.gpu_ptr_t }

func (ptr *GpuPtrT) Clone() GpuPtrT {
    return GpuPtrT{C.go_clone_gpu_ptr_t(&ptr.cgo)}
}

func (ptr *GpuPtrT) Drop() {
    C.go_drop_gpu_ptr_t(&ptr.cgo)
}

func IsCudaAvailable() bool {
    return bool(C.go_cuda_available())
}
