#pragma once

#include "risc0/core/util.h"
#include "risc0/zkp/accel/pp.h"
#include "risc0/zkp/core/fp4.h"
#include "risc0/zkp/core/sha256.h"

#include <memory>
#include <vector>

namespace risc0 {

// The actual buffer details are per accelerator and thus 'pImpl'ed.
struct AccelBufImpl;

// Simple minimal c-like API to the backend accelerator.
void accelStartup();
AccelBufImpl* accelAllocBuf(size_t size);
void accelFreeBuf(AccelBufImpl* impl);
void* accelGetContents(AccelBufImpl* impl, size_t offset, size_t size, bool sync);
void accelIsDirty(AccelBufImpl* impl, size_t offset, size_t size);
void accelBeginProfile();
void accelEndProfile();

// Wrapper object for RAII buffer management
struct AccelBuf {
  AccelBufImpl* buf;
  size_t size;
  AccelBuf(size_t size) : buf(accelAllocBuf(size)), size(size) {}
  ~AccelBuf() { accelFreeBuf(buf); }
  AccelBuf(const AccelBuf&) = delete;
  AccelBuf& operator=(const AccelBuf&) = delete;
};

// A slice basically represents a memory range inside an accel buffer and also
// holds down the buffer via a shared_ptr.  Generally, buffers are not used directly
// by the user, but instead the static allocation method in this class is used to construct new
// buffers
template <typename T> struct AccelConstSlice;

template <typename T> struct AccelSlice {
  friend struct AccelConstSlice<T>;

public:
  AccelSlice() : offset_(0), size_(0) {} // A 'null' slice that points to nothing
  static AccelSlice allocate(size_t size) {
    AccelSlice ret;
    ret.buf_ = std::make_shared<AccelBuf>(size * sizeof(T));
    ret.size_ = size;
    return ret;
  }
  static AccelSlice copy(const T* rhs, size_t size) {
    AccelSlice ret = allocate(size);
    size_t sizeBytes = size * sizeof(T);
    T* data = reinterpret_cast<T*>(accelGetContents(ret.buf_->buf, 0, sizeBytes, false));
    memcpy(data, rhs, sizeBytes);
    accelIsDirty(ret.buf_->buf, 0, sizeBytes);
    return ret;
  }
  static AccelSlice copy(const std::vector<T>& rhs) { return copy(rhs.data(), rhs.size()); }
  operator bool() const { return static_cast<bool>(buf_); }
  AccelSlice slice(size_t offset, size_t size) const {
    REQUIRE(offset + size <= size_);
    AccelSlice ret = *this;
    ret.offset_ += offset;
    ret.size_ = size;
    return ret;
  }
  size_t size() const { return size_; }
  size_t offset() const { return offset_; }
  AccelBufImpl* buf() const { return buf_->buf; }

private:
  std::shared_ptr<AccelBuf> buf_;
  size_t offset_;
  size_t size_;
};

template <typename T> struct AccelConstSlice {
public:
  AccelConstSlice(AccelSlice<T> rhs) : buf_(rhs.buf_), offset_(rhs.offset_), size_(rhs.size_) {}
  AccelConstSlice() : offset_(0), size_(0) {} // A 'null' slice that points to nothing
  operator bool() const { return static_cast<bool>(buf_); }
  AccelConstSlice slice(size_t offset, size_t size) const {
    REQUIRE(offset + size <= size_);
    AccelConstSlice ret = *this;
    ret.offset_ += offset;
    ret.size_ = size;
    return ret;
  }
  size_t size() const { return size_; }
  size_t offset() const { return offset_; }
  AccelBufImpl* buf() const { return buf_->buf; }

private:
  std::shared_ptr<AccelBuf> buf_;
  size_t offset_;
  size_t size_;
};

// An RAII classes for logically mapping an accel buffers to CPU memory

template <typename T> class AccelReadLock {
public:
  AccelReadLock(AccelConstSlice<T> slice) {
    data_ = reinterpret_cast<T*>(
        accelGetContents(slice.buf(), slice.offset() * sizeof(T), slice.size() * sizeof(T), true));
    size_ = slice.size();
  }
  AccelReadLock(AccelSlice<T> slice) : AccelReadLock(AccelConstSlice<T>(slice)) {}
  ~AccelReadLock() {
    // Do nothing
  }
  AccelReadLock(const AccelReadLock&) = delete;
  AccelReadLock& operator=(const AccelReadLock&) = delete;

  const T& operator[](size_t i) const { return data_[i]; }
  const T* data() const { return data_; }
  size_t size() const { return size_; }

private:
  const T* data_;
  size_t size_;
};

template <typename T> class AccelWriteLockBase {
public:
  // sync = true means read/write, sync = false means write only (i.e. any reads may be out of date)
  AccelWriteLockBase(AccelSlice<T> slice, bool sync)
      : impl_(slice.buf()), offset_(slice.offset()), size_(slice.size()) {
    data_ =
        reinterpret_cast<T*>(accelGetContents(impl_, offset_ * sizeof(T), size_ * sizeof(T), sync));
  }
  ~AccelWriteLockBase() { accelIsDirty(impl_, offset_ * sizeof(T), size_ * sizeof(T)); }
  AccelWriteLockBase(const AccelWriteLockBase&) = delete;
  AccelWriteLockBase& operator=(const AccelWriteLockBase&) = delete;

  T& operator[](size_t i) const { return data_[i]; }
  T* data() const { return data_; }
  size_t size() const { return size_; }

private:
  AccelBufImpl* impl_;
  size_t offset_;
  size_t size_;
  T* data_;
};

template <typename T> class AccelWriteOnlyLock : public AccelWriteLockBase<T> {
public:
  AccelWriteOnlyLock(AccelSlice<T> slice) : AccelWriteLockBase<T>(slice, false) {}
};

template <typename T> class AccelReadWriteLock : public AccelWriteLockBase<T> {
public:
  AccelReadWriteLock(AccelSlice<T> slice) : AccelWriteLockBase<T>(slice, true) {}
};

// Special cases (with seperate CPU + GPU implementations)

void batchEvaluateNTT(AccelSlice<Fp> io, size_t count, size_t expandBits = 0);
void batchInterpolateNTT(AccelSlice<Fp> io, size_t count);
void batchExpand(AccelSlice<Fp> out, AccelConstSlice<Fp> in, size_t count);
void batchBitReverse(AccelSlice<Fp> io, size_t count);

// Evaluate a various polynomials (in Fp) at various points (in Fp4)
void batchEvaluateAny(
    AccelConstSlice<Fp> coeffs, // The polynomials (polyCount * polySize)
    size_t polyCount,
    AccelConstSlice<uint32_t> which, // Poly to pick for each evaluation (evalCount entries)
    AccelConstSlice<Fp4> xs,         // Position to eval at (evalCount entries)
    AccelSlice<Fp4> out              // Where to put the outputs (evalCount entries)
);

// Generated declarations

#define DECL_PTR(type, name) AccelSlice<type> name,
#define DECL_CPTR(type, name) AccelConstSlice<type> name,
#define DECL_SIZE(name) size_t name,
#define DECL_CALC(name, expr) /**/
#define DECL_REQ(expr)        /**/
#define DECL_MAP(arg) PP_PASTE(DECL, PP_PASTE(_, arg))

#define PARALLEL_KERNEL(name, args, impl)                                                          \
  extern void name##Accel(PP_APPLY_LST(DECL_MAP, args) bool ignore = true);

#include "risc0/zkp/accel/kernels/all.h"

#undef DECL_PTR
#undef DECL_CPTR
#undef DECL_SIZE
#undef DECL_CALC
#undef DECL_REQ
#undef DECL_MAP
#undef PARALLEL_KERNEL

} // namespace risc0
