// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

template <typename C> FDEV void IsZero<C>::set(CTX, Fp val) DEV {
  if (Val<C>(val) == Val<C>(0)) {
    isZero.set(ctx, 1);
    invReg.set(ctx, 0);
  } else {
    isZero.set(ctx, 0);
    invReg.set(ctx, inv(val));
  }
}

template <typename C> FDEV void IsZero<C>::verify(CTX, Val<C> val) DEV {
  // If isZero is 0 (i.e. nonzero) then val must have an inverse
  EQ(val * invReg.get(), Val<C>(1) - isZero.get());
  // If isZero is 1, then val must be zero
  EQZ(isZero.get() * val);
  // If isZero is 1, then inv must be zero
  EQZ(isZero.get() * invReg.get());
}
