// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#pragma once

#include <memory>
#include <stdexcept>
#include <cstring>
#include <vector>

#include "zkp/digest.h"
#include "zkp/fp.h"
#include "zkp/fpext.h"

namespace risc0 {

class IHal;
using IHalPtr = std::shared_ptr<IHal>;

class DualHal;

// The low level opaque hal buffer
class IBuffer {
public:
  IBuffer() {}
  virtual ~IBuffer() {}
  virtual size_t size() = 0;  // Size in bytes
};

using IBufferPtr = std::shared_ptr<IBuffer>;

template<typename T> class PinnedArrayRO;
template<typename T> class PinnedArrayBase;
template<typename T> class PinnedMatrixRO;
template<typename T> class PinnedMatrixBase;

// A typed one-dimensional hal buffer, smartptr like
template<typename T>
class HalArray {
  friend class IHal;
  friend class DualHal;
  friend class PinnedArrayRO<T>;
  friend class PinnedArrayBase<T>;
public:
  HalArray() = default;
  HalArray(IBufferPtr inner) : inner(inner), _offset(0), _size(inner->size()) {}
  HalArray(const HalArray<T>& rhs) = default;

  void copyFromCpu(IHalPtr hal, const T* data);

  // Size in elements
  size_t size() const { return _size / sizeof(T); }

  // Slice user # of elements
  HalArray<T> slice(size_t offset, size_t size) {
    if ((offset + size) * sizeof(T) > _size) {
      throw std::runtime_error("Invalid slice");
    }
    HalArray<T> ret = *this;
    ret._offset = _offset + offset * sizeof(T);
    ret._size = size * sizeof(T);
    return ret;
  }

private:
  IBufferPtr inner;
  // Offset + size are in *bytes* not elements
  size_t _offset;
  size_t _size;
};

// A typed two-dimensional hal buffer, smartptr like
template<typename T>
class HalMatrix {
  friend class IHal;
  friend class DualHal;
  friend class PinnedMatrixRO<T>;
  friend class PinnedMatrixBase<T>;
public:
  HalMatrix() = default;
  HalMatrix(IBufferPtr inner, size_t rows, size_t cols) : inner(inner), _rows(rows), _cols(cols) {}
  HalMatrix(const HalMatrix<T>& rhs) = default;

  // Size in elements
  size_t rows() const { return _rows; }
  size_t cols() const { return _cols; }
  size_t size() { return inner->size() / sizeof(T); }
  HalMatrix reshape(size_t rows, size_t cols) {
    if (rows * cols != _rows * _cols) {
      throw std::runtime_error("Invalid reshape");
    }
    return HalMatrix(inner, rows, cols);
  }

private:
  IBufferPtr inner;
  size_t _rows;
  size_t _cols;
};

struct RowInfo {
  RowInfo() = default;
  RowInfo(uint8_t rowType, uint8_t blockCount, uint32_t auxOffset)
    : rowType(rowType), blockCount(blockCount), auxOffset(auxOffset) {}
  uint8_t rowType;
  uint8_t blockCount;
  uint16_t padding = 0;
  uint32_t auxOffset;
};

struct EvalInfo {
  uint32_t group;
  uint32_t column;
  uint32_t comboId;
  uint32_t coeffIndex;
};

struct DivideInfo {
  uint32_t comboId;
  FpExt z;
};

// Hal abstraction
class IHal : public std::enable_shared_from_this<IHal> {
  template<typename T> friend class PinnedArrayRO;
  template<typename T> friend class PinnedArrayBase;
  template<typename T> friend class PinnedMatrixRO;
  template<typename T> friend class PinnedMatrixBase;
  friend class DualHal;
public:
  virtual ~IHal() {}

  // Allocations
  template<typename T>
  HalArray<T> allocateArray(size_t size) {
    IBufferPtr inner = allocate(size * sizeof(T));
    return HalArray<T>(inner);
  }

  template<typename T>
  HalArray<T> allocateArrayCopy(const std::vector<T>& in);

  template<typename T>
  HalMatrix<T> allocateMatrix(size_t rows, size_t cols) {
    IBufferPtr inner = allocate(rows * cols * sizeof(T));
    return HalMatrix<T>(inner, rows, cols);
  }

  // Copies
  template<typename T>
  void copy(HalArray<T> out, HalMatrix<T> in) {
    if (out.size() != in.size()) {
      throw std::runtime_error("Invalid copy");
    }
    copy(out.inner, out._offset, in.inner, in._offset, in._size);
  }
  template<typename T>
  void copy(HalMatrix<T> out, HalMatrix<T> in) {
    if (out.rows() != in.rows() || out.cols() != in.cols()) {
      throw std::runtime_error("Invalid copy");
    }
    copy(out.inner, 0, in.inner, 0, out.rows() * out.cols() * sizeof(T));
  }

  template<typename T>
  void zero(HalArray<T> out) {
    zero(out.inner, out._offset, out._size);
  }
  template<typename T>
  void zero(HalMatrix<T> out) {
    zero(out.inner, 0, out.rows() * out.cols() * sizeof(T));
  }

  // Hashing related functions
  virtual void hashRows(HalArray<Digest> out, HalMatrix<Fp> in) = 0;
  virtual void hashFold(HalArray<Digest> out, HalArray<Digest> in) = 0;
  virtual void query(HalArray<Fp> out, HalMatrix<Fp> data, HalArray<Digest> tree, size_t topSize, size_t idx) = 0;

  // NTT functions
  virtual void batchBitReverse(HalMatrix<Fp> io) = 0;
  virtual void batchExpandAndEvaluate(HalMatrix<Fp> out, HalMatrix<Fp> in) = 0;
  virtual void batchInterpolate(HalMatrix<Fp> io) = 0;
  virtual void batchShift(HalMatrix<Fp> io) = 0;
  virtual void batchPolyEval(HalArray<FpExt> out, HalMatrix<Fp> coeffs, HalArray<uint32_t> cols, HalArray<FpExt> xs) = 0;

  // Mixing related functions
  virtual void combosMix(HalMatrix<FpExt> combos, HalMatrix<Fp> coeffs, HalArray<uint32_t> whichCombo, FpExt cur, FpExt mix) = 0;
  virtual void combosPrep(HalMatrix<FpExt> combos, HalArray<FpExt> eval, HalArray<EvalInfo> info, FpExt mix) = 0;
  virtual void combosDivide(HalMatrix<FpExt> combos, HalArray<DivideInfo> info) = 0;
  virtual void combosFinalize(HalMatrix<Fp> out, HalMatrix<FpExt> combos) = 0;

  // FRI functins
  virtual void friFold(HalMatrix<Fp> out, HalMatrix<Fp> in, FpExt mix) = 0;

  // Compute the data witness from the preflight data
  virtual void computeDataWitness(HalMatrix<Fp> data, HalArray<Fp> globals, HalArray<RowInfo> rows, HalArray<uint32_t> aux, HalArray<uint32_t> tables) = 0;
  // Compute the accum witness from the data
  virtual void computeAccumWitness(HalMatrix<Fp> accum, HalMatrix<Fp> data, HalArray<Fp> globals, HalArray<FpExt> accMix) = 0;
  // Compute the evaluation of the constraint polynomial
  virtual void evalCheck(HalMatrix<Fp> check, HalMatrix<Fp> data, HalMatrix<Fp> accum, HalArray<Fp> globals, HalArray<FpExt> accMix, FpExt ecMix) = 0;

  // Finish any outstanding compute (for benchmarking)
  virtual void sync() = 0;

protected:
  // Allocate a new buffer based on size in bytes, uninitialized
  virtual IBufferPtr allocate(size_t size) = 0;
  // Copy from one buffer to another
  virtual void copy(IBufferPtr dst, size_t dstOffset, IBufferPtr src, size_t srcOffset, size_t count) = 0;
  // Zero a buffer
  virtual void zero(IBufferPtr buf, size_t offset, size_t size) = 0;
  // Pin a buffer, optionally sync, return pointer
  virtual void* pin(IBufferPtr buf, size_t offset, size_t size, bool sync) = 0;
  // Unpin a buffer
  virtual void unpin(IBufferPtr buf, void* pinned, size_t offset, size_t size, bool modified) = 0;

  // Helpers for subclasses to bypass privacy restrictions
  template<typename T>
  IBufferPtr extract(HalArray<T> array) { return array.inner; }
  template<typename T>
  size_t getOffset(HalArray<T> array) { return array._offset; }
  template<typename T>
  IBufferPtr extract(HalMatrix<T> matrix) { return matrix.inner; }
};

template<typename T>
class PinnedArrayRO {
public:
  PinnedArrayRO(IHalPtr hal, HalArray<T> buf)
    : hal(hal)
    , buf(buf.inner)
    , pbuf(reinterpret_cast<T*>(hal->pin(buf.inner, buf._offset, buf._size, true)))
    , _offset(buf._offset)
    , _size(buf._size)
  {}
  ~PinnedArrayRO() {
    hal->unpin(buf, pbuf, _offset, _size, false);
  }
  const T& operator[](size_t i) const { return pbuf[i]; }
  const T* data() const { return pbuf; }
  size_t size() const { return _size / sizeof(T); }

private:
  IHalPtr hal;
  IBufferPtr buf;
  T* pbuf;
  size_t _offset;
  size_t _size;
};

template<typename T>
class PinnedArrayBase {
public:
  PinnedArrayBase(IHalPtr hal, HalArray<T> buf, bool sync)
    : hal(hal)
    , buf(buf.inner)
    , pbuf(reinterpret_cast<T*>(hal->pin(buf.inner, buf._offset, buf._size, sync)))
    , _offset(buf._offset)
    , _size(buf._size)
  {}
  ~PinnedArrayBase() {
    hal->unpin(buf, pbuf, _offset, _size, true);
  }
  T& operator[](size_t i) { return pbuf[i]; }
  T* data() { return pbuf; }
  size_t size() const { return _size / sizeof(T); }

private:
  IHalPtr hal;
  IBufferPtr buf;
  T* pbuf;
  size_t _offset;
  size_t _size;
};

template<typename T>
class PinnedArrayWO : public PinnedArrayBase<T> {
public:
  PinnedArrayWO(IHalPtr hal, HalArray<T> buf) : PinnedArrayBase<T>(hal, buf, false) {}
};

template<typename T>
class PinnedArrayRW : public PinnedArrayBase<T> {
public:
  PinnedArrayRW(IHalPtr hal, HalArray<T> buf) : PinnedArrayBase<T>(hal, buf, true) {}
};

template<typename T>
void HalArray<T>::copyFromCpu(IHalPtr hal, const T* data) {
  PinnedArrayWO<T> pinned(hal, *this);
  memcpy(pinned.data(), data, _size);
}

template<typename T>
class PinnedMatrixRO {
public:
  PinnedMatrixRO(IHalPtr hal, HalMatrix<T> mat)
    : hal(hal), buf(mat.inner), pbuf(reinterpret_cast<T*>(hal->pin(buf, 0, buf->size(), true))), _rows(mat.rows()), _cols(mat.cols()) {}
  ~PinnedMatrixRO() {
    hal->unpin(buf, pbuf, 0, buf->size(), false);
  }
  const T& operator[](size_t i) const { return pbuf[i]; }
  const T& operator()(size_t i, size_t j) const { return pbuf[_rows * j + i]; }
  const T* data() const { return pbuf; }
  size_t size() const { return buf->size() / sizeof(T); }
  size_t rows() const { return _rows; }
  size_t cols() const { return _cols; }

private:
  IHalPtr hal;
  IBufferPtr buf;
  T* pbuf;
  size_t _rows;
  size_t _cols;
};

template<typename T>
class PinnedMatrixBase {
public:
  PinnedMatrixBase(IHalPtr hal, HalMatrix<T> mat, bool sync)
    : hal(hal), buf(mat.inner), pbuf(reinterpret_cast<T*>(hal->pin(buf, 0, buf->size(), sync))), _rows(mat.rows()), _cols(mat.cols()) {}
  ~PinnedMatrixBase() {
    hal->unpin(buf, pbuf, 0, buf->size(), true);
  }
  T& operator()(size_t i, size_t j) { return pbuf[_rows * j + i]; }
  T& operator[](size_t i) { return pbuf[i]; }
  T* data() { return pbuf; }
  size_t size() const { return buf->size() / sizeof(T); }
  size_t rows() const { return _rows; }
  size_t cols() const { return _cols; }

private:
  IHalPtr hal;
  IBufferPtr buf;
  T* pbuf;
  size_t _rows;
  size_t _cols;
};

template<typename T>
class PinnedMatrixWO : public PinnedMatrixBase<T> {
public:
  PinnedMatrixWO(IHalPtr hal, HalMatrix<T> buf) : PinnedMatrixBase<T>(hal, buf, false) {}
};

template<typename T>
class PinnedMatrixRW : public PinnedMatrixBase<T> {
public:
  PinnedMatrixRW(IHalPtr hal, HalMatrix<T> buf) : PinnedMatrixBase<T>(hal, buf, true) {}
};

template<typename T>
HalArray<T> IHal::allocateArrayCopy(const std::vector<T>& in) {
  auto halArray = allocateArray<T>(in.size());
  PinnedArrayWO<T> pin(shared_from_this(), halArray);
  memcpy(pin.data(), in.data(), sizeof(T) * in.size());
  return halArray;
}

// TODO: Where should I actually put these
IHalPtr getCpuHal();
IHalPtr getGpuHal();

} // namespace risc0
