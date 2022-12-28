// Copyright (c) 2022 RISC Zero, Inc.
//
// All rights reserved.

// This code is automatically generated

#include "ffi.h"
#include "fp.h"

#include <array>
#include <cassert>
#include <stdexcept>

// clang-format off
namespace risc0::circuit::rv32im {

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-variable"
#endif

Fp step_verify_bytes(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  std::array<Fp, 32> host_args;
  std::array<Fp, 32> host_outs;
  // loc("cirgen/components/bytes.cpp":82:0)
  Fp x0(255);
  // loc("cirgen/components/bytes.cpp":37:0)
  Fp x1(2);
  // loc("cirgen/components/bytes.cpp":34:0)
  Fp x2(254);
  // loc("cirgen/components/bytes.cpp":21:0)
  Fp x3(0);
  // loc("cirgen/circuit/rv32im/top.cpp":18:0)
  Fp x4(1);
  // loc("Top/Code/OneHot/Reg1"("./cirgen/components/mux.h":37:0))
  auto x5 = args[0][2 * steps + ((cycle - 0) & mask)];
  assert(x5 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg2"("./cirgen/components/mux.h":37:0))
  auto x6 = args[0][3 * steps + ((cycle - 0) & mask)];
  assert(x6 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg3"("./cirgen/components/mux.h":37:0))
  auto x7 = args[0][4 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg4"("./cirgen/components/mux.h":37:0))
  auto x8 = args[0][5 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg5"("./cirgen/components/mux.h":37:0))
  auto x9 = args[0][6 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg6"("./cirgen/components/mux.h":37:0))
  auto x10 = args[0][7 * steps + ((cycle - 0) & mask)];
  assert(x10 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg"("cirgen/circuit/rv32im/top.cpp":69:0))
  auto x11 = args[0][1 * steps + ((cycle - 0) & mask)];
  assert(x11 != Fp::invalid());
  if (x11 != 0) {
    // loc("cirgen/components/bytes.cpp":21:0)
    {
      auto& reg = args[2][0 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x3);
      reg = x3;
    }
    // loc("cirgen/components/bytes.cpp":22:0)
    {
      auto& reg = args[2][1 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x3);
      reg = x3;
    }
  }
  if (x5 != 0) {
    {
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x12 = host_outs.at(0);
      auto x13 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x12);
        reg = x12;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x13);
        reg = x13;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x14 = host_outs.at(0);
      auto x15 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x14);
        reg = x14;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x15);
        reg = x15;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x16 = host_outs.at(0);
      auto x17 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x16);
        reg = x16;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x17);
        reg = x17;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x18 = host_outs.at(0);
      auto x19 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x18);
        reg = x18;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x19);
        reg = x19;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x20 = host_outs.at(0);
      auto x21 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x20);
        reg = x20;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x21);
        reg = x21;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x22 = host_outs.at(0);
      auto x23 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x22);
        reg = x22;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x23);
        reg = x23;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x24 = host_outs.at(0);
      auto x25 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x24);
        reg = x24;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x25);
        reg = x25;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x26 = host_outs.at(0);
      auto x27 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x26);
        reg = x26;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x27);
        reg = x27;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x28 = host_outs.at(0);
      auto x29 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x28);
        reg = x28;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x29);
        reg = x29;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x30 = host_outs.at(0);
      auto x31 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x30);
        reg = x30;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x31);
        reg = x31;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x32 = host_outs.at(0);
      auto x33 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][72 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x32);
        reg = x32;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][73 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x33);
        reg = x33;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x34 = host_outs.at(0);
      auto x35 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][74 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x34);
        reg = x34;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][75 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x35);
        reg = x35;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x36 = host_outs.at(0);
      auto x37 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x36);
        reg = x36;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x37);
        reg = x37;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x38 = host_outs.at(0);
      auto x39 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x38);
        reg = x38;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x39);
        reg = x39;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x40 = host_outs.at(0);
      auto x41 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x40);
        reg = x40;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x41);
        reg = x41;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x42 = host_outs.at(0);
      auto x43 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x42);
        reg = x42;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x43);
        reg = x43;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x44 = host_outs.at(0);
      auto x45 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x44);
        reg = x44;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x45);
        reg = x45;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x46 = host_outs.at(0);
      auto x47 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x46);
        reg = x46;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x47);
        reg = x47;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x48 = host_outs.at(0);
      auto x49 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x48);
        reg = x48;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x49);
        reg = x49;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x50 = host_outs.at(0);
      auto x51 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][90 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x50);
        reg = x50;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][91 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x51);
        reg = x51;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x52 = host_outs.at(0);
      auto x53 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x52);
        reg = x52;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x53);
        reg = x53;
      }
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":52:0))
    auto x54 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x54 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":53:0))
    auto x55 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x55 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement21/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x56 = args[2][52 * steps + ((cycle - 0) & mask)];
    assert(x56 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement21/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x57 = args[2][53 * steps + ((cycle - 0) & mask)];
    assert(x57 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x58 = x56 - x54;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x59 = x57 - x55;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x60 = x58 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x61 = x58 * x60;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x61 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x58 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x57 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x62 = x55 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x63 = x55 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x64 = x63 * x62;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x64 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x65 = x4 - x58;
    if (x65 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x66 = x59 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x67 = x59 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x68 = x59 * x67;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x69 = x68 * x66;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x69 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement22/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x70 = args[2][54 * steps + ((cycle - 0) & mask)];
    assert(x70 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement22/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x71 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x71 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x72 = x70 - x56;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x73 = x71 - x57;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x74 = x72 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x75 = x72 * x74;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x75 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x72 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x71 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x76 = x57 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x77 = x57 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x78 = x77 * x76;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x78 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x79 = x4 - x72;
    if (x79 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x80 = x73 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x81 = x73 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x82 = x73 * x81;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x83 = x82 * x80;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x83 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement23/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x84 = args[2][56 * steps + ((cycle - 0) & mask)];
    assert(x84 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement23/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x85 = args[2][57 * steps + ((cycle - 0) & mask)];
    assert(x85 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x86 = x84 - x70;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x87 = x85 - x71;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x88 = x86 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x89 = x86 * x88;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x89 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x86 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x85 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x90 = x71 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x91 = x71 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x92 = x91 * x90;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x92 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x93 = x4 - x86;
    if (x93 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x94 = x87 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x95 = x87 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x96 = x87 * x95;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x97 = x96 * x94;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x97 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement24/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x98 = args[2][58 * steps + ((cycle - 0) & mask)];
    assert(x98 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement24/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x99 = args[2][59 * steps + ((cycle - 0) & mask)];
    assert(x99 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x100 = x98 - x84;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x101 = x99 - x85;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x102 = x100 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x103 = x100 * x102;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x103 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x100 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x99 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x104 = x85 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x105 = x85 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x106 = x105 * x104;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x106 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x107 = x4 - x100;
    if (x107 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x108 = x101 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x109 = x101 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x110 = x101 * x109;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x111 = x110 * x108;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x111 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement25/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x112 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x112 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement25/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x113 = args[2][61 * steps + ((cycle - 0) & mask)];
    assert(x113 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x114 = x112 - x98;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x115 = x113 - x99;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x116 = x114 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x117 = x114 * x116;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x117 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x114 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x113 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x118 = x99 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x119 = x99 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x120 = x119 * x118;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x120 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x121 = x4 - x114;
    if (x121 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x122 = x115 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x123 = x115 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x124 = x115 * x123;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x125 = x124 * x122;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x125 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement26/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x126 = args[2][62 * steps + ((cycle - 0) & mask)];
    assert(x126 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement26/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x127 = args[2][63 * steps + ((cycle - 0) & mask)];
    assert(x127 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x128 = x126 - x112;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x129 = x127 - x113;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x130 = x128 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x131 = x128 * x130;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x131 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x128 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x127 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x132 = x113 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x133 = x113 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x134 = x133 * x132;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x134 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x135 = x4 - x128;
    if (x135 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x136 = x129 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x137 = x129 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x138 = x129 * x137;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x139 = x138 * x136;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x139 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement27/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x140 = args[2][64 * steps + ((cycle - 0) & mask)];
    assert(x140 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement27/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x141 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x141 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x142 = x140 - x126;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x143 = x141 - x127;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x144 = x142 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x145 = x142 * x144;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x145 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x142 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x141 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x146 = x127 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x147 = x127 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x148 = x147 * x146;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x148 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x149 = x4 - x142;
    if (x149 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x150 = x143 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x151 = x143 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x152 = x143 * x151;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x153 = x152 * x150;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x153 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement28/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x154 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x154 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement28/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x155 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x155 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x156 = x154 - x140;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x157 = x155 - x141;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x158 = x156 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x159 = x156 * x158;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x159 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x156 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x155 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x160 = x141 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x161 = x141 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x162 = x161 * x160;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x162 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x163 = x4 - x156;
    if (x163 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x164 = x157 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x165 = x157 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x166 = x157 * x165;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x167 = x166 * x164;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x167 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement29/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x168 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x168 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement29/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x169 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x169 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x170 = x168 - x154;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x171 = x169 - x155;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x172 = x170 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x173 = x170 * x172;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x173 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x170 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x169 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x174 = x155 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x175 = x155 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x176 = x175 * x174;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x176 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x177 = x4 - x170;
    if (x177 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x178 = x171 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x179 = x171 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x180 = x171 * x179;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x181 = x180 * x178;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x181 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement30/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x182 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x182 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement30/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x183 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x183 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x184 = x182 - x168;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x185 = x183 - x169;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x186 = x184 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x187 = x184 * x186;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x187 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x184 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x183 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x188 = x169 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x189 = x169 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x190 = x189 * x188;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x190 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x191 = x4 - x184;
    if (x191 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x192 = x185 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x193 = x185 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x194 = x185 * x193;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x195 = x194 * x192;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x195 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement31/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x196 = args[2][72 * steps + ((cycle - 0) & mask)];
    assert(x196 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement31/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x197 = args[2][73 * steps + ((cycle - 0) & mask)];
    assert(x197 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x198 = x196 - x182;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x199 = x197 - x183;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x200 = x198 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x201 = x198 * x200;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x201 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x198 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x197 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x202 = x183 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x203 = x183 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x204 = x203 * x202;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x204 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x205 = x4 - x198;
    if (x205 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x206 = x199 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x207 = x199 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x208 = x199 * x207;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x209 = x208 * x206;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x209 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement32/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x210 = args[2][74 * steps + ((cycle - 0) & mask)];
    assert(x210 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement32/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x211 = args[2][75 * steps + ((cycle - 0) & mask)];
    assert(x211 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x212 = x210 - x196;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x213 = x211 - x197;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x214 = x212 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x215 = x212 * x214;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x215 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x212 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x211 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x216 = x197 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x217 = x197 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x218 = x217 * x216;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x218 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x219 = x4 - x212;
    if (x219 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x220 = x213 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x221 = x213 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x222 = x213 * x221;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x223 = x222 * x220;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x223 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement33/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x224 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x224 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement33/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x225 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x225 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x226 = x224 - x210;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x227 = x225 - x211;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x228 = x226 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x229 = x226 * x228;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x229 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x226 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x225 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x230 = x211 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x231 = x211 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x232 = x231 * x230;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x232 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x233 = x4 - x226;
    if (x233 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x234 = x227 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x235 = x227 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x236 = x227 * x235;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x237 = x236 * x234;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x237 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement34/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x238 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x238 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement34/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x239 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x239 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x240 = x238 - x224;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x241 = x239 - x225;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x242 = x240 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x243 = x240 * x242;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x243 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x240 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x239 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x244 = x225 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x245 = x225 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x246 = x245 * x244;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x246 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x247 = x4 - x240;
    if (x247 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x248 = x241 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x249 = x241 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x250 = x241 * x249;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x251 = x250 * x248;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x251 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement35/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x252 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x252 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement35/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x253 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x253 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x254 = x252 - x238;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x255 = x253 - x239;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x256 = x254 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x257 = x254 * x256;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x257 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x254 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x253 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x258 = x239 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x259 = x239 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x260 = x259 * x258;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x260 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x261 = x4 - x254;
    if (x261 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x262 = x255 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x263 = x255 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x264 = x255 * x263;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x265 = x264 * x262;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x265 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement36/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x266 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x266 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement36/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x267 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x267 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x268 = x266 - x252;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x269 = x267 - x253;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x270 = x268 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x271 = x268 * x270;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x271 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x268 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x267 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x272 = x253 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x273 = x253 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x274 = x273 * x272;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x274 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x275 = x4 - x268;
    if (x275 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x276 = x269 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x277 = x269 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x278 = x269 * x277;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x279 = x278 * x276;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x279 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement37/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x280 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x280 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement37/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x281 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x281 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x282 = x280 - x266;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x283 = x281 - x267;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x284 = x282 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x285 = x282 * x284;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x285 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x282 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x281 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x286 = x267 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x287 = x267 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x288 = x287 * x286;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x288 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x289 = x4 - x282;
    if (x289 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x290 = x283 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x291 = x283 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x292 = x283 * x291;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x293 = x292 * x290;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x293 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement38/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x294 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x294 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement38/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x295 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x295 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x296 = x294 - x280;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x297 = x295 - x281;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x298 = x296 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x299 = x296 * x298;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x299 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x296 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x295 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x300 = x281 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x301 = x281 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x302 = x301 * x300;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x302 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x303 = x4 - x296;
    if (x303 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x304 = x297 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x305 = x297 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x306 = x297 * x305;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x307 = x306 * x304;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x307 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement39/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x308 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x308 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement39/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x309 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x309 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x310 = x308 - x294;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x311 = x309 - x295;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x312 = x310 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x313 = x310 * x312;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x313 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x310 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x309 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x314 = x295 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x315 = x295 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x316 = x315 * x314;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x316 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x317 = x4 - x310;
    if (x317 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x318 = x311 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x319 = x311 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x320 = x311 * x319;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x321 = x320 * x318;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x321 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement40/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x322 = args[2][90 * steps + ((cycle - 0) & mask)];
    assert(x322 != Fp::invalid());
    // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement40/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x323 = args[2][91 * steps + ((cycle - 0) & mask)];
    assert(x323 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x324 = x322 - x308;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x325 = x323 - x309;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x326 = x324 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x327 = x324 * x326;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x327 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x324 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x323 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x328 = x309 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x329 = x309 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x330 = x329 * x328;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x330 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x331 = x4 - x324;
    if (x331 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x332 = x325 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x333 = x325 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x334 = x325 * x333;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x335 = x334 * x332;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x335 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x336 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x336 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x337 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x337 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x338 = x336 - x322;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x339 = x337 - x323;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x340 = x338 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x341 = x338 * x340;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x341 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x338 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x337 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x342 = x323 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x343 = x323 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x344 = x343 * x342;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x344 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x345 = x4 - x338;
    if (x345 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x346 = x339 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x347 = x339 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x348 = x339 * x347;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x349 = x348 * x346;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x349 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
  }
  if (x6 != 0) {
    {
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x350 = host_outs.at(0);
      auto x351 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][32 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x350);
        reg = x350;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][33 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x351);
        reg = x351;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x352 = host_outs.at(0);
      auto x353 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][34 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x352);
        reg = x352;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][35 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x353);
        reg = x353;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x354 = host_outs.at(0);
      auto x355 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][36 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x354);
        reg = x354;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][37 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x355);
        reg = x355;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x356 = host_outs.at(0);
      auto x357 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][38 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x356);
        reg = x356;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][39 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x357);
        reg = x357;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x358 = host_outs.at(0);
      auto x359 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][40 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x358);
        reg = x358;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][41 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x359);
        reg = x359;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x360 = host_outs.at(0);
      auto x361 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][42 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x360);
        reg = x360;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][43 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x361);
        reg = x361;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x362 = host_outs.at(0);
      auto x363 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][44 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x362);
        reg = x362;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x363);
        reg = x363;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x364 = host_outs.at(0);
      auto x365 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x364);
        reg = x364;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x365);
        reg = x365;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x366 = host_outs.at(0);
      auto x367 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x366);
        reg = x366;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x367);
        reg = x367;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x368 = host_outs.at(0);
      auto x369 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x368);
        reg = x368;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x369);
        reg = x369;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x370 = host_outs.at(0);
      auto x371 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x370);
        reg = x370;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x371);
        reg = x371;
      }
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":52:0))
    auto x372 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x372 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":53:0))
    auto x373 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x373 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement11/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x374 = args[2][32 * steps + ((cycle - 0) & mask)];
    assert(x374 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement11/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x375 = args[2][33 * steps + ((cycle - 0) & mask)];
    assert(x375 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x376 = x374 - x372;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x377 = x375 - x373;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x378 = x376 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x379 = x376 * x378;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x379 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x376 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x375 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x380 = x373 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x381 = x373 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x382 = x381 * x380;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x382 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x383 = x4 - x376;
    if (x383 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x384 = x377 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x385 = x377 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x386 = x377 * x385;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x387 = x386 * x384;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x387 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement12/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x388 = args[2][34 * steps + ((cycle - 0) & mask)];
    assert(x388 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement12/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x389 = args[2][35 * steps + ((cycle - 0) & mask)];
    assert(x389 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x390 = x388 - x374;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x391 = x389 - x375;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x392 = x390 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x393 = x390 * x392;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x393 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x390 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x389 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x394 = x375 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x395 = x375 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x396 = x395 * x394;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x396 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x397 = x4 - x390;
    if (x397 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x398 = x391 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x399 = x391 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x400 = x391 * x399;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x401 = x400 * x398;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x401 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement13/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x402 = args[2][36 * steps + ((cycle - 0) & mask)];
    assert(x402 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement13/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x403 = args[2][37 * steps + ((cycle - 0) & mask)];
    assert(x403 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x404 = x402 - x388;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x405 = x403 - x389;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x406 = x404 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x407 = x404 * x406;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x407 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x404 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x403 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x408 = x389 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x409 = x389 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x410 = x409 * x408;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x410 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x411 = x4 - x404;
    if (x411 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x412 = x405 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x413 = x405 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x414 = x405 * x413;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x415 = x414 * x412;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x415 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement14/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x416 = args[2][38 * steps + ((cycle - 0) & mask)];
    assert(x416 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement14/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x417 = args[2][39 * steps + ((cycle - 0) & mask)];
    assert(x417 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x418 = x416 - x402;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x419 = x417 - x403;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x420 = x418 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x421 = x418 * x420;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x421 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x418 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x417 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x422 = x403 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x423 = x403 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x424 = x423 * x422;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x424 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x425 = x4 - x418;
    if (x425 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x426 = x419 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x427 = x419 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x428 = x419 * x427;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x429 = x428 * x426;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x429 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement15/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x430 = args[2][40 * steps + ((cycle - 0) & mask)];
    assert(x430 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement15/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x431 = args[2][41 * steps + ((cycle - 0) & mask)];
    assert(x431 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x432 = x430 - x416;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x433 = x431 - x417;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x434 = x432 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x435 = x432 * x434;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x435 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x432 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x431 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x436 = x417 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x437 = x417 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x438 = x437 * x436;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x438 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x439 = x4 - x432;
    if (x439 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x440 = x433 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x441 = x433 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x442 = x433 * x441;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x443 = x442 * x440;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x443 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement16/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x444 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x444 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement16/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x445 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x445 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x446 = x444 - x430;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x447 = x445 - x431;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x448 = x446 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x449 = x446 * x448;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x449 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x446 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x445 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x450 = x431 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x451 = x431 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x452 = x451 * x450;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x452 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x453 = x4 - x446;
    if (x453 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x454 = x447 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x455 = x447 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x456 = x447 * x455;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x457 = x456 * x454;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x457 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement17/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x458 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x458 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement17/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x459 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x459 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x460 = x458 - x444;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x461 = x459 - x445;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x462 = x460 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x463 = x460 * x462;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x463 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x460 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x459 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x464 = x445 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x465 = x445 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x466 = x465 * x464;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x466 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x467 = x4 - x460;
    if (x467 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x468 = x461 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x469 = x461 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x470 = x461 * x469;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x471 = x470 * x468;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x471 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement18/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x472 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x472 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement18/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x473 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x473 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x474 = x472 - x458;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x475 = x473 - x459;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x476 = x474 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x477 = x474 * x476;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x477 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x474 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x473 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x478 = x459 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x479 = x459 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x480 = x479 * x478;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x480 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x481 = x4 - x474;
    if (x481 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x482 = x475 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x483 = x475 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x484 = x475 * x483;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x485 = x484 * x482;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x485 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement19/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x486 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x486 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement19/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x487 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x487 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x488 = x486 - x472;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x489 = x487 - x473;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x490 = x488 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x491 = x488 * x490;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x491 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x488 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x487 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x492 = x473 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x493 = x473 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x494 = x493 * x492;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x494 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x495 = x4 - x488;
    if (x495 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x496 = x489 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x497 = x489 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x498 = x489 * x497;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x499 = x498 * x496;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x499 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement20/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x500 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x500 != Fp::invalid());
    // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement20/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x501 = args[2][51 * steps + ((cycle - 0) & mask)];
    assert(x501 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x502 = x500 - x486;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x503 = x501 - x487;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x504 = x502 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x505 = x502 * x504;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x505 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x502 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x501 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x506 = x487 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x507 = x487 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x508 = x507 * x506;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x508 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x509 = x4 - x502;
    if (x509 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x510 = x503 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x511 = x503 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x512 = x503 * x511;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x513 = x512 * x510;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x513 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x514 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x514 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x515 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x515 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x516 = x514 - x500;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x517 = x515 - x501;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x518 = x516 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x519 = x516 * x518;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x519 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x516 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x515 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x520 = x501 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x521 = x501 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x522 = x521 * x520;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x522 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x523 = x4 - x516;
    if (x523 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x524 = x517 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x525 = x517 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x526 = x517 * x525;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x527 = x526 * x524;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x527 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
  }
  if (x7 != 0) {
    {
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x528 = host_outs.at(0);
      auto x529 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][42 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x528);
        reg = x528;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][43 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x529);
        reg = x529;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x530 = host_outs.at(0);
      auto x531 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][44 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x530);
        reg = x530;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x531);
        reg = x531;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x532 = host_outs.at(0);
      auto x533 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x532);
        reg = x532;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x533);
        reg = x533;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x534 = host_outs.at(0);
      auto x535 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x534);
        reg = x534;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x535);
        reg = x535;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x536 = host_outs.at(0);
      auto x537 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x536);
        reg = x536;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x537);
        reg = x537;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x538 = host_outs.at(0);
      auto x539 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x538);
        reg = x538;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x539);
        reg = x539;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x540 = host_outs.at(0);
      auto x541 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x540);
        reg = x540;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x541);
        reg = x541;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x542 = host_outs.at(0);
      auto x543 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x542);
        reg = x542;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x543);
        reg = x543;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x544 = host_outs.at(0);
      auto x545 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x544);
        reg = x544;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x545);
        reg = x545;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x546 = host_outs.at(0);
      auto x547 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x546);
        reg = x546;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x547);
        reg = x547;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x548 = host_outs.at(0);
      auto x549 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x548);
        reg = x548;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x549);
        reg = x549;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x550 = host_outs.at(0);
      auto x551 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x550);
        reg = x550;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x551);
        reg = x551;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x552 = host_outs.at(0);
      auto x553 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x552);
        reg = x552;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x553);
        reg = x553;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x554 = host_outs.at(0);
      auto x555 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x554);
        reg = x554;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x555);
        reg = x555;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x556 = host_outs.at(0);
      auto x557 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x556);
        reg = x556;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x557);
        reg = x557;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x558 = host_outs.at(0);
      auto x559 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x558);
        reg = x558;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x559);
        reg = x559;
      }
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":52:0))
    auto x560 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x560 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":53:0))
    auto x561 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x561 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement16/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x562 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x562 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement16/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x563 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x563 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x564 = x562 - x560;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x565 = x563 - x561;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x566 = x564 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x567 = x564 * x566;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x567 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x564 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x563 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x568 = x561 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x569 = x561 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x570 = x569 * x568;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x570 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x571 = x4 - x564;
    if (x571 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x572 = x565 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x573 = x565 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x574 = x565 * x573;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x575 = x574 * x572;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x575 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement17/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x576 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x576 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement17/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x577 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x577 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x578 = x576 - x562;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x579 = x577 - x563;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x580 = x578 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x581 = x578 * x580;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x581 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x578 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x577 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x582 = x563 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x583 = x563 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x584 = x583 * x582;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x584 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x585 = x4 - x578;
    if (x585 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x586 = x579 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x587 = x579 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x588 = x579 * x587;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x589 = x588 * x586;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x589 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement18/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x590 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x590 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement18/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x591 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x591 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x592 = x590 - x576;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x593 = x591 - x577;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x594 = x592 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x595 = x592 * x594;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x595 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x592 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x591 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x596 = x577 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x597 = x577 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x598 = x597 * x596;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x598 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x599 = x4 - x592;
    if (x599 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x600 = x593 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x601 = x593 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x602 = x593 * x601;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x603 = x602 * x600;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x603 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement19/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x604 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x604 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement19/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x605 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x605 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x606 = x604 - x590;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x607 = x605 - x591;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x608 = x606 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x609 = x606 * x608;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x609 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x606 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x605 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x610 = x591 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x611 = x591 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x612 = x611 * x610;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x612 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x613 = x4 - x606;
    if (x613 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x614 = x607 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x615 = x607 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x616 = x607 * x615;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x617 = x616 * x614;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x617 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement20/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x618 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x618 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement20/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x619 = args[2][51 * steps + ((cycle - 0) & mask)];
    assert(x619 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x620 = x618 - x604;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x621 = x619 - x605;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x622 = x620 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x623 = x620 * x622;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x623 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x620 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x619 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x624 = x605 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x625 = x605 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x626 = x625 * x624;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x626 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x627 = x4 - x620;
    if (x627 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x628 = x621 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x629 = x621 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x630 = x621 * x629;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x631 = x630 * x628;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x631 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement21/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x632 = args[2][52 * steps + ((cycle - 0) & mask)];
    assert(x632 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement21/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x633 = args[2][53 * steps + ((cycle - 0) & mask)];
    assert(x633 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x634 = x632 - x618;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x635 = x633 - x619;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x636 = x634 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x637 = x634 * x636;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x637 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x634 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x633 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x638 = x619 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x639 = x619 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x640 = x639 * x638;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x640 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x641 = x4 - x634;
    if (x641 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x642 = x635 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x643 = x635 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x644 = x635 * x643;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x645 = x644 * x642;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x645 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement22/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x646 = args[2][54 * steps + ((cycle - 0) & mask)];
    assert(x646 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement22/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x647 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x647 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x648 = x646 - x632;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x649 = x647 - x633;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x650 = x648 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x651 = x648 * x650;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x651 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x648 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x647 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x652 = x633 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x653 = x633 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x654 = x653 * x652;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x654 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x655 = x4 - x648;
    if (x655 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x656 = x649 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x657 = x649 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x658 = x649 * x657;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x659 = x658 * x656;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x659 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement23/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x660 = args[2][56 * steps + ((cycle - 0) & mask)];
    assert(x660 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement23/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x661 = args[2][57 * steps + ((cycle - 0) & mask)];
    assert(x661 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x662 = x660 - x646;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x663 = x661 - x647;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x664 = x662 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x665 = x662 * x664;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x665 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x662 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x661 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x666 = x647 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x667 = x647 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x668 = x667 * x666;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x668 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x669 = x4 - x662;
    if (x669 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x670 = x663 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x671 = x663 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x672 = x663 * x671;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x673 = x672 * x670;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x673 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement24/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x674 = args[2][58 * steps + ((cycle - 0) & mask)];
    assert(x674 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement24/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x675 = args[2][59 * steps + ((cycle - 0) & mask)];
    assert(x675 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x676 = x674 - x660;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x677 = x675 - x661;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x678 = x676 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x679 = x676 * x678;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x679 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x676 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x675 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x680 = x661 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x681 = x661 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x682 = x681 * x680;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x682 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x683 = x4 - x676;
    if (x683 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x684 = x677 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x685 = x677 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x686 = x677 * x685;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x687 = x686 * x684;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x687 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement25/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x688 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x688 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement25/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x689 = args[2][61 * steps + ((cycle - 0) & mask)];
    assert(x689 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x690 = x688 - x674;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x691 = x689 - x675;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x692 = x690 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x693 = x690 * x692;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x693 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x690 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x689 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x694 = x675 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x695 = x675 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x696 = x695 * x694;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x696 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x697 = x4 - x690;
    if (x697 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x698 = x691 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x699 = x691 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x700 = x691 * x699;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x701 = x700 * x698;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x701 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement26/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x702 = args[2][62 * steps + ((cycle - 0) & mask)];
    assert(x702 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement26/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x703 = args[2][63 * steps + ((cycle - 0) & mask)];
    assert(x703 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x704 = x702 - x688;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x705 = x703 - x689;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x706 = x704 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x707 = x704 * x706;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x707 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x704 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x703 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x708 = x689 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x709 = x689 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x710 = x709 * x708;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x710 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x711 = x4 - x704;
    if (x711 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x712 = x705 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x713 = x705 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x714 = x705 * x713;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x715 = x714 * x712;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x715 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement27/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x716 = args[2][64 * steps + ((cycle - 0) & mask)];
    assert(x716 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement27/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x717 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x717 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x718 = x716 - x702;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x719 = x717 - x703;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x720 = x718 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x721 = x718 * x720;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x721 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x718 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x717 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x722 = x703 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x723 = x703 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x724 = x723 * x722;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x724 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x725 = x4 - x718;
    if (x725 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x726 = x719 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x727 = x719 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x728 = x719 * x727;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x729 = x728 * x726;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x729 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement28/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x730 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x730 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement28/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x731 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x731 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x732 = x730 - x716;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x733 = x731 - x717;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x734 = x732 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x735 = x732 * x734;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x735 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x732 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x731 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x736 = x717 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x737 = x717 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x738 = x737 * x736;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x738 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x739 = x4 - x732;
    if (x739 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x740 = x733 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x741 = x733 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x742 = x733 * x741;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x743 = x742 * x740;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x743 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement29/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x744 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x744 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement29/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x745 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x745 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x746 = x744 - x730;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x747 = x745 - x731;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x748 = x746 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x749 = x746 * x748;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x749 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x746 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x745 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x750 = x731 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x751 = x731 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x752 = x751 * x750;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x752 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x753 = x4 - x746;
    if (x753 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x754 = x747 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x755 = x747 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x756 = x747 * x755;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x757 = x756 * x754;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x757 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement30/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x758 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x758 != Fp::invalid());
    // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement30/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x759 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x759 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x760 = x758 - x744;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x761 = x759 - x745;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x762 = x760 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x763 = x760 * x762;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x763 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x760 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x759 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x764 = x745 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x765 = x745 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x766 = x765 * x764;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x766 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x767 = x4 - x760;
    if (x767 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x768 = x761 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x769 = x761 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x770 = x761 * x769;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x771 = x770 * x768;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x771 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x772 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x772 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x773 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x773 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x774 = x772 - x758;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x775 = x773 - x759;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x776 = x774 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x777 = x774 * x776;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x777 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x774 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x773 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x778 = x759 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x779 = x759 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x780 = x779 * x778;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x780 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x781 = x4 - x774;
    if (x781 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x782 = x775 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x783 = x775 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x784 = x775 * x783;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x785 = x784 * x782;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x785 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
  }
  if (x8 != 0) {
    {
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x786 = host_outs.at(0);
      auto x787 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][42 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x786);
        reg = x786;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][43 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x787);
        reg = x787;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x788 = host_outs.at(0);
      auto x789 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][44 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x788);
        reg = x788;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][45 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x789);
        reg = x789;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x790 = host_outs.at(0);
      auto x791 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][46 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x790);
        reg = x790;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][47 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x791);
        reg = x791;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x792 = host_outs.at(0);
      auto x793 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][48 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x792);
        reg = x792;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][49 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x793);
        reg = x793;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x794 = host_outs.at(0);
      auto x795 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][50 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x794);
        reg = x794;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][51 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x795);
        reg = x795;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x796 = host_outs.at(0);
      auto x797 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x796);
        reg = x796;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x797);
        reg = x797;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x798 = host_outs.at(0);
      auto x799 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x798);
        reg = x798;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][55 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x799);
        reg = x799;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x800 = host_outs.at(0);
      auto x801 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][56 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x800);
        reg = x800;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][57 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x801);
        reg = x801;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x802 = host_outs.at(0);
      auto x803 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][58 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x802);
        reg = x802;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][59 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x803);
        reg = x803;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x804 = host_outs.at(0);
      auto x805 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][60 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x804);
        reg = x804;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][61 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x805);
        reg = x805;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x806 = host_outs.at(0);
      auto x807 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][62 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x806);
        reg = x806;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][63 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x807);
        reg = x807;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x808 = host_outs.at(0);
      auto x809 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][64 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x808);
        reg = x808;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][65 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x809);
        reg = x809;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x810 = host_outs.at(0);
      auto x811 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][66 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x810);
        reg = x810;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][67 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x811);
        reg = x811;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x812 = host_outs.at(0);
      auto x813 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][68 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x812);
        reg = x812;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][69 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x813);
        reg = x813;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x814 = host_outs.at(0);
      auto x815 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][70 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x814);
        reg = x814;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][71 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x815);
        reg = x815;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x816 = host_outs.at(0);
      auto x817 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x816);
        reg = x816;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x817);
        reg = x817;
      }
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":52:0))
    auto x818 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x818 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":53:0))
    auto x819 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x819 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement16/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x820 = args[2][42 * steps + ((cycle - 0) & mask)];
    assert(x820 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement16/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x821 = args[2][43 * steps + ((cycle - 0) & mask)];
    assert(x821 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x822 = x820 - x818;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x823 = x821 - x819;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x824 = x822 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x825 = x822 * x824;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x825 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x822 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x821 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x826 = x819 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x827 = x819 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x828 = x827 * x826;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x828 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x829 = x4 - x822;
    if (x829 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x830 = x823 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x831 = x823 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x832 = x823 * x831;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x833 = x832 * x830;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x833 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement17/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x834 = args[2][44 * steps + ((cycle - 0) & mask)];
    assert(x834 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement17/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x835 = args[2][45 * steps + ((cycle - 0) & mask)];
    assert(x835 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x836 = x834 - x820;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x837 = x835 - x821;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x838 = x836 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x839 = x836 * x838;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x839 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x836 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x835 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x840 = x821 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x841 = x821 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x842 = x841 * x840;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x842 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x843 = x4 - x836;
    if (x843 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x844 = x837 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x845 = x837 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x846 = x837 * x845;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x847 = x846 * x844;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x847 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement18/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x848 = args[2][46 * steps + ((cycle - 0) & mask)];
    assert(x848 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement18/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x849 = args[2][47 * steps + ((cycle - 0) & mask)];
    assert(x849 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x850 = x848 - x834;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x851 = x849 - x835;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x852 = x850 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x853 = x850 * x852;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x853 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x850 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x849 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x854 = x835 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x855 = x835 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x856 = x855 * x854;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x856 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x857 = x4 - x850;
    if (x857 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x858 = x851 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x859 = x851 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x860 = x851 * x859;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x861 = x860 * x858;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x861 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement19/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x862 = args[2][48 * steps + ((cycle - 0) & mask)];
    assert(x862 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement19/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x863 = args[2][49 * steps + ((cycle - 0) & mask)];
    assert(x863 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x864 = x862 - x848;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x865 = x863 - x849;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x866 = x864 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x867 = x864 * x866;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x867 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x864 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x863 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x868 = x849 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x869 = x849 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x870 = x869 * x868;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x870 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x871 = x4 - x864;
    if (x871 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x872 = x865 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x873 = x865 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x874 = x865 * x873;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x875 = x874 * x872;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x875 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement20/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x876 = args[2][50 * steps + ((cycle - 0) & mask)];
    assert(x876 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement20/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x877 = args[2][51 * steps + ((cycle - 0) & mask)];
    assert(x877 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x878 = x876 - x862;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x879 = x877 - x863;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x880 = x878 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x881 = x878 * x880;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x881 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x878 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x877 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x882 = x863 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x883 = x863 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x884 = x883 * x882;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x884 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x885 = x4 - x878;
    if (x885 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x886 = x879 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x887 = x879 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x888 = x879 * x887;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x889 = x888 * x886;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x889 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement21/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x890 = args[2][52 * steps + ((cycle - 0) & mask)];
    assert(x890 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement21/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x891 = args[2][53 * steps + ((cycle - 0) & mask)];
    assert(x891 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x892 = x890 - x876;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x893 = x891 - x877;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x894 = x892 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x895 = x892 * x894;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x895 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x892 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x891 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x896 = x877 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x897 = x877 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x898 = x897 * x896;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x898 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x899 = x4 - x892;
    if (x899 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x900 = x893 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x901 = x893 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x902 = x893 * x901;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x903 = x902 * x900;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x903 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement22/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x904 = args[2][54 * steps + ((cycle - 0) & mask)];
    assert(x904 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement22/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x905 = args[2][55 * steps + ((cycle - 0) & mask)];
    assert(x905 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x906 = x904 - x890;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x907 = x905 - x891;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x908 = x906 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x909 = x906 * x908;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x909 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x906 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x905 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x910 = x891 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x911 = x891 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x912 = x911 * x910;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x912 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x913 = x4 - x906;
    if (x913 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x914 = x907 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x915 = x907 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x916 = x907 * x915;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x917 = x916 * x914;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x917 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement23/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x918 = args[2][56 * steps + ((cycle - 0) & mask)];
    assert(x918 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement23/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x919 = args[2][57 * steps + ((cycle - 0) & mask)];
    assert(x919 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x920 = x918 - x904;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x921 = x919 - x905;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x922 = x920 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x923 = x920 * x922;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x923 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x920 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x919 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x924 = x905 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x925 = x905 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x926 = x925 * x924;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x926 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x927 = x4 - x920;
    if (x927 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x928 = x921 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x929 = x921 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x930 = x921 * x929;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x931 = x930 * x928;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x931 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement24/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x932 = args[2][58 * steps + ((cycle - 0) & mask)];
    assert(x932 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement24/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x933 = args[2][59 * steps + ((cycle - 0) & mask)];
    assert(x933 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x934 = x932 - x918;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x935 = x933 - x919;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x936 = x934 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x937 = x934 * x936;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x937 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x934 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x933 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x938 = x919 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x939 = x919 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x940 = x939 * x938;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x940 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x941 = x4 - x934;
    if (x941 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x942 = x935 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x943 = x935 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x944 = x935 * x943;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x945 = x944 * x942;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x945 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement25/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x946 = args[2][60 * steps + ((cycle - 0) & mask)];
    assert(x946 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement25/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x947 = args[2][61 * steps + ((cycle - 0) & mask)];
    assert(x947 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x948 = x946 - x932;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x949 = x947 - x933;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x950 = x948 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x951 = x948 * x950;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x951 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x948 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x947 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x952 = x933 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x953 = x933 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x954 = x953 * x952;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x954 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x955 = x4 - x948;
    if (x955 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x956 = x949 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x957 = x949 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x958 = x949 * x957;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x959 = x958 * x956;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x959 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement26/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x960 = args[2][62 * steps + ((cycle - 0) & mask)];
    assert(x960 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement26/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x961 = args[2][63 * steps + ((cycle - 0) & mask)];
    assert(x961 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x962 = x960 - x946;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x963 = x961 - x947;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x964 = x962 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x965 = x962 * x964;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x965 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x962 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x961 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x966 = x947 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x967 = x947 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x968 = x967 * x966;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x968 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x969 = x4 - x962;
    if (x969 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x970 = x963 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x971 = x963 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x972 = x963 * x971;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x973 = x972 * x970;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x973 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement27/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x974 = args[2][64 * steps + ((cycle - 0) & mask)];
    assert(x974 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement27/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x975 = args[2][65 * steps + ((cycle - 0) & mask)];
    assert(x975 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x976 = x974 - x960;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x977 = x975 - x961;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x978 = x976 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x979 = x976 * x978;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x979 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x976 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x975 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x980 = x961 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x981 = x961 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x982 = x981 * x980;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x982 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x983 = x4 - x976;
    if (x983 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x984 = x977 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x985 = x977 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x986 = x977 * x985;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x987 = x986 * x984;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x987 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement28/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x988 = args[2][66 * steps + ((cycle - 0) & mask)];
    assert(x988 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement28/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x989 = args[2][67 * steps + ((cycle - 0) & mask)];
    assert(x989 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x990 = x988 - x974;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x991 = x989 - x975;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x992 = x990 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x993 = x990 * x992;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x993 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x990 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x989 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x994 = x975 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x995 = x975 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x996 = x995 * x994;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x996 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x997 = x4 - x990;
    if (x997 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x998 = x991 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x999 = x991 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1000 = x991 * x999;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1001 = x1000 * x998;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x1001 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement29/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1002 = args[2][68 * steps + ((cycle - 0) & mask)];
    assert(x1002 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement29/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1003 = args[2][69 * steps + ((cycle - 0) & mask)];
    assert(x1003 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x1004 = x1002 - x988;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x1005 = x1003 - x989;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1006 = x1004 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1007 = x1004 * x1006;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x1007 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x1004 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x1003 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1008 = x989 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1009 = x989 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1010 = x1009 * x1008;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x1010 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x1011 = x4 - x1004;
    if (x1011 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1012 = x1005 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1013 = x1005 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1014 = x1005 * x1013;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1015 = x1014 * x1012;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x1015 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement30/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1016 = args[2][70 * steps + ((cycle - 0) & mask)];
    assert(x1016 != Fp::invalid());
    // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement30/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1017 = args[2][71 * steps + ((cycle - 0) & mask)];
    assert(x1017 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x1018 = x1016 - x1002;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x1019 = x1017 - x1003;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1020 = x1018 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1021 = x1018 * x1020;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x1021 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x1018 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x1017 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1022 = x1003 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1023 = x1003 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1024 = x1023 * x1022;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x1024 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x1025 = x4 - x1018;
    if (x1025 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1026 = x1019 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1027 = x1019 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1028 = x1019 * x1027;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1029 = x1028 * x1026;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x1029 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1030 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x1030 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1031 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x1031 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x1032 = x1030 - x1016;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x1033 = x1031 - x1017;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1034 = x1032 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1035 = x1032 * x1034;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x1035 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x1032 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x1031 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1036 = x1017 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1037 = x1017 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1038 = x1037 * x1036;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x1038 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x1039 = x4 - x1032;
    if (x1039 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1040 = x1033 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1041 = x1033 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1042 = x1033 * x1041;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1043 = x1042 * x1040;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x1043 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
  }
  if (x9 != 0) {
    {
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x1044 = host_outs.at(0);
      auto x1045 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][14 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1044);
        reg = x1044;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][15 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1045);
        reg = x1045;
      }
      host(ctx, "plonkRead", "bytes", host_args.data(), 0, host_outs.data(), 2);
      auto x1046 = host_outs.at(0);
      auto x1047 = host_outs.at(1);
      // loc("cirgen/components/bytes.cpp":16:0)
      {
        auto& reg = args[2][0 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1046);
        reg = x1046;
      }
      // loc("cirgen/components/bytes.cpp":17:0)
      {
        auto& reg = args[2][1 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1047);
        reg = x1047;
      }
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":52:0))
    auto x1048 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x1048 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":53:0))
    auto x1049 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x1049 != Fp::invalid());
    // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1050 = args[2][14 * steps + ((cycle - 0) & mask)];
    assert(x1050 != Fp::invalid());
    // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1051 = args[2][15 * steps + ((cycle - 0) & mask)];
    assert(x1051 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x1052 = x1050 - x1048;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x1053 = x1051 - x1049;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1054 = x1052 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1055 = x1052 * x1054;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x1055 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x1052 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x1051 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1056 = x1049 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1057 = x1049 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1058 = x1057 * x1056;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x1058 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x1059 = x4 - x1052;
    if (x1059 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1060 = x1053 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1061 = x1053 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1062 = x1053 * x1061;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1063 = x1062 * x1060;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x1063 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1064 = args[2][0 * steps + ((cycle - 0) & mask)];
    assert(x1064 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1065 = args[2][1 * steps + ((cycle - 0) & mask)];
    assert(x1065 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x1066 = x1064 - x1050;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x1067 = x1065 - x1051;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1068 = x1066 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1069 = x1066 * x1068;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x1069 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x1066 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x1065 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1070 = x1051 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1071 = x1051 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1072 = x1071 * x1070;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x1072 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x1073 = x4 - x1066;
    if (x1073 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1074 = x1067 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1075 = x1067 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1076 = x1067 * x1075;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1077 = x1076 * x1074;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x1077 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
  }
  if (x10 != 0) {
    // loc("cirgen/components/bytes.cpp":26:0)
    {
      auto& reg = args[2][10 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x0);
      reg = x0;
    }
    // loc("cirgen/components/bytes.cpp":27:0)
    {
      auto& reg = args[2][11 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x0);
      reg = x0;
    }
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":52:0))
    auto x1078 = args[2][0 * steps + ((cycle - 1) & mask)];
    assert(x1078 != Fp::invalid());
    // loc("Top/PlonkHeader/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":53:0))
    auto x1079 = args[2][1 * steps + ((cycle - 1) & mask)];
    assert(x1079 != Fp::invalid());
    // loc("Top/Mux/6/PlonkFini/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1080 = args[2][10 * steps + ((cycle - 0) & mask)];
    assert(x1080 != Fp::invalid());
    // loc("Top/Mux/6/PlonkFini/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":85:0))
    auto x1081 = args[2][11 * steps + ((cycle - 0) & mask)];
    assert(x1081 != Fp::invalid());
    // loc("cirgen/components/bytes.cpp":56:0)
    auto x1082 = x1080 - x1078;
    // loc("cirgen/components/bytes.cpp":57:0)
    auto x1083 = x1081 - x1079;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1084 = x1082 - x4;
    // loc("cirgen/components/bytes.cpp":59:0)
    auto x1085 = x1082 * x1084;
    // loc("cirgen/components/bytes.cpp":59:0)
    if (x1085 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:59");
    if (x1082 != 0) {
      // loc("cirgen/components/bytes.cpp":63:0)
      if (x1081 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:63");
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1086 = x1079 - x2;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1087 = x1079 - x0;
      // loc("cirgen/components/bytes.cpp":65:0)
      auto x1088 = x1087 * x1086;
      // loc("cirgen/components/bytes.cpp":65:0)
      if (x1088 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:65");
    }
    // loc("cirgen/components/bytes.cpp":67:0)
    auto x1089 = x4 - x1082;
    if (x1089 != 0) {
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1090 = x1083 - x1;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1091 = x1083 - x4;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1092 = x1083 * x1091;
      // loc("cirgen/components/bytes.cpp":69:0)
      auto x1093 = x1092 * x1090;
      // loc("cirgen/components/bytes.cpp":69:0)
      if (x1093 != 0) throw std::runtime_error("eqz failed at: cirgen/components/bytes.cpp:69");
    }
  }
  return x3;
}

} // namespace risc0::circuit::rv32im
// clang-format on
