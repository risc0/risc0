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

Fp step_verify_mem(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  std::array<Fp, 32> host_args;
  std::array<Fp, 32> host_outs;
  // loc("cirgen/components/ram.cpp":18:14)
  Fp x0(33554431);
  // loc("cirgen/components/ram.cpp":17:13)
  Fp x1(67108863);
  // loc("cirgen/components/bytes.cpp":79:30)
  Fp x2(2005401601);
  // loc("cirgen/components/bytes.cpp":78:26)
  Fp x3(255);
  // loc("cirgen/components/bytes.cpp":33:25)
  Fp x4(2);
  // loc("cirgen/components/bytes.cpp":17:13)
  Fp x5(0);
  // loc("cirgen/circuit/rv32im/top.cpp":14:17)
  Fp x6(1);
  // loc("Top/Code/OneHot/Reg1"("./cirgen/components/mux.h":33:25))
  auto x7 = args[0][2 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg2"("./cirgen/components/mux.h":33:25))
  auto x8 = args[0][3 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg3"("./cirgen/components/mux.h":33:25))
  auto x9 = args[0][4 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg4"("./cirgen/components/mux.h":33:25))
  auto x10 = args[0][5 * steps + ((cycle - 0) & mask)];
  assert(x10 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg5"("./cirgen/components/mux.h":33:25))
  auto x11 = args[0][6 * steps + ((cycle - 0) & mask)];
  assert(x11 != Fp::invalid());
  // loc("Top/Code/OneHot/Reg"("cirgen/circuit/rv32im/top.cpp":65:27))
  auto x12 = args[0][1 * steps + ((cycle - 0) & mask)];
  assert(x12 != Fp::invalid());
  if (x12 != 0) {
    // loc("cirgen/components/ram.cpp":10:3)
    {
      auto& reg = args[2][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x5);
      reg = x5;
    }
    // loc("cirgen/components/ram.cpp":11:3)
    {
      auto& reg = args[2][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x5);
      reg = x5;
    }
    // loc("cirgen/components/ram.cpp":12:3)
    {
      auto& reg = args[2][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x5);
      reg = x5;
    }
    // loc("cirgen/components/u32.cpp":18:5)
    {
      auto& reg = args[2][5 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x5);
      reg = x5;
    }
    // loc("cirgen/components/u32.cpp":18:5)
    {
      auto& reg = args[2][6 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x5);
      reg = x5;
    }
    // loc("cirgen/components/u32.cpp":18:5)
    {
      auto& reg = args[2][7 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x5);
      reg = x5;
    }
    // loc("cirgen/components/u32.cpp":18:5)
    {
      auto& reg = args[2][8 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x5);
      reg = x5;
    }
  }
  if (x7 != 0) {
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x13 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x13 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
    auto x14 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x14 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
    auto x15 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x15 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x16 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x16 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
    auto x17 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x17 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
    auto x18 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x18 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
    auto x19 = args[2][8 * steps + ((cycle - 1) & mask)];
    assert(x19 != Fp::invalid());
    // loc("cirgen/components/ram.cpp":31:3)
    {
      auto& reg = args[2][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x13);
      reg = x13;
    }
    // loc("cirgen/components/ram.cpp":32:3)
    {
      auto& reg = args[2][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x14);
      reg = x14;
    }
    // loc("cirgen/components/ram.cpp":33:3)
    {
      auto& reg = args[2][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x15);
      reg = x15;
    }
    // loc("cirgen/components/u32.cpp":72:5)
    {
      auto& reg = args[2][5 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x16);
      reg = x16;
    }
    // loc("cirgen/components/u32.cpp":72:5)
    {
      auto& reg = args[2][6 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x17);
      reg = x17;
    }
    // loc("cirgen/components/u32.cpp":72:5)
    {
      auto& reg = args[2][7 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x18);
      reg = x18;
    }
    // loc("cirgen/components/u32.cpp":72:5)
    {
      auto& reg = args[2][8 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x19);
      reg = x19;
    }
  }
  if (x8 != 0) {
    {
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x20 = host_outs.at(0);
      auto x21 = host_outs.at(1);
      auto x22 = host_outs.at(2);
      auto x23 = host_outs.at(3);
      auto x24 = host_outs.at(4);
      auto x25 = host_outs.at(5);
      auto x26 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":31:3)
      {
        auto& reg = args[2][76 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x20);
        reg = x20;
      }
      // loc("cirgen/components/ram.cpp":32:3)
      {
        auto& reg = args[2][77 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x21);
        reg = x21;
      }
      // loc("cirgen/components/ram.cpp":33:3)
      {
        auto& reg = args[2][78 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x22);
        reg = x22;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][79 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x23);
        reg = x23;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][80 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x24);
        reg = x24;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][81 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x25);
        reg = x25;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][82 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x26);
        reg = x26;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x27 = host_outs.at(0);
      auto x28 = host_outs.at(1);
      auto x29 = host_outs.at(2);
      auto x30 = host_outs.at(3);
      auto x31 = host_outs.at(4);
      auto x32 = host_outs.at(5);
      auto x33 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":31:3)
      {
        auto& reg = args[2][83 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x27);
        reg = x27;
      }
      // loc("cirgen/components/ram.cpp":32:3)
      {
        auto& reg = args[2][84 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x28);
        reg = x28;
      }
      // loc("cirgen/components/ram.cpp":33:3)
      {
        auto& reg = args[2][85 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x29);
        reg = x29;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][86 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x30);
        reg = x30;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][87 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x31);
        reg = x31;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][88 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x32);
        reg = x32;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][89 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x33);
        reg = x33;
      }
      host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
      auto x34 = host_outs.at(0);
      auto x35 = host_outs.at(1);
      auto x36 = host_outs.at(2);
      auto x37 = host_outs.at(3);
      auto x38 = host_outs.at(4);
      auto x39 = host_outs.at(5);
      auto x40 = host_outs.at(6);
      // loc("cirgen/components/ram.cpp":31:3)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x34);
        reg = x34;
      }
      // loc("cirgen/components/ram.cpp":32:3)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x35);
        reg = x35;
      }
      // loc("cirgen/components/ram.cpp":33:3)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x36);
        reg = x36;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x37);
        reg = x37;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x38);
        reg = x38;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x39);
        reg = x39;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x40);
        reg = x40;
      }
    }
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
    auto x41 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x41 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
    auto x42 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x42 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
    auto x43 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x43 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x44 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x44 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
    auto x45 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x45 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
    auto x46 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x46 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
    auto x47 = args[2][8 * steps + ((cycle - 1) & mask)];
    assert(x47 != Fp::invalid());
    {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x48 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x48 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":52:35)
      auto x49 = x41 - x48;
      // loc("cirgen/components/ram.cpp":52:35)
      auto x50 = (x49 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":52:27)
      auto x51 = x6 - x50;
      // loc("cirgen/components/ram.cpp":52:12)
      {
        auto& reg = args[2][90 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x51);
        reg = x51;
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x52 = args[2][90 * steps + ((cycle - 0) & mask)];
    assert(x52 != Fp::invalid());
    if (x52 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x53 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x53 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":62:31)
      auto x54 = x53 - x41;
      // loc("cirgen/components/ram.cpp":62:31)
      auto x55 = x54 - x6;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x56 = Fp(x55.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x56);
          reg = x56;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x57 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x57 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x58 = x55 - x57;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x59 = x58 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x60 = Fp(x59.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x60);
          reg = x60;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":79:16))
      auto x61 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x61 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x62 = x59 - x61;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x63 = x62 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x64 = Fp(x63.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x64);
          reg = x64;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x65 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x65 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x66 = x63 - x65;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x67 = x66 * x2;
      // loc("./cirgen/components/bits.h":53:23)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x67);
        reg = x67;
      }
    }
    // loc("cirgen/components/ram.cpp":64:19)
    auto x68 = x6 - x52;
    if (x68 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x69 = args[2][76 * steps + ((cycle - 0) & mask)];
      assert(x69 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":66:9)
      auto x70 = x41 - x69;
      // loc("cirgen/components/ram.cpp":66:9)
      if (x70 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x71 = args[2][77 * steps + ((cycle - 0) & mask)];
      assert(x71 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:17)
      auto x72 = x71 * x4;
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x73 = args[2][78 * steps + ((cycle - 0) & mask)];
      assert(x73 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:17)
      auto x74 = x72 + x73;
      // loc("cirgen/components/ram.cpp":68:45)
      auto x75 = x42 * x4;
      // loc("cirgen/components/ram.cpp":68:17)
      auto x76 = x74 - x75;
      // loc("cirgen/components/ram.cpp":68:17)
      auto x77 = x76 + x43;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x78 = Fp(x77.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x78);
          reg = x78;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x79 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x79 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x80 = x77 - x79;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x81 = x80 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x82 = Fp(x81.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x82);
          reg = x82;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":79:16))
      auto x83 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x83 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x84 = x81 - x83;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x85 = x84 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x86 = Fp(x85.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x86);
          reg = x86;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x87 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x87 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x88 = x85 - x87;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x89 = x88 * x2;
      // loc("./cirgen/components/bits.h":53:23)
      {
        auto& reg = args[2][52 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x89);
        reg = x89;
      }
      // loc("cirgen/components/ram.cpp":70:22)
      auto x90 = x6 - x73;
      if (x90 != 0) {
        // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
        auto x91 = args[2][79 * steps + ((cycle - 0) & mask)];
        assert(x91 != Fp::invalid());
        // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
        auto x92 = args[2][80 * steps + ((cycle - 0) & mask)];
        assert(x92 != Fp::invalid());
        // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
        auto x93 = args[2][81 * steps + ((cycle - 0) & mask)];
        assert(x93 != Fp::invalid());
        // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
        auto x94 = args[2][82 * steps + ((cycle - 0) & mask)];
        assert(x94 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":70:26)
        auto x95 = x44 - x91;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x95 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x96 = x45 - x92;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x96 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x97 = x46 - x93;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x97 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x98 = x47 - x94;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x98 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg"("cirgen/components/ram.cpp":47:40))
    auto x99 = args[2][76 * steps + ((cycle - 0) & mask)];
    assert(x99 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg1"("cirgen/components/ram.cpp":48:42))
    auto x100 = args[2][77 * steps + ((cycle - 0) & mask)];
    assert(x100 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/Reg2"("cirgen/components/ram.cpp":49:46))
    auto x101 = args[2][78 * steps + ((cycle - 0) & mask)];
    assert(x101 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x102 = args[2][79 * steps + ((cycle - 0) & mask)];
    assert(x102 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
    auto x103 = args[2][80 * steps + ((cycle - 0) & mask)];
    assert(x103 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
    auto x104 = args[2][81 * steps + ((cycle - 0) & mask)];
    assert(x104 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement3/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
    auto x105 = args[2][82 * steps + ((cycle - 0) & mask)];
    assert(x105 != Fp::invalid());
    {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x106 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x106 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":52:35)
      auto x107 = x99 - x106;
      // loc("cirgen/components/ram.cpp":52:35)
      auto x108 = (x107 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":52:27)
      auto x109 = x6 - x108;
      // loc("cirgen/components/ram.cpp":52:12)
      {
        auto& reg = args[2][91 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x109);
        reg = x109;
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x110 = args[2][91 * steps + ((cycle - 0) & mask)];
    assert(x110 != Fp::invalid());
    if (x110 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x111 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x111 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":62:31)
      auto x112 = x111 - x99;
      // loc("cirgen/components/ram.cpp":62:31)
      auto x113 = x112 - x6;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x114 = Fp(x113.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x114);
          reg = x114;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
      auto x115 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x115 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x116 = x113 - x115;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x117 = x116 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x118 = Fp(x117.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x118);
          reg = x118;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x119 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x119 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x120 = x117 - x119;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x121 = x120 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x122 = Fp(x121.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x122);
          reg = x122;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
      auto x123 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x123 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x124 = x121 - x123;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x125 = x124 * x2;
      // loc("./cirgen/components/bits.h":53:23)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x125);
        reg = x125;
      }
    }
    // loc("cirgen/components/ram.cpp":64:19)
    auto x126 = x6 - x110;
    if (x126 != 0) {
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x127 = args[2][83 * steps + ((cycle - 0) & mask)];
      assert(x127 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":66:9)
      auto x128 = x99 - x127;
      // loc("cirgen/components/ram.cpp":66:9)
      if (x128 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x129 = args[2][84 * steps + ((cycle - 0) & mask)];
      assert(x129 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:17)
      auto x130 = x129 * x4;
      // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x131 = args[2][85 * steps + ((cycle - 0) & mask)];
      assert(x131 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:17)
      auto x132 = x130 + x131;
      // loc("cirgen/components/ram.cpp":68:45)
      auto x133 = x100 * x4;
      // loc("cirgen/components/ram.cpp":68:17)
      auto x134 = x132 - x133;
      // loc("cirgen/components/ram.cpp":68:17)
      auto x135 = x134 + x101;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x136 = Fp(x135.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][13 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x136);
          reg = x136;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
      auto x137 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x137 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x138 = x135 - x137;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x139 = x138 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x140 = Fp(x139.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][14 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x140);
          reg = x140;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x141 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x141 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x142 = x139 - x141;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x143 = x142 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x144 = Fp(x143.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][15 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x144);
          reg = x144;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
      auto x145 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x145 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x146 = x143 - x145;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x147 = x146 * x2;
      // loc("./cirgen/components/bits.h":53:23)
      {
        auto& reg = args[2][53 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x147);
        reg = x147;
      }
      // loc("cirgen/components/ram.cpp":70:22)
      auto x148 = x6 - x131;
      if (x148 != 0) {
        // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
        auto x149 = args[2][86 * steps + ((cycle - 0) & mask)];
        assert(x149 != Fp::invalid());
        // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
        auto x150 = args[2][87 * steps + ((cycle - 0) & mask)];
        assert(x150 != Fp::invalid());
        // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
        auto x151 = args[2][88 * steps + ((cycle - 0) & mask)];
        assert(x151 != Fp::invalid());
        // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
        auto x152 = args[2][89 * steps + ((cycle - 0) & mask)];
        assert(x152 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":70:26)
        auto x153 = x102 - x149;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x153 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x154 = x103 - x150;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x154 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x155 = x104 - x151;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x155 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x156 = x105 - x152;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x156 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":47:40))
    auto x157 = args[2][83 * steps + ((cycle - 0) & mask)];
    assert(x157 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":48:42))
    auto x158 = args[2][84 * steps + ((cycle - 0) & mask)];
    assert(x158 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":49:46))
    auto x159 = args[2][85 * steps + ((cycle - 0) & mask)];
    assert(x159 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x160 = args[2][86 * steps + ((cycle - 0) & mask)];
    assert(x160 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
    auto x161 = args[2][87 * steps + ((cycle - 0) & mask)];
    assert(x161 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
    auto x162 = args[2][88 * steps + ((cycle - 0) & mask)];
    assert(x162 != Fp::invalid());
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
    auto x163 = args[2][89 * steps + ((cycle - 0) & mask)];
    assert(x163 != Fp::invalid());
    {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x164 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x164 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":52:35)
      auto x165 = x157 - x164;
      // loc("cirgen/components/ram.cpp":52:35)
      auto x166 = (x165 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":52:27)
      auto x167 = x6 - x166;
      // loc("cirgen/components/ram.cpp":52:12)
      {
        auto& reg = args[2][92 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x167);
        reg = x167;
      }
    }
    // loc("Top/Mux/2/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x168 = args[2][92 * steps + ((cycle - 0) & mask)];
    assert(x168 != Fp::invalid());
    if (x168 != 0) {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x169 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x169 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":62:31)
      auto x170 = x169 - x157;
      // loc("cirgen/components/ram.cpp":62:31)
      auto x171 = x170 - x6;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x172 = Fp(x171.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x172);
          reg = x172;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x173 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x173 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x174 = x171 - x173;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x175 = x174 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x176 = Fp(x175.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x176);
          reg = x176;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
      auto x177 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x177 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x178 = x175 - x177;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x179 = x178 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x180 = Fp(x179.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][18 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x180);
          reg = x180;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x181 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x181 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x182 = x179 - x181;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x183 = x182 * x2;
      // loc("./cirgen/components/bits.h":53:23)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x183);
        reg = x183;
      }
    }
    // loc("cirgen/components/ram.cpp":64:19)
    auto x184 = x6 - x168;
    if (x184 != 0) {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x185 = args[2][2 * steps + ((cycle - 0) & mask)];
      assert(x185 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":66:9)
      auto x186 = x157 - x185;
      // loc("cirgen/components/ram.cpp":66:9)
      if (x186 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x187 = args[2][3 * steps + ((cycle - 0) & mask)];
      assert(x187 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:17)
      auto x188 = x187 * x4;
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x189 = args[2][4 * steps + ((cycle - 0) & mask)];
      assert(x189 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:17)
      auto x190 = x188 + x189;
      // loc("cirgen/components/ram.cpp":68:45)
      auto x191 = x158 * x4;
      // loc("cirgen/components/ram.cpp":68:17)
      auto x192 = x190 - x191;
      // loc("cirgen/components/ram.cpp":68:17)
      auto x193 = x192 + x159;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x194 = Fp(x193.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][16 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x194);
          reg = x194;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x195 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x195 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x196 = x193 - x195;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x197 = x196 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x198 = Fp(x197.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][17 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x198);
          reg = x198;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
      auto x199 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x199 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x200 = x197 - x199;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x201 = x200 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x202 = Fp(x201.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][18 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x202);
          reg = x202;
        }
      }
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x203 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x203 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x204 = x201 - x203;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x205 = x204 * x2;
      // loc("./cirgen/components/bits.h":53:23)
      {
        auto& reg = args[2][54 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x205);
        reg = x205;
      }
      // loc("cirgen/components/ram.cpp":70:22)
      auto x206 = x6 - x189;
      if (x206 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
        auto x207 = args[2][5 * steps + ((cycle - 0) & mask)];
        assert(x207 != Fp::invalid());
        // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
        auto x208 = args[2][6 * steps + ((cycle - 0) & mask)];
        assert(x208 != Fp::invalid());
        // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
        auto x209 = args[2][7 * steps + ((cycle - 0) & mask)];
        assert(x209 != Fp::invalid());
        // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
        auto x210 = args[2][8 * steps + ((cycle - 0) & mask)];
        assert(x210 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":70:26)
        auto x211 = x160 - x207;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x211 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x212 = x161 - x208;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x212 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x213 = x162 - x209;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x213 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x214 = x163 - x210;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x214 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
      }
    }
  }
  if (x9 != 0) {
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x215 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x215 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
    auto x216 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x216 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
    auto x217 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x217 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x218 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x218 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
    auto x219 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x219 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
    auto x220 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x220 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
    auto x221 = args[2][8 * steps + ((cycle - 1) & mask)];
    assert(x221 != Fp::invalid());
    // loc("cirgen/components/ram.cpp":31:3)
    {
      auto& reg = args[2][2 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x215);
      reg = x215;
    }
    // loc("cirgen/components/ram.cpp":32:3)
    {
      auto& reg = args[2][3 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x216);
      reg = x216;
    }
    // loc("cirgen/components/ram.cpp":33:3)
    {
      auto& reg = args[2][4 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x217);
      reg = x217;
    }
    // loc("cirgen/components/u32.cpp":72:5)
    {
      auto& reg = args[2][5 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x218);
      reg = x218;
    }
    // loc("cirgen/components/u32.cpp":72:5)
    {
      auto& reg = args[2][6 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x219);
      reg = x219;
    }
    // loc("cirgen/components/u32.cpp":72:5)
    {
      auto& reg = args[2][7 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x220);
      reg = x220;
    }
    // loc("cirgen/components/u32.cpp":72:5)
    {
      auto& reg = args[2][8 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x221);
      reg = x221;
    }
  }
  if (x10 != 0) {
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x222 = args[2][94 * steps + ((cycle - 0) & mask)];
    assert(x222 != Fp::invalid());
    if (x222 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x223 = host_outs.at(0);
        auto x224 = host_outs.at(1);
        auto x225 = host_outs.at(2);
        auto x226 = host_outs.at(3);
        auto x227 = host_outs.at(4);
        auto x228 = host_outs.at(5);
        auto x229 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][135 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x223);
          reg = x223;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x224);
          reg = x224;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x225);
          reg = x225;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x226);
          reg = x226;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x227);
          reg = x227;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x228);
          reg = x228;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x229);
          reg = x229;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x230 = host_outs.at(0);
        auto x231 = host_outs.at(1);
        auto x232 = host_outs.at(2);
        auto x233 = host_outs.at(3);
        auto x234 = host_outs.at(4);
        auto x235 = host_outs.at(5);
        auto x236 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x230);
          reg = x230;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x231);
          reg = x231;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x232);
          reg = x232;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x233);
          reg = x233;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x234);
          reg = x234;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x235);
          reg = x235;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x236);
          reg = x236;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x237 = host_outs.at(0);
        auto x238 = host_outs.at(1);
        auto x239 = host_outs.at(2);
        auto x240 = host_outs.at(3);
        auto x241 = host_outs.at(4);
        auto x242 = host_outs.at(5);
        auto x243 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x237);
          reg = x237;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x238);
          reg = x238;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x239);
          reg = x239;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x240);
          reg = x240;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x241);
          reg = x241;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x242);
          reg = x242;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x243);
          reg = x243;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x244 = host_outs.at(0);
        auto x245 = host_outs.at(1);
        auto x246 = host_outs.at(2);
        auto x247 = host_outs.at(3);
        auto x248 = host_outs.at(4);
        auto x249 = host_outs.at(5);
        auto x250 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x244);
          reg = x244;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x245);
          reg = x245;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x246);
          reg = x246;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x247);
          reg = x247;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x248);
          reg = x248;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x249);
          reg = x249;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x250);
          reg = x250;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
      auto x251 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x251 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x252 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x252 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x253 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x253 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x254 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x254 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x255 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x255 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x256 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x256 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x257 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x257 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x258 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x258 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x259 = x251 - x258;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x260 = (x259 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x261 = x6 - x260;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x261);
          reg = x261;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x262 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x262 != Fp::invalid());
      if (x262 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x263 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x263 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x264 = x263 - x251;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x265 = x264 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x266 = Fp(x265.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x266);
            reg = x266;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x267 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x267 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x268 = x265 - x267;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x269 = x268 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x270 = Fp(x269.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x270);
            reg = x270;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x271 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x271 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x272 = x269 - x271;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x273 = x272 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x274 = Fp(x273.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x274);
            reg = x274;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x275 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x275 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x276 = x273 - x275;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x277 = x276 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x277);
          reg = x277;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x278 = x6 - x262;
      if (x278 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x279 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x279 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x280 = x251 - x279;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x280 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x281 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x281 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x282 = x281 * x4;
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x283 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x283 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x284 = x282 + x283;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x285 = x252 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x286 = x284 - x285;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x287 = x286 + x253;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x288 = Fp(x287.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x288);
            reg = x288;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x289 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x289 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x290 = x287 - x289;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x291 = x290 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x292 = Fp(x291.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x292);
            reg = x292;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x293 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x293 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x294 = x291 - x293;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x295 = x294 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x296 = Fp(x295.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x296);
            reg = x296;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x297 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x297 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x298 = x295 - x297;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x299 = x298 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x299);
          reg = x299;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x300 = x6 - x283;
        if (x300 != 0) {
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x301 = args[2][138 * steps + ((cycle - 0) & mask)];
          assert(x301 != Fp::invalid());
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x302 = args[2][139 * steps + ((cycle - 0) & mask)];
          assert(x302 != Fp::invalid());
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x303 = args[2][140 * steps + ((cycle - 0) & mask)];
          assert(x303 != Fp::invalid());
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x304 = args[2][141 * steps + ((cycle - 0) & mask)];
          assert(x304 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x305 = x254 - x301;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x305 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x306 = x255 - x302;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x306 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x307 = x256 - x303;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x307 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x308 = x257 - x304;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x308 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":47:40))
      auto x309 = args[2][135 * steps + ((cycle - 0) & mask)];
      assert(x309 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x310 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x310 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x311 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x311 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x312 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x312 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x313 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x313 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x314 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x314 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x315 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x315 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x316 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x316 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x317 = x309 - x316;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x318 = (x317 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x319 = x6 - x318;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x319);
          reg = x319;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x320 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x320 != Fp::invalid());
      if (x320 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x321 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x321 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x322 = x321 - x309;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x323 = x322 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x324 = Fp(x323.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x324);
            reg = x324;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x325 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x325 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x326 = x323 - x325;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x327 = x326 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x328 = Fp(x327.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x328);
            reg = x328;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x329 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x329 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x330 = x327 - x329;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x331 = x330 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x332 = Fp(x331.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x332);
            reg = x332;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x333 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x333 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x334 = x331 - x333;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x335 = x334 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x335);
          reg = x335;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x336 = x6 - x320;
      if (x336 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x337 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x337 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x338 = x309 - x337;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x338 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x339 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x339 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x340 = x339 * x4;
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x341 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x341 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x342 = x340 + x341;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x343 = x310 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x344 = x342 - x343;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x345 = x344 + x311;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x346 = Fp(x345.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x346);
            reg = x346;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x347 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x347 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x348 = x345 - x347;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x349 = x348 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x350 = Fp(x349.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x350);
            reg = x350;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x351 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x351 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x352 = x349 - x351;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x353 = x352 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x354 = Fp(x353.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x354);
            reg = x354;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x355 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x355 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x356 = x353 - x355;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x357 = x356 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x357);
          reg = x357;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x358 = x6 - x341;
        if (x358 != 0) {
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x359 = args[2][145 * steps + ((cycle - 0) & mask)];
          assert(x359 != Fp::invalid());
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x360 = args[2][146 * steps + ((cycle - 0) & mask)];
          assert(x360 != Fp::invalid());
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x361 = args[2][147 * steps + ((cycle - 0) & mask)];
          assert(x361 != Fp::invalid());
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x362 = args[2][148 * steps + ((cycle - 0) & mask)];
          assert(x362 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x363 = x312 - x359;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x363 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x364 = x313 - x360;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x364 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x365 = x314 - x361;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x365 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x366 = x315 - x362;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x366 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":47:40))
      auto x367 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x367 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x368 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x368 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x369 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x369 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x370 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x370 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x371 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x371 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x372 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x372 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x373 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x373 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x374 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x374 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x375 = x367 - x374;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x376 = (x375 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x377 = x6 - x376;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x377);
          reg = x377;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x378 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x378 != Fp::invalid());
      if (x378 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x379 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x379 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x380 = x379 - x367;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x381 = x380 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x382 = Fp(x381.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x382);
            reg = x382;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x383 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x383 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x384 = x381 - x383;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x385 = x384 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x386 = Fp(x385.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x386);
            reg = x386;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x387 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x387 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x388 = x385 - x387;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x389 = x388 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x390 = Fp(x389.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x390);
            reg = x390;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x391 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x391 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x392 = x389 - x391;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x393 = x392 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x393);
          reg = x393;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x394 = x6 - x378;
      if (x394 != 0) {
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x395 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x395 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x396 = x367 - x395;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x396 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x397 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x397 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x398 = x397 * x4;
        // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x399 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x399 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x400 = x398 + x399;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x401 = x368 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x402 = x400 - x401;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x403 = x402 + x369;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x404 = Fp(x403.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x404);
            reg = x404;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x405 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x405 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x406 = x403 - x405;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x407 = x406 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x408 = Fp(x407.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x408);
            reg = x408;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x409 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x409 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x410 = x407 - x409;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x411 = x410 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x412 = Fp(x411.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x412);
            reg = x412;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x413 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x413 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x414 = x411 - x413;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x415 = x414 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x415);
          reg = x415;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x416 = x6 - x399;
        if (x416 != 0) {
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x417 = args[2][152 * steps + ((cycle - 0) & mask)];
          assert(x417 != Fp::invalid());
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x418 = args[2][153 * steps + ((cycle - 0) & mask)];
          assert(x418 != Fp::invalid());
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x419 = args[2][154 * steps + ((cycle - 0) & mask)];
          assert(x419 != Fp::invalid());
          // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x420 = args[2][155 * steps + ((cycle - 0) & mask)];
          assert(x420 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x421 = x370 - x417;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x421 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x422 = x371 - x418;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x422 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x423 = x372 - x419;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x423 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x424 = x373 - x420;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x424 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":47:40))
      auto x425 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x425 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x426 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x426 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x427 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x427 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x428 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x428 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x429 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x429 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x430 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x430 != Fp::invalid());
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x431 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x431 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x432 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x432 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x433 = x425 - x432;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x434 = (x433 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x435 = x6 - x434;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x435);
          reg = x435;
        }
      }
      // loc("Top/Mux/4/Mux/0/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x436 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x436 != Fp::invalid());
      if (x436 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x437 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x437 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x438 = x437 - x425;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x439 = x438 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x440 = Fp(x439.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x440);
            reg = x440;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x441 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x441 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x442 = x439 - x441;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x443 = x442 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x444 = Fp(x443.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x444);
            reg = x444;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x445 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x445 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x446 = x443 - x445;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x447 = x446 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x448 = Fp(x447.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x448);
            reg = x448;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x449 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x449 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x450 = x447 - x449;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x451 = x450 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x451);
          reg = x451;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x452 = x6 - x436;
      if (x452 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x453 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x453 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x454 = x425 - x453;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x454 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x455 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x455 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x456 = x455 * x4;
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x457 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x457 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x458 = x456 + x457;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x459 = x426 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x460 = x458 - x459;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x461 = x460 + x427;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x462 = Fp(x461.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x462);
            reg = x462;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x463 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x463 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x464 = x461 - x463;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x465 = x464 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x466 = Fp(x465.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x466);
            reg = x466;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x467 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x467 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x468 = x465 - x467;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x469 = x468 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x470 = Fp(x469.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x470);
            reg = x470;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x471 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x471 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x472 = x469 - x471;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x473 = x472 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x473);
          reg = x473;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x474 = x6 - x457;
        if (x474 != 0) {
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x475 = args[2][5 * steps + ((cycle - 0) & mask)];
          assert(x475 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x476 = args[2][6 * steps + ((cycle - 0) & mask)];
          assert(x476 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x477 = args[2][7 * steps + ((cycle - 0) & mask)];
          assert(x477 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x478 = args[2][8 * steps + ((cycle - 0) & mask)];
          assert(x478 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x479 = x428 - x475;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x479 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x480 = x429 - x476;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x480 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x481 = x430 - x477;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x481 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x482 = x431 - x478;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x482 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x483 = args[2][95 * steps + ((cycle - 0) & mask)];
    assert(x483 != Fp::invalid());
    if (x483 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x484 = host_outs.at(0);
        auto x485 = host_outs.at(1);
        auto x486 = host_outs.at(2);
        auto x487 = host_outs.at(3);
        auto x488 = host_outs.at(4);
        auto x489 = host_outs.at(5);
        auto x490 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][135 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x484);
          reg = x484;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x485);
          reg = x485;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x486);
          reg = x486;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x487);
          reg = x487;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x488);
          reg = x488;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x489);
          reg = x489;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x490);
          reg = x490;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x491 = host_outs.at(0);
        auto x492 = host_outs.at(1);
        auto x493 = host_outs.at(2);
        auto x494 = host_outs.at(3);
        auto x495 = host_outs.at(4);
        auto x496 = host_outs.at(5);
        auto x497 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x491);
          reg = x491;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x492);
          reg = x492;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x493);
          reg = x493;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x494);
          reg = x494;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x495);
          reg = x495;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x496);
          reg = x496;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x497);
          reg = x497;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x498 = host_outs.at(0);
        auto x499 = host_outs.at(1);
        auto x500 = host_outs.at(2);
        auto x501 = host_outs.at(3);
        auto x502 = host_outs.at(4);
        auto x503 = host_outs.at(5);
        auto x504 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x498);
          reg = x498;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x499);
          reg = x499;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x500);
          reg = x500;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x501);
          reg = x501;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x502);
          reg = x502;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x503);
          reg = x503;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x504);
          reg = x504;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x505 = host_outs.at(0);
        auto x506 = host_outs.at(1);
        auto x507 = host_outs.at(2);
        auto x508 = host_outs.at(3);
        auto x509 = host_outs.at(4);
        auto x510 = host_outs.at(5);
        auto x511 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x505);
          reg = x505;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x506);
          reg = x506;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x507);
          reg = x507;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x508);
          reg = x508;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x509);
          reg = x509;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x510);
          reg = x510;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x511);
          reg = x511;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
      auto x512 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x512 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x513 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x513 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x514 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x514 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x515 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x515 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x516 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x516 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x517 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x517 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x518 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x518 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x519 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x519 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x520 = x512 - x519;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x521 = (x520 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x522 = x6 - x521;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x522);
          reg = x522;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x523 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x523 != Fp::invalid());
      if (x523 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x524 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x524 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x525 = x524 - x512;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x526 = x525 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x527 = Fp(x526.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x527);
            reg = x527;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x528 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x528 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x529 = x526 - x528;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x530 = x529 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x531 = Fp(x530.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x531);
            reg = x531;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x532 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x532 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x533 = x530 - x532;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x534 = x533 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x535 = Fp(x534.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x535);
            reg = x535;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x536 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x536 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x537 = x534 - x536;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x538 = x537 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x538);
          reg = x538;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x539 = x6 - x523;
      if (x539 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x540 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x540 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x541 = x512 - x540;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x541 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x542 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x542 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x543 = x542 * x4;
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x544 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x544 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x545 = x543 + x544;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x546 = x513 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x547 = x545 - x546;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x548 = x547 + x514;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x549 = Fp(x548.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x549);
            reg = x549;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x550 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x550 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x551 = x548 - x550;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x552 = x551 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x553 = Fp(x552.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x553);
            reg = x553;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x554 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x554 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x555 = x552 - x554;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x556 = x555 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x557 = Fp(x556.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x557);
            reg = x557;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x558 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x558 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x559 = x556 - x558;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x560 = x559 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x560);
          reg = x560;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x561 = x6 - x544;
        if (x561 != 0) {
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x562 = args[2][138 * steps + ((cycle - 0) & mask)];
          assert(x562 != Fp::invalid());
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x563 = args[2][139 * steps + ((cycle - 0) & mask)];
          assert(x563 != Fp::invalid());
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x564 = args[2][140 * steps + ((cycle - 0) & mask)];
          assert(x564 != Fp::invalid());
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x565 = args[2][141 * steps + ((cycle - 0) & mask)];
          assert(x565 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x566 = x515 - x562;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x566 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x567 = x516 - x563;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x567 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x568 = x517 - x564;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x568 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x569 = x518 - x565;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x569 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":47:40))
      auto x570 = args[2][135 * steps + ((cycle - 0) & mask)];
      assert(x570 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x571 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x571 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x572 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x572 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x573 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x573 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x574 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x574 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x575 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x575 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x576 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x576 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x577 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x577 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x578 = x570 - x577;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x579 = (x578 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x580 = x6 - x579;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x580);
          reg = x580;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x581 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x581 != Fp::invalid());
      if (x581 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x582 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x582 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x583 = x582 - x570;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x584 = x583 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x585 = Fp(x584.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x585);
            reg = x585;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x586 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x586 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x587 = x584 - x586;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x588 = x587 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x589 = Fp(x588.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x589);
            reg = x589;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x590 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x590 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x591 = x588 - x590;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x592 = x591 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x593 = Fp(x592.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x593);
            reg = x593;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x594 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x594 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x595 = x592 - x594;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x596 = x595 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x596);
          reg = x596;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x597 = x6 - x581;
      if (x597 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x598 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x598 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x599 = x570 - x598;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x599 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x600 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x600 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x601 = x600 * x4;
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x602 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x602 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x603 = x601 + x602;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x604 = x571 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x605 = x603 - x604;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x606 = x605 + x572;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x607 = Fp(x606.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x607);
            reg = x607;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x608 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x608 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x609 = x606 - x608;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x610 = x609 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x611 = Fp(x610.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x611);
            reg = x611;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x612 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x612 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x613 = x610 - x612;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x614 = x613 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x615 = Fp(x614.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x615);
            reg = x615;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x616 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x616 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x617 = x614 - x616;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x618 = x617 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x618);
          reg = x618;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x619 = x6 - x602;
        if (x619 != 0) {
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x620 = args[2][145 * steps + ((cycle - 0) & mask)];
          assert(x620 != Fp::invalid());
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x621 = args[2][146 * steps + ((cycle - 0) & mask)];
          assert(x621 != Fp::invalid());
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x622 = args[2][147 * steps + ((cycle - 0) & mask)];
          assert(x622 != Fp::invalid());
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x623 = args[2][148 * steps + ((cycle - 0) & mask)];
          assert(x623 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x624 = x573 - x620;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x624 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x625 = x574 - x621;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x625 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x626 = x575 - x622;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x626 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x627 = x576 - x623;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x627 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":47:40))
      auto x628 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x628 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x629 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x629 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x630 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x630 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x631 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x631 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x632 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x632 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x633 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x633 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x634 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x634 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x635 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x635 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x636 = x628 - x635;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x637 = (x636 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x638 = x6 - x637;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x638);
          reg = x638;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x639 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x639 != Fp::invalid());
      if (x639 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x640 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x640 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x641 = x640 - x628;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x642 = x641 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x643 = Fp(x642.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x643);
            reg = x643;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x644 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x644 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x645 = x642 - x644;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x646 = x645 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x647 = Fp(x646.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x647);
            reg = x647;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x648 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x648 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x649 = x646 - x648;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x650 = x649 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x651 = Fp(x650.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x651);
            reg = x651;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x652 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x652 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x653 = x650 - x652;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x654 = x653 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x654);
          reg = x654;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x655 = x6 - x639;
      if (x655 != 0) {
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x656 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x656 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x657 = x628 - x656;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x657 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x658 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x658 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x659 = x658 * x4;
        // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x660 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x660 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x661 = x659 + x660;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x662 = x629 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x663 = x661 - x662;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x664 = x663 + x630;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x665 = Fp(x664.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x665);
            reg = x665;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x666 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x666 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x667 = x664 - x666;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x668 = x667 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x669 = Fp(x668.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x669);
            reg = x669;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x670 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x670 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x671 = x668 - x670;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x672 = x671 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x673 = Fp(x672.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x673);
            reg = x673;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x674 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x674 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x675 = x672 - x674;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x676 = x675 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x676);
          reg = x676;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x677 = x6 - x660;
        if (x677 != 0) {
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x678 = args[2][152 * steps + ((cycle - 0) & mask)];
          assert(x678 != Fp::invalid());
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x679 = args[2][153 * steps + ((cycle - 0) & mask)];
          assert(x679 != Fp::invalid());
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x680 = args[2][154 * steps + ((cycle - 0) & mask)];
          assert(x680 != Fp::invalid());
          // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x681 = args[2][155 * steps + ((cycle - 0) & mask)];
          assert(x681 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x682 = x631 - x678;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x682 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x683 = x632 - x679;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x683 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x684 = x633 - x680;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x684 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x685 = x634 - x681;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x685 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":47:40))
      auto x686 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x686 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x687 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x687 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x688 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x688 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x689 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x689 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x690 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x690 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x691 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x691 != Fp::invalid());
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x692 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x692 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x693 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x693 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x694 = x686 - x693;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x695 = (x694 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x696 = x6 - x695;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x696);
          reg = x696;
        }
      }
      // loc("Top/Mux/4/Mux/1/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x697 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x697 != Fp::invalid());
      if (x697 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x698 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x698 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x699 = x698 - x686;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x700 = x699 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x701 = Fp(x700.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x701);
            reg = x701;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x702 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x702 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x703 = x700 - x702;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x704 = x703 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x705 = Fp(x704.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x705);
            reg = x705;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x706 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x706 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x707 = x704 - x706;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x708 = x707 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x709 = Fp(x708.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x709);
            reg = x709;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x710 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x710 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x711 = x708 - x710;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x712 = x711 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x712);
          reg = x712;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x713 = x6 - x697;
      if (x713 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x714 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x714 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x715 = x686 - x714;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x715 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x716 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x716 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x717 = x716 * x4;
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x718 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x718 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x719 = x717 + x718;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x720 = x687 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x721 = x719 - x720;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x722 = x721 + x688;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x723 = Fp(x722.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x723);
            reg = x723;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x724 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x724 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x725 = x722 - x724;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x726 = x725 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x727 = Fp(x726.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x727);
            reg = x727;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x728 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x728 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x729 = x726 - x728;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x730 = x729 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x731 = Fp(x730.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x731);
            reg = x731;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x732 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x732 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x733 = x730 - x732;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x734 = x733 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x734);
          reg = x734;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x735 = x6 - x718;
        if (x735 != 0) {
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x736 = args[2][5 * steps + ((cycle - 0) & mask)];
          assert(x736 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x737 = args[2][6 * steps + ((cycle - 0) & mask)];
          assert(x737 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x738 = args[2][7 * steps + ((cycle - 0) & mask)];
          assert(x738 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x739 = args[2][8 * steps + ((cycle - 0) & mask)];
          assert(x739 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x740 = x689 - x736;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x740 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x741 = x690 - x737;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x741 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x742 = x691 - x738;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x742 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x743 = x692 - x739;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x743 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x744 = args[2][96 * steps + ((cycle - 0) & mask)];
    assert(x744 != Fp::invalid());
    if (x744 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x745 = host_outs.at(0);
        auto x746 = host_outs.at(1);
        auto x747 = host_outs.at(2);
        auto x748 = host_outs.at(3);
        auto x749 = host_outs.at(4);
        auto x750 = host_outs.at(5);
        auto x751 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][135 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x745);
          reg = x745;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x746);
          reg = x746;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x747);
          reg = x747;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x748);
          reg = x748;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x749);
          reg = x749;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x750);
          reg = x750;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x751);
          reg = x751;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x752 = host_outs.at(0);
        auto x753 = host_outs.at(1);
        auto x754 = host_outs.at(2);
        auto x755 = host_outs.at(3);
        auto x756 = host_outs.at(4);
        auto x757 = host_outs.at(5);
        auto x758 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x752);
          reg = x752;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x753);
          reg = x753;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x754);
          reg = x754;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x755);
          reg = x755;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x756);
          reg = x756;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x757);
          reg = x757;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x758);
          reg = x758;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x759 = host_outs.at(0);
        auto x760 = host_outs.at(1);
        auto x761 = host_outs.at(2);
        auto x762 = host_outs.at(3);
        auto x763 = host_outs.at(4);
        auto x764 = host_outs.at(5);
        auto x765 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x759);
          reg = x759;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x760);
          reg = x760;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x761);
          reg = x761;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x762);
          reg = x762;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x763);
          reg = x763;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x764);
          reg = x764;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x765);
          reg = x765;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x766 = host_outs.at(0);
        auto x767 = host_outs.at(1);
        auto x768 = host_outs.at(2);
        auto x769 = host_outs.at(3);
        auto x770 = host_outs.at(4);
        auto x771 = host_outs.at(5);
        auto x772 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x766);
          reg = x766;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x767);
          reg = x767;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x768);
          reg = x768;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x769);
          reg = x769;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x770);
          reg = x770;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x771);
          reg = x771;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x772);
          reg = x772;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
      auto x773 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x773 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x774 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x774 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x775 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x775 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x776 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x776 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x777 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x777 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x778 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x778 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x779 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x779 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x780 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x780 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x781 = x773 - x780;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x782 = (x781 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x783 = x6 - x782;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x783);
          reg = x783;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x784 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x784 != Fp::invalid());
      if (x784 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x785 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x785 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x786 = x785 - x773;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x787 = x786 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x788 = Fp(x787.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x788);
            reg = x788;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x789 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x789 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x790 = x787 - x789;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x791 = x790 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x792 = Fp(x791.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x792);
            reg = x792;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x793 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x793 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x794 = x791 - x793;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x795 = x794 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x796 = Fp(x795.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x796);
            reg = x796;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x797 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x797 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x798 = x795 - x797;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x799 = x798 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x799);
          reg = x799;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x800 = x6 - x784;
      if (x800 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x801 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x801 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x802 = x773 - x801;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x802 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x803 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x803 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x804 = x803 * x4;
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x805 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x805 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x806 = x804 + x805;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x807 = x774 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x808 = x806 - x807;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x809 = x808 + x775;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x810 = Fp(x809.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x810);
            reg = x810;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x811 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x811 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x812 = x809 - x811;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x813 = x812 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x814 = Fp(x813.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x814);
            reg = x814;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x815 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x815 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x816 = x813 - x815;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x817 = x816 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x818 = Fp(x817.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x818);
            reg = x818;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x819 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x819 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x820 = x817 - x819;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x821 = x820 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x821);
          reg = x821;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x822 = x6 - x805;
        if (x822 != 0) {
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x823 = args[2][138 * steps + ((cycle - 0) & mask)];
          assert(x823 != Fp::invalid());
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x824 = args[2][139 * steps + ((cycle - 0) & mask)];
          assert(x824 != Fp::invalid());
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x825 = args[2][140 * steps + ((cycle - 0) & mask)];
          assert(x825 != Fp::invalid());
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x826 = args[2][141 * steps + ((cycle - 0) & mask)];
          assert(x826 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x827 = x776 - x823;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x827 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x828 = x777 - x824;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x828 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x829 = x778 - x825;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x829 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x830 = x779 - x826;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x830 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":47:40))
      auto x831 = args[2][135 * steps + ((cycle - 0) & mask)];
      assert(x831 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x832 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x832 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x833 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x833 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x834 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x834 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x835 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x835 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x836 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x836 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x837 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x837 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x838 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x838 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x839 = x831 - x838;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x840 = (x839 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x841 = x6 - x840;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x841);
          reg = x841;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x842 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x842 != Fp::invalid());
      if (x842 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x843 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x843 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x844 = x843 - x831;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x845 = x844 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x846 = Fp(x845.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x846);
            reg = x846;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x847 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x847 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x848 = x845 - x847;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x849 = x848 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x850 = Fp(x849.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x850);
            reg = x850;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x851 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x851 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x852 = x849 - x851;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x853 = x852 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x854 = Fp(x853.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x854);
            reg = x854;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x855 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x855 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x856 = x853 - x855;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x857 = x856 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x857);
          reg = x857;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x858 = x6 - x842;
      if (x858 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x859 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x859 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x860 = x831 - x859;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x860 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x861 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x861 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x862 = x861 * x4;
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x863 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x863 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x864 = x862 + x863;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x865 = x832 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x866 = x864 - x865;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x867 = x866 + x833;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x868 = Fp(x867.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x868);
            reg = x868;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x869 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x869 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x870 = x867 - x869;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x871 = x870 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x872 = Fp(x871.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x872);
            reg = x872;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x873 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x873 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x874 = x871 - x873;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x875 = x874 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x876 = Fp(x875.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x876);
            reg = x876;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x877 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x877 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x878 = x875 - x877;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x879 = x878 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x879);
          reg = x879;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x880 = x6 - x863;
        if (x880 != 0) {
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x881 = args[2][145 * steps + ((cycle - 0) & mask)];
          assert(x881 != Fp::invalid());
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x882 = args[2][146 * steps + ((cycle - 0) & mask)];
          assert(x882 != Fp::invalid());
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x883 = args[2][147 * steps + ((cycle - 0) & mask)];
          assert(x883 != Fp::invalid());
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x884 = args[2][148 * steps + ((cycle - 0) & mask)];
          assert(x884 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x885 = x834 - x881;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x885 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x886 = x835 - x882;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x886 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x887 = x836 - x883;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x887 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x888 = x837 - x884;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x888 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":47:40))
      auto x889 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x889 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x890 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x890 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x891 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x891 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x892 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x892 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x893 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x893 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x894 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x894 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x895 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x895 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x896 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x896 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x897 = x889 - x896;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x898 = (x897 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x899 = x6 - x898;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x899);
          reg = x899;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x900 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x900 != Fp::invalid());
      if (x900 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x901 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x901 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x902 = x901 - x889;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x903 = x902 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x904 = Fp(x903.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x904);
            reg = x904;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x905 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x905 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x906 = x903 - x905;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x907 = x906 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x908 = Fp(x907.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x908);
            reg = x908;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x909 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x909 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x910 = x907 - x909;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x911 = x910 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x912 = Fp(x911.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x912);
            reg = x912;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x913 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x913 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x914 = x911 - x913;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x915 = x914 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x915);
          reg = x915;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x916 = x6 - x900;
      if (x916 != 0) {
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x917 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x917 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x918 = x889 - x917;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x918 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x919 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x919 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x920 = x919 * x4;
        // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x921 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x921 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x922 = x920 + x921;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x923 = x890 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x924 = x922 - x923;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x925 = x924 + x891;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x926 = Fp(x925.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x926);
            reg = x926;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x927 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x927 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x928 = x925 - x927;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x929 = x928 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x930 = Fp(x929.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x930);
            reg = x930;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x931 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x931 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x932 = x929 - x931;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x933 = x932 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x934 = Fp(x933.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x934);
            reg = x934;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x935 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x935 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x936 = x933 - x935;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x937 = x936 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x937);
          reg = x937;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x938 = x6 - x921;
        if (x938 != 0) {
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x939 = args[2][152 * steps + ((cycle - 0) & mask)];
          assert(x939 != Fp::invalid());
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x940 = args[2][153 * steps + ((cycle - 0) & mask)];
          assert(x940 != Fp::invalid());
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x941 = args[2][154 * steps + ((cycle - 0) & mask)];
          assert(x941 != Fp::invalid());
          // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x942 = args[2][155 * steps + ((cycle - 0) & mask)];
          assert(x942 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x943 = x892 - x939;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x943 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x944 = x893 - x940;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x944 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x945 = x894 - x941;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x945 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x946 = x895 - x942;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x946 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":47:40))
      auto x947 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x947 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x948 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x948 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x949 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x949 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x950 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x950 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x951 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x951 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x952 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x952 != Fp::invalid());
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x953 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x953 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x954 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x954 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x955 = x947 - x954;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x956 = (x955 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x957 = x6 - x956;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x957);
          reg = x957;
        }
      }
      // loc("Top/Mux/4/Mux/2/ComputeCycle/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x958 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x958 != Fp::invalid());
      if (x958 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x959 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x959 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x960 = x959 - x947;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x961 = x960 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x962 = Fp(x961.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x962);
            reg = x962;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x963 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x963 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x964 = x961 - x963;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x965 = x964 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x966 = Fp(x965.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x966);
            reg = x966;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x967 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x967 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x968 = x965 - x967;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x969 = x968 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x970 = Fp(x969.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x970);
            reg = x970;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x971 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x971 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x972 = x969 - x971;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x973 = x972 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x973);
          reg = x973;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x974 = x6 - x958;
      if (x974 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x975 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x975 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x976 = x947 - x975;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x976 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x977 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x977 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x978 = x977 * x4;
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x979 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x979 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x980 = x978 + x979;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x981 = x948 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x982 = x980 - x981;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x983 = x982 + x949;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x984 = Fp(x983.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x984);
            reg = x984;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x985 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x985 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x986 = x983 - x985;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x987 = x986 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x988 = Fp(x987.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x988);
            reg = x988;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x989 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x989 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x990 = x987 - x989;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x991 = x990 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x992 = Fp(x991.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x992);
            reg = x992;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x993 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x993 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x994 = x991 - x993;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x995 = x994 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x995);
          reg = x995;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x996 = x6 - x979;
        if (x996 != 0) {
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x997 = args[2][5 * steps + ((cycle - 0) & mask)];
          assert(x997 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x998 = args[2][6 * steps + ((cycle - 0) & mask)];
          assert(x998 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x999 = args[2][7 * steps + ((cycle - 0) & mask)];
          assert(x999 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1000 = args[2][8 * steps + ((cycle - 0) & mask)];
          assert(x1000 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1001 = x950 - x997;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1001 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1002 = x951 - x998;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1002 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1003 = x952 - x999;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1003 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1004 = x953 - x1000;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1004 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x1005 = args[2][97 * steps + ((cycle - 0) & mask)];
    assert(x1005 != Fp::invalid());
    if (x1005 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1006 = host_outs.at(0);
        auto x1007 = host_outs.at(1);
        auto x1008 = host_outs.at(2);
        auto x1009 = host_outs.at(3);
        auto x1010 = host_outs.at(4);
        auto x1011 = host_outs.at(5);
        auto x1012 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1006);
          reg = x1006;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1007);
          reg = x1007;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1008);
          reg = x1008;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1009);
          reg = x1009;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1010);
          reg = x1010;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1011);
          reg = x1011;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1012);
          reg = x1012;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1013 = host_outs.at(0);
        auto x1014 = host_outs.at(1);
        auto x1015 = host_outs.at(2);
        auto x1016 = host_outs.at(3);
        auto x1017 = host_outs.at(4);
        auto x1018 = host_outs.at(5);
        auto x1019 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1013);
          reg = x1013;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1014);
          reg = x1014;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1015);
          reg = x1015;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1016);
          reg = x1016;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1017);
          reg = x1017;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1018);
          reg = x1018;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1019);
          reg = x1019;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1020 = host_outs.at(0);
        auto x1021 = host_outs.at(1);
        auto x1022 = host_outs.at(2);
        auto x1023 = host_outs.at(3);
        auto x1024 = host_outs.at(4);
        auto x1025 = host_outs.at(5);
        auto x1026 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1020);
          reg = x1020;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1021);
          reg = x1021;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1022);
          reg = x1022;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1023);
          reg = x1023;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1024);
          reg = x1024;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1025);
          reg = x1025;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1026);
          reg = x1026;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1027 = host_outs.at(0);
        auto x1028 = host_outs.at(1);
        auto x1029 = host_outs.at(2);
        auto x1030 = host_outs.at(3);
        auto x1031 = host_outs.at(4);
        auto x1032 = host_outs.at(5);
        auto x1033 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1027);
          reg = x1027;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1028);
          reg = x1028;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1029);
          reg = x1029;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1030);
          reg = x1030;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1031);
          reg = x1031;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1032);
          reg = x1032;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1033);
          reg = x1033;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1034 = host_outs.at(0);
        auto x1035 = host_outs.at(1);
        auto x1036 = host_outs.at(2);
        auto x1037 = host_outs.at(3);
        auto x1038 = host_outs.at(4);
        auto x1039 = host_outs.at(5);
        auto x1040 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1034);
          reg = x1034;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1035);
          reg = x1035;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1036);
          reg = x1036;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1037);
          reg = x1037;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1038);
          reg = x1038;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1039);
          reg = x1039;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1040);
          reg = x1040;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1041 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1041 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1042 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1042 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1043 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1043 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1044 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1044 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1045 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1045 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1046 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1046 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1047 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1047 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1048 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x1048 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1049 = x1041 - x1048;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1050 = (x1049 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1051 = x6 - x1050;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1051);
          reg = x1051;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1052 = args[2][170 * steps + ((cycle - 0) & mask)];
      assert(x1052 != Fp::invalid());
      if (x1052 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1053 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x1053 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1054 = x1053 - x1041;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1055 = x1054 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1056 = Fp(x1055.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1056);
            reg = x1056;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1057 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1057 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1058 = x1055 - x1057;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1059 = x1058 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1060 = Fp(x1059.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1060);
            reg = x1060;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1061 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1061 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1062 = x1059 - x1061;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1063 = x1062 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1064 = Fp(x1063.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1064);
            reg = x1064;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1065 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1065 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1066 = x1063 - x1065;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1067 = x1066 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1067);
          reg = x1067;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1068 = x6 - x1052;
      if (x1068 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1069 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x1069 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1070 = x1041 - x1069;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1070 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1071 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1071 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1072 = x1071 * x4;
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1073 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x1073 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1074 = x1072 + x1073;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1075 = x1042 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1076 = x1074 - x1075;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1077 = x1076 + x1043;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1078 = Fp(x1077.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1078);
            reg = x1078;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1079 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1079 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1080 = x1077 - x1079;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1081 = x1080 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1082 = Fp(x1081.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1082);
            reg = x1082;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1083 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1083 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1084 = x1081 - x1083;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1085 = x1084 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1086 = Fp(x1085.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1086);
            reg = x1086;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1087 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1087 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1088 = x1085 - x1087;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1089 = x1088 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1089);
          reg = x1089;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1090 = x6 - x1073;
        if (x1090 != 0) {
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1091 = args[2][145 * steps + ((cycle - 0) & mask)];
          assert(x1091 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1092 = args[2][146 * steps + ((cycle - 0) & mask)];
          assert(x1092 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1093 = args[2][147 * steps + ((cycle - 0) & mask)];
          assert(x1093 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1094 = args[2][148 * steps + ((cycle - 0) & mask)];
          assert(x1094 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1095 = x1044 - x1091;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1095 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1096 = x1045 - x1092;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1096 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1097 = x1046 - x1093;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1097 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1098 = x1047 - x1094;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1098 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1099 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x1099 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1100 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x1100 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1101 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x1101 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1102 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x1102 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1103 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x1103 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1104 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x1104 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1105 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x1105 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1106 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x1106 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1107 = x1099 - x1106;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1108 = (x1107 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1109 = x6 - x1108;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1109);
          reg = x1109;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1110 = args[2][171 * steps + ((cycle - 0) & mask)];
      assert(x1110 != Fp::invalid());
      if (x1110 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1111 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x1111 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1112 = x1111 - x1099;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1113 = x1112 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1114 = Fp(x1113.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1114);
            reg = x1114;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1115 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1115 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1116 = x1113 - x1115;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1117 = x1116 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1118 = Fp(x1117.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1118);
            reg = x1118;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1119 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1119 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1120 = x1117 - x1119;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1121 = x1120 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1122 = Fp(x1121.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1122);
            reg = x1122;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1123 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1123 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1124 = x1121 - x1123;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1125 = x1124 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1125);
          reg = x1125;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1126 = x6 - x1110;
      if (x1126 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1127 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x1127 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1128 = x1099 - x1127;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1128 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1129 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1129 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1130 = x1129 * x4;
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1131 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x1131 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1132 = x1130 + x1131;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1133 = x1100 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1134 = x1132 - x1133;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1135 = x1134 + x1101;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1136 = Fp(x1135.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1136);
            reg = x1136;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1137 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1137 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1138 = x1135 - x1137;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1139 = x1138 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1140 = Fp(x1139.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1140);
            reg = x1140;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1141 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1141 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1142 = x1139 - x1141;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1143 = x1142 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1144 = Fp(x1143.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1144);
            reg = x1144;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1145 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1145 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1146 = x1143 - x1145;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1147 = x1146 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1147);
          reg = x1147;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1148 = x6 - x1131;
        if (x1148 != 0) {
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1149 = args[2][152 * steps + ((cycle - 0) & mask)];
          assert(x1149 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1150 = args[2][153 * steps + ((cycle - 0) & mask)];
          assert(x1150 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1151 = args[2][154 * steps + ((cycle - 0) & mask)];
          assert(x1151 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1152 = args[2][155 * steps + ((cycle - 0) & mask)];
          assert(x1152 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1153 = x1102 - x1149;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1153 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1154 = x1103 - x1150;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1154 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1155 = x1104 - x1151;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1155 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1156 = x1105 - x1152;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1156 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1157 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x1157 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1158 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x1158 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1159 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x1159 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1160 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x1160 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1161 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x1161 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1162 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x1162 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1163 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x1163 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1164 = args[2][156 * steps + ((cycle - 0) & mask)];
        assert(x1164 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1165 = x1157 - x1164;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1166 = (x1165 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1167 = x6 - x1166;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1167);
          reg = x1167;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1168 = args[2][172 * steps + ((cycle - 0) & mask)];
      assert(x1168 != Fp::invalid());
      if (x1168 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1169 = args[2][156 * steps + ((cycle - 0) & mask)];
        assert(x1169 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1170 = x1169 - x1157;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1171 = x1170 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1172 = Fp(x1171.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1172);
            reg = x1172;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1173 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1173 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1174 = x1171 - x1173;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1175 = x1174 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1176 = Fp(x1175.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1176);
            reg = x1176;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1177 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1177 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1178 = x1175 - x1177;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1179 = x1178 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1180 = Fp(x1179.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1180);
            reg = x1180;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1181 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1181 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1182 = x1179 - x1181;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1183 = x1182 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1183);
          reg = x1183;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1184 = x6 - x1168;
      if (x1184 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1185 = args[2][156 * steps + ((cycle - 0) & mask)];
        assert(x1185 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1186 = x1157 - x1185;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1186 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1187 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x1187 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1188 = x1187 * x4;
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1189 = args[2][158 * steps + ((cycle - 0) & mask)];
        assert(x1189 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1190 = x1188 + x1189;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1191 = x1158 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1192 = x1190 - x1191;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1193 = x1192 + x1159;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1194 = Fp(x1193.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1194);
            reg = x1194;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1195 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1195 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1196 = x1193 - x1195;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1197 = x1196 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1198 = Fp(x1197.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1198);
            reg = x1198;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1199 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1199 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1200 = x1197 - x1199;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1201 = x1200 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1202 = Fp(x1201.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1202);
            reg = x1202;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1203 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1203 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1204 = x1201 - x1203;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1205 = x1204 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1205);
          reg = x1205;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1206 = x6 - x1189;
        if (x1206 != 0) {
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1207 = args[2][159 * steps + ((cycle - 0) & mask)];
          assert(x1207 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1208 = args[2][160 * steps + ((cycle - 0) & mask)];
          assert(x1208 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1209 = args[2][161 * steps + ((cycle - 0) & mask)];
          assert(x1209 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1210 = args[2][162 * steps + ((cycle - 0) & mask)];
          assert(x1210 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1211 = x1160 - x1207;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1211 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1212 = x1161 - x1208;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1212 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1213 = x1162 - x1209;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1213 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1214 = x1163 - x1210;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1214 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1215 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x1215 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1216 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x1216 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1217 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x1217 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1218 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x1218 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1219 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x1219 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1220 = args[2][161 * steps + ((cycle - 0) & mask)];
      assert(x1220 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1221 = args[2][162 * steps + ((cycle - 0) & mask)];
      assert(x1221 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1222 = args[2][163 * steps + ((cycle - 0) & mask)];
        assert(x1222 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1223 = x1215 - x1222;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1224 = (x1223 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1225 = x6 - x1224;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][173 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1225);
          reg = x1225;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1226 = args[2][173 * steps + ((cycle - 0) & mask)];
      assert(x1226 != Fp::invalid());
      if (x1226 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1227 = args[2][163 * steps + ((cycle - 0) & mask)];
        assert(x1227 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1228 = x1227 - x1215;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1229 = x1228 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1230 = Fp(x1229.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1230);
            reg = x1230;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1231 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1231 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1232 = x1229 - x1231;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1233 = x1232 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1234 = Fp(x1233.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1234);
            reg = x1234;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1235 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1235 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1236 = x1233 - x1235;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1237 = x1236 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1238 = Fp(x1237.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1238);
            reg = x1238;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1239 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1239 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1240 = x1237 - x1239;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1241 = x1240 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1241);
          reg = x1241;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1242 = x6 - x1226;
      if (x1242 != 0) {
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1243 = args[2][163 * steps + ((cycle - 0) & mask)];
        assert(x1243 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1244 = x1215 - x1243;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1244 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1245 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x1245 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1246 = x1245 * x4;
        // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1247 = args[2][165 * steps + ((cycle - 0) & mask)];
        assert(x1247 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1248 = x1246 + x1247;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1249 = x1216 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1250 = x1248 - x1249;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1251 = x1250 + x1217;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1252 = Fp(x1251.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1252);
            reg = x1252;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1253 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1253 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1254 = x1251 - x1253;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1255 = x1254 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1256 = Fp(x1255.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1256);
            reg = x1256;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1257 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1257 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1258 = x1255 - x1257;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1259 = x1258 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1260 = Fp(x1259.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1260);
            reg = x1260;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1261 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1261 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1262 = x1259 - x1261;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1263 = x1262 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1263);
          reg = x1263;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1264 = x6 - x1247;
        if (x1264 != 0) {
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1265 = args[2][166 * steps + ((cycle - 0) & mask)];
          assert(x1265 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1266 = args[2][167 * steps + ((cycle - 0) & mask)];
          assert(x1266 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1267 = args[2][168 * steps + ((cycle - 0) & mask)];
          assert(x1267 != Fp::invalid());
          // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1268 = args[2][169 * steps + ((cycle - 0) & mask)];
          assert(x1268 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1269 = x1218 - x1265;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1269 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1270 = x1219 - x1266;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1270 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1271 = x1220 - x1267;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1271 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1272 = x1221 - x1268;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1272 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1273 = args[2][163 * steps + ((cycle - 0) & mask)];
      assert(x1273 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1274 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x1274 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1275 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x1275 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1276 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x1276 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1277 = args[2][167 * steps + ((cycle - 0) & mask)];
      assert(x1277 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1278 = args[2][168 * steps + ((cycle - 0) & mask)];
      assert(x1278 != Fp::invalid());
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1279 = args[2][169 * steps + ((cycle - 0) & mask)];
      assert(x1279 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1280 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1280 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1281 = x1273 - x1280;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1282 = (x1281 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1283 = x6 - x1282;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][174 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1283);
          reg = x1283;
        }
      }
      // loc("Top/Mux/4/Mux/3/RamBody/PlonkBody/RamPlonkVerifier4/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1284 = args[2][174 * steps + ((cycle - 0) & mask)];
      assert(x1284 != Fp::invalid());
      if (x1284 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1285 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1285 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1286 = x1285 - x1273;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1287 = x1286 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1288 = Fp(x1287.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1288);
            reg = x1288;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1289 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x1289 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1290 = x1287 - x1289;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1291 = x1290 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1292 = Fp(x1291.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1292);
            reg = x1292;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1293 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x1293 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1294 = x1291 - x1293;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1295 = x1294 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1296 = Fp(x1295.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1296);
            reg = x1296;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1297 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x1297 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1298 = x1295 - x1297;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1299 = x1298 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1299);
          reg = x1299;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1300 = x6 - x1284;
      if (x1300 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1301 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1301 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1302 = x1273 - x1301;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1302 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1303 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x1303 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1304 = x1303 * x4;
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1305 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1305 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1306 = x1304 + x1305;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1307 = x1274 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1308 = x1306 - x1307;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1309 = x1308 + x1275;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1310 = Fp(x1309.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1310);
            reg = x1310;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1311 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x1311 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1312 = x1309 - x1311;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1313 = x1312 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1314 = Fp(x1313.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1314);
            reg = x1314;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1315 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x1315 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1316 = x1313 - x1315;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1317 = x1316 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1318 = Fp(x1317.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1318);
            reg = x1318;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1319 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x1319 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1320 = x1317 - x1319;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1321 = x1320 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1321);
          reg = x1321;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1322 = x6 - x1305;
        if (x1322 != 0) {
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1323 = args[2][5 * steps + ((cycle - 0) & mask)];
          assert(x1323 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1324 = args[2][6 * steps + ((cycle - 0) & mask)];
          assert(x1324 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1325 = args[2][7 * steps + ((cycle - 0) & mask)];
          assert(x1325 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1326 = args[2][8 * steps + ((cycle - 0) & mask)];
          assert(x1326 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1327 = x1276 - x1323;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1327 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1328 = x1277 - x1324;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1328 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1329 = x1278 - x1325;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1329 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1330 = x1279 - x1326;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1330 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x1331 = args[2][98 * steps + ((cycle - 0) & mask)];
    assert(x1331 != Fp::invalid());
    if (x1331 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1332 = host_outs.at(0);
        auto x1333 = host_outs.at(1);
        auto x1334 = host_outs.at(2);
        auto x1335 = host_outs.at(3);
        auto x1336 = host_outs.at(4);
        auto x1337 = host_outs.at(5);
        auto x1338 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1332);
          reg = x1332;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1333);
          reg = x1333;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1334);
          reg = x1334;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1335);
          reg = x1335;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1336);
          reg = x1336;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1337);
          reg = x1337;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1338);
          reg = x1338;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1339 = host_outs.at(0);
        auto x1340 = host_outs.at(1);
        auto x1341 = host_outs.at(2);
        auto x1342 = host_outs.at(3);
        auto x1343 = host_outs.at(4);
        auto x1344 = host_outs.at(5);
        auto x1345 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1339);
          reg = x1339;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1340);
          reg = x1340;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1341);
          reg = x1341;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1342);
          reg = x1342;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1343);
          reg = x1343;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1344);
          reg = x1344;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1345);
          reg = x1345;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1346 = host_outs.at(0);
        auto x1347 = host_outs.at(1);
        auto x1348 = host_outs.at(2);
        auto x1349 = host_outs.at(3);
        auto x1350 = host_outs.at(4);
        auto x1351 = host_outs.at(5);
        auto x1352 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1346);
          reg = x1346;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1347);
          reg = x1347;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1348);
          reg = x1348;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1349);
          reg = x1349;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][160 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1350);
          reg = x1350;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][161 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1351);
          reg = x1351;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][162 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1352);
          reg = x1352;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1353 = host_outs.at(0);
        auto x1354 = host_outs.at(1);
        auto x1355 = host_outs.at(2);
        auto x1356 = host_outs.at(3);
        auto x1357 = host_outs.at(4);
        auto x1358 = host_outs.at(5);
        auto x1359 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][163 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1353);
          reg = x1353;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][164 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1354);
          reg = x1354;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][165 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1355);
          reg = x1355;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][166 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1356);
          reg = x1356;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][167 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1357);
          reg = x1357;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][168 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1358);
          reg = x1358;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][169 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1359);
          reg = x1359;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1360 = host_outs.at(0);
        auto x1361 = host_outs.at(1);
        auto x1362 = host_outs.at(2);
        auto x1363 = host_outs.at(3);
        auto x1364 = host_outs.at(4);
        auto x1365 = host_outs.at(5);
        auto x1366 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1360);
          reg = x1360;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1361);
          reg = x1361;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1362);
          reg = x1362;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1363);
          reg = x1363;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1364);
          reg = x1364;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1365);
          reg = x1365;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1366);
          reg = x1366;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1367 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1367 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1368 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1368 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1369 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1369 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1370 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1370 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1371 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1371 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1372 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1372 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1373 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1373 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1374 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x1374 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1375 = x1367 - x1374;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1376 = (x1375 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1377 = x6 - x1376;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][170 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1377);
          reg = x1377;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1378 = args[2][170 * steps + ((cycle - 0) & mask)];
      assert(x1378 != Fp::invalid());
      if (x1378 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1379 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x1379 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1380 = x1379 - x1367;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1381 = x1380 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1382 = Fp(x1381.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1382);
            reg = x1382;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1383 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1383 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1384 = x1381 - x1383;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1385 = x1384 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1386 = Fp(x1385.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1386);
            reg = x1386;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1387 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1387 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1388 = x1385 - x1387;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1389 = x1388 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1390 = Fp(x1389.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1390);
            reg = x1390;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1391 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1391 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1392 = x1389 - x1391;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1393 = x1392 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1393);
          reg = x1393;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1394 = x6 - x1378;
      if (x1394 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1395 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x1395 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1396 = x1367 - x1395;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1396 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1397 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1397 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1398 = x1397 * x4;
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1399 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x1399 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1400 = x1398 + x1399;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1401 = x1368 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1402 = x1400 - x1401;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1403 = x1402 + x1369;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1404 = Fp(x1403.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1404);
            reg = x1404;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1405 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1405 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1406 = x1403 - x1405;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1407 = x1406 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1408 = Fp(x1407.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1408);
            reg = x1408;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1409 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1409 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1410 = x1407 - x1409;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1411 = x1410 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1412 = Fp(x1411.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1412);
            reg = x1412;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1413 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1413 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1414 = x1411 - x1413;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1415 = x1414 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1415);
          reg = x1415;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1416 = x6 - x1399;
        if (x1416 != 0) {
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1417 = args[2][145 * steps + ((cycle - 0) & mask)];
          assert(x1417 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1418 = args[2][146 * steps + ((cycle - 0) & mask)];
          assert(x1418 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1419 = args[2][147 * steps + ((cycle - 0) & mask)];
          assert(x1419 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1420 = args[2][148 * steps + ((cycle - 0) & mask)];
          assert(x1420 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1421 = x1370 - x1417;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1421 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1422 = x1371 - x1418;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1422 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1423 = x1372 - x1419;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1423 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1424 = x1373 - x1420;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1424 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1425 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x1425 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1426 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x1426 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1427 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x1427 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1428 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x1428 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1429 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x1429 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1430 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x1430 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1431 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x1431 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1432 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x1432 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1433 = x1425 - x1432;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1434 = (x1433 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1435 = x6 - x1434;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][171 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1435);
          reg = x1435;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1436 = args[2][171 * steps + ((cycle - 0) & mask)];
      assert(x1436 != Fp::invalid());
      if (x1436 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1437 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x1437 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1438 = x1437 - x1425;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1439 = x1438 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1440 = Fp(x1439.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1440);
            reg = x1440;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1441 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1441 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1442 = x1439 - x1441;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1443 = x1442 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1444 = Fp(x1443.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1444);
            reg = x1444;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1445 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1445 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1446 = x1443 - x1445;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1447 = x1446 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1448 = Fp(x1447.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1448);
            reg = x1448;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1449 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1449 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1450 = x1447 - x1449;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1451 = x1450 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1451);
          reg = x1451;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1452 = x6 - x1436;
      if (x1452 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1453 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x1453 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1454 = x1425 - x1453;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1454 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1455 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1455 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1456 = x1455 * x4;
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1457 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x1457 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1458 = x1456 + x1457;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1459 = x1426 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1460 = x1458 - x1459;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1461 = x1460 + x1427;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1462 = Fp(x1461.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1462);
            reg = x1462;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1463 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1463 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1464 = x1461 - x1463;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1465 = x1464 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1466 = Fp(x1465.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1466);
            reg = x1466;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1467 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1467 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1468 = x1465 - x1467;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1469 = x1468 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1470 = Fp(x1469.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1470);
            reg = x1470;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1471 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1471 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1472 = x1469 - x1471;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1473 = x1472 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1473);
          reg = x1473;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1474 = x6 - x1457;
        if (x1474 != 0) {
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1475 = args[2][152 * steps + ((cycle - 0) & mask)];
          assert(x1475 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1476 = args[2][153 * steps + ((cycle - 0) & mask)];
          assert(x1476 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1477 = args[2][154 * steps + ((cycle - 0) & mask)];
          assert(x1477 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1478 = args[2][155 * steps + ((cycle - 0) & mask)];
          assert(x1478 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1479 = x1428 - x1475;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1479 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1480 = x1429 - x1476;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1480 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1481 = x1430 - x1477;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1481 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1482 = x1431 - x1478;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1482 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1483 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x1483 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1484 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x1484 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1485 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x1485 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1486 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x1486 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1487 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x1487 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1488 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x1488 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1489 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x1489 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1490 = args[2][156 * steps + ((cycle - 0) & mask)];
        assert(x1490 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1491 = x1483 - x1490;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1492 = (x1491 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1493 = x6 - x1492;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][172 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1493);
          reg = x1493;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1494 = args[2][172 * steps + ((cycle - 0) & mask)];
      assert(x1494 != Fp::invalid());
      if (x1494 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1495 = args[2][156 * steps + ((cycle - 0) & mask)];
        assert(x1495 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1496 = x1495 - x1483;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1497 = x1496 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1498 = Fp(x1497.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1498);
            reg = x1498;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1499 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1499 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1500 = x1497 - x1499;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1501 = x1500 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1502 = Fp(x1501.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1502);
            reg = x1502;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1503 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1503 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1504 = x1501 - x1503;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1505 = x1504 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1506 = Fp(x1505.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1506);
            reg = x1506;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1507 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1507 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1508 = x1505 - x1507;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1509 = x1508 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1509);
          reg = x1509;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1510 = x6 - x1494;
      if (x1510 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1511 = args[2][156 * steps + ((cycle - 0) & mask)];
        assert(x1511 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1512 = x1483 - x1511;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1512 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1513 = args[2][157 * steps + ((cycle - 0) & mask)];
        assert(x1513 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1514 = x1513 * x4;
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1515 = args[2][158 * steps + ((cycle - 0) & mask)];
        assert(x1515 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1516 = x1514 + x1515;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1517 = x1484 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1518 = x1516 - x1517;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1519 = x1518 + x1485;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1520 = Fp(x1519.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1520);
            reg = x1520;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1521 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1521 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1522 = x1519 - x1521;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1523 = x1522 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1524 = Fp(x1523.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1524);
            reg = x1524;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1525 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1525 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1526 = x1523 - x1525;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1527 = x1526 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1528 = Fp(x1527.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1528);
            reg = x1528;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1529 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1529 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1530 = x1527 - x1529;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1531 = x1530 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1531);
          reg = x1531;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1532 = x6 - x1515;
        if (x1532 != 0) {
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1533 = args[2][159 * steps + ((cycle - 0) & mask)];
          assert(x1533 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1534 = args[2][160 * steps + ((cycle - 0) & mask)];
          assert(x1534 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1535 = args[2][161 * steps + ((cycle - 0) & mask)];
          assert(x1535 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1536 = args[2][162 * steps + ((cycle - 0) & mask)];
          assert(x1536 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1537 = x1486 - x1533;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1537 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1538 = x1487 - x1534;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1538 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1539 = x1488 - x1535;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1539 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1540 = x1489 - x1536;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1540 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1541 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x1541 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1542 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x1542 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1543 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x1543 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1544 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x1544 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1545 = args[2][160 * steps + ((cycle - 0) & mask)];
      assert(x1545 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1546 = args[2][161 * steps + ((cycle - 0) & mask)];
      assert(x1546 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement7/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1547 = args[2][162 * steps + ((cycle - 0) & mask)];
      assert(x1547 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1548 = args[2][163 * steps + ((cycle - 0) & mask)];
        assert(x1548 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1549 = x1541 - x1548;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1550 = (x1549 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1551 = x6 - x1550;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][173 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1551);
          reg = x1551;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1552 = args[2][173 * steps + ((cycle - 0) & mask)];
      assert(x1552 != Fp::invalid());
      if (x1552 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1553 = args[2][163 * steps + ((cycle - 0) & mask)];
        assert(x1553 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1554 = x1553 - x1541;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1555 = x1554 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1556 = Fp(x1555.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1556);
            reg = x1556;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1557 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1557 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1558 = x1555 - x1557;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1559 = x1558 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1560 = Fp(x1559.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1560);
            reg = x1560;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1561 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1561 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1562 = x1559 - x1561;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1563 = x1562 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1564 = Fp(x1563.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1564);
            reg = x1564;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1565 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1565 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1566 = x1563 - x1565;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1567 = x1566 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1567);
          reg = x1567;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1568 = x6 - x1552;
      if (x1568 != 0) {
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1569 = args[2][163 * steps + ((cycle - 0) & mask)];
        assert(x1569 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1570 = x1541 - x1569;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1570 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1571 = args[2][164 * steps + ((cycle - 0) & mask)];
        assert(x1571 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1572 = x1571 * x4;
        // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1573 = args[2][165 * steps + ((cycle - 0) & mask)];
        assert(x1573 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1574 = x1572 + x1573;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1575 = x1542 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1576 = x1574 - x1575;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1577 = x1576 + x1543;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1578 = Fp(x1577.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1578);
            reg = x1578;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1579 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1579 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1580 = x1577 - x1579;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1581 = x1580 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1582 = Fp(x1581.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1582);
            reg = x1582;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1583 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1583 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1584 = x1581 - x1583;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1585 = x1584 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1586 = Fp(x1585.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1586);
            reg = x1586;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1587 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1587 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1588 = x1585 - x1587;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1589 = x1588 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1589);
          reg = x1589;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1590 = x6 - x1573;
        if (x1590 != 0) {
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1591 = args[2][166 * steps + ((cycle - 0) & mask)];
          assert(x1591 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1592 = args[2][167 * steps + ((cycle - 0) & mask)];
          assert(x1592 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1593 = args[2][168 * steps + ((cycle - 0) & mask)];
          assert(x1593 != Fp::invalid());
          // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1594 = args[2][169 * steps + ((cycle - 0) & mask)];
          assert(x1594 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1595 = x1544 - x1591;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1595 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1596 = x1545 - x1592;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1596 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1597 = x1546 - x1593;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1597 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1598 = x1547 - x1594;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1598 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1599 = args[2][163 * steps + ((cycle - 0) & mask)];
      assert(x1599 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1600 = args[2][164 * steps + ((cycle - 0) & mask)];
      assert(x1600 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1601 = args[2][165 * steps + ((cycle - 0) & mask)];
      assert(x1601 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1602 = args[2][166 * steps + ((cycle - 0) & mask)];
      assert(x1602 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1603 = args[2][167 * steps + ((cycle - 0) & mask)];
      assert(x1603 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1604 = args[2][168 * steps + ((cycle - 0) & mask)];
      assert(x1604 != Fp::invalid());
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkElement8/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1605 = args[2][169 * steps + ((cycle - 0) & mask)];
      assert(x1605 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1606 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1606 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1607 = x1599 - x1606;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1608 = (x1607 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1609 = x6 - x1608;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][174 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1609);
          reg = x1609;
        }
      }
      // loc("Top/Mux/4/Mux/4/RamBody/PlonkBody/RamPlonkVerifier4/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1610 = args[2][174 * steps + ((cycle - 0) & mask)];
      assert(x1610 != Fp::invalid());
      if (x1610 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1611 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1611 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1612 = x1611 - x1599;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1613 = x1612 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1614 = Fp(x1613.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1614);
            reg = x1614;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1615 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x1615 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1616 = x1613 - x1615;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1617 = x1616 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1618 = Fp(x1617.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1618);
            reg = x1618;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1619 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x1619 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1620 = x1617 - x1619;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1621 = x1620 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1622 = Fp(x1621.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1622);
            reg = x1622;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1623 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x1623 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1624 = x1621 - x1623;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1625 = x1624 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1625);
          reg = x1625;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1626 = x6 - x1610;
      if (x1626 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1627 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1627 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1628 = x1599 - x1627;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1628 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1629 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x1629 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1630 = x1629 * x4;
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1631 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1631 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1632 = x1630 + x1631;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1633 = x1600 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1634 = x1632 - x1633;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1635 = x1634 + x1601;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1636 = Fp(x1635.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][25 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1636);
            reg = x1636;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1637 = args[2][25 * steps + ((cycle - 0) & mask)];
        assert(x1637 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1638 = x1635 - x1637;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1639 = x1638 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1640 = Fp(x1639.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][26 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1640);
            reg = x1640;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1641 = args[2][26 * steps + ((cycle - 0) & mask)];
        assert(x1641 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1642 = x1639 - x1641;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1643 = x1642 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1644 = Fp(x1643.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][27 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1644);
            reg = x1644;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1645 = args[2][27 * steps + ((cycle - 0) & mask)];
        assert(x1645 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1646 = x1643 - x1645;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1647 = x1646 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][78 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1647);
          reg = x1647;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1648 = x6 - x1631;
        if (x1648 != 0) {
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1649 = args[2][5 * steps + ((cycle - 0) & mask)];
          assert(x1649 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1650 = args[2][6 * steps + ((cycle - 0) & mask)];
          assert(x1650 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1651 = args[2][7 * steps + ((cycle - 0) & mask)];
          assert(x1651 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1652 = args[2][8 * steps + ((cycle - 0) & mask)];
          assert(x1652 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1653 = x1602 - x1649;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1653 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1654 = x1603 - x1650;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1654 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1655 = x1604 - x1651;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1655 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1656 = x1605 - x1652;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1656 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x1657 = args[2][99 * steps + ((cycle - 0) & mask)];
    assert(x1657 != Fp::invalid());
    if (x1657 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1658 = host_outs.at(0);
        auto x1659 = host_outs.at(1);
        auto x1660 = host_outs.at(2);
        auto x1661 = host_outs.at(3);
        auto x1662 = host_outs.at(4);
        auto x1663 = host_outs.at(5);
        auto x1664 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][135 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1658);
          reg = x1658;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1659);
          reg = x1659;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1660);
          reg = x1660;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1661);
          reg = x1661;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1662);
          reg = x1662;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1663);
          reg = x1663;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1664);
          reg = x1664;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1665 = host_outs.at(0);
        auto x1666 = host_outs.at(1);
        auto x1667 = host_outs.at(2);
        auto x1668 = host_outs.at(3);
        auto x1669 = host_outs.at(4);
        auto x1670 = host_outs.at(5);
        auto x1671 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1665);
          reg = x1665;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1666);
          reg = x1666;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1667);
          reg = x1667;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1668);
          reg = x1668;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1669);
          reg = x1669;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1670);
          reg = x1670;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1671);
          reg = x1671;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1672 = host_outs.at(0);
        auto x1673 = host_outs.at(1);
        auto x1674 = host_outs.at(2);
        auto x1675 = host_outs.at(3);
        auto x1676 = host_outs.at(4);
        auto x1677 = host_outs.at(5);
        auto x1678 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1672);
          reg = x1672;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1673);
          reg = x1673;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1674);
          reg = x1674;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1675);
          reg = x1675;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1676);
          reg = x1676;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1677);
          reg = x1677;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1678);
          reg = x1678;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1679 = host_outs.at(0);
        auto x1680 = host_outs.at(1);
        auto x1681 = host_outs.at(2);
        auto x1682 = host_outs.at(3);
        auto x1683 = host_outs.at(4);
        auto x1684 = host_outs.at(5);
        auto x1685 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1679);
          reg = x1679;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1680);
          reg = x1680;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1681);
          reg = x1681;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1682);
          reg = x1682;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1683);
          reg = x1683;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1684);
          reg = x1684;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1685);
          reg = x1685;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1686 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1686 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1687 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1687 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1688 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1688 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1689 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1689 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1690 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1690 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1691 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1691 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1692 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1692 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1693 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x1693 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1694 = x1686 - x1693;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1695 = (x1694 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1696 = x6 - x1695;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1696);
          reg = x1696;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1697 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x1697 != Fp::invalid());
      if (x1697 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1698 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x1698 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1699 = x1698 - x1686;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1700 = x1699 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1701 = Fp(x1700.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1701);
            reg = x1701;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1702 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1702 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1703 = x1700 - x1702;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1704 = x1703 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1705 = Fp(x1704.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1705);
            reg = x1705;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1706 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1706 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1707 = x1704 - x1706;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1708 = x1707 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1709 = Fp(x1708.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1709);
            reg = x1709;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1710 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1710 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1711 = x1708 - x1710;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1712 = x1711 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1712);
          reg = x1712;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1713 = x6 - x1697;
      if (x1713 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1714 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x1714 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1715 = x1686 - x1714;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1715 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1716 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1716 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1717 = x1716 * x4;
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1718 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x1718 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1719 = x1717 + x1718;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1720 = x1687 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1721 = x1719 - x1720;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1722 = x1721 + x1688;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1723 = Fp(x1722.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1723);
            reg = x1723;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1724 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1724 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1725 = x1722 - x1724;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1726 = x1725 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1727 = Fp(x1726.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1727);
            reg = x1727;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1728 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1728 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1729 = x1726 - x1728;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1730 = x1729 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1731 = Fp(x1730.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1731);
            reg = x1731;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1732 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1732 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1733 = x1730 - x1732;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1734 = x1733 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1734);
          reg = x1734;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1735 = x6 - x1718;
        if (x1735 != 0) {
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1736 = args[2][138 * steps + ((cycle - 0) & mask)];
          assert(x1736 != Fp::invalid());
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1737 = args[2][139 * steps + ((cycle - 0) & mask)];
          assert(x1737 != Fp::invalid());
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1738 = args[2][140 * steps + ((cycle - 0) & mask)];
          assert(x1738 != Fp::invalid());
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1739 = args[2][141 * steps + ((cycle - 0) & mask)];
          assert(x1739 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1740 = x1689 - x1736;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1740 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1741 = x1690 - x1737;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1741 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1742 = x1691 - x1738;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1742 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1743 = x1692 - x1739;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1743 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1744 = args[2][135 * steps + ((cycle - 0) & mask)];
      assert(x1744 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1745 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x1745 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1746 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x1746 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1747 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x1747 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1748 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x1748 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1749 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x1749 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1750 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x1750 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1751 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x1751 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1752 = x1744 - x1751;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1753 = (x1752 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1754 = x6 - x1753;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1754);
          reg = x1754;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1755 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x1755 != Fp::invalid());
      if (x1755 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1756 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x1756 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1757 = x1756 - x1744;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1758 = x1757 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1759 = Fp(x1758.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1759);
            reg = x1759;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1760 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1760 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1761 = x1758 - x1760;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1762 = x1761 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1763 = Fp(x1762.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1763);
            reg = x1763;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1764 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1764 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1765 = x1762 - x1764;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1766 = x1765 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1767 = Fp(x1766.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1767);
            reg = x1767;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1768 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1768 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1769 = x1766 - x1768;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1770 = x1769 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1770);
          reg = x1770;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1771 = x6 - x1755;
      if (x1771 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1772 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x1772 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1773 = x1744 - x1772;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1773 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1774 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x1774 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1775 = x1774 * x4;
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1776 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x1776 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1777 = x1775 + x1776;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1778 = x1745 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1779 = x1777 - x1778;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1780 = x1779 + x1746;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1781 = Fp(x1780.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1781);
            reg = x1781;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1782 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x1782 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1783 = x1780 - x1782;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1784 = x1783 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1785 = Fp(x1784.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1785);
            reg = x1785;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1786 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x1786 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1787 = x1784 - x1786;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1788 = x1787 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1789 = Fp(x1788.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1789);
            reg = x1789;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1790 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x1790 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1791 = x1788 - x1790;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1792 = x1791 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1792);
          reg = x1792;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1793 = x6 - x1776;
        if (x1793 != 0) {
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1794 = args[2][145 * steps + ((cycle - 0) & mask)];
          assert(x1794 != Fp::invalid());
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1795 = args[2][146 * steps + ((cycle - 0) & mask)];
          assert(x1795 != Fp::invalid());
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1796 = args[2][147 * steps + ((cycle - 0) & mask)];
          assert(x1796 != Fp::invalid());
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1797 = args[2][148 * steps + ((cycle - 0) & mask)];
          assert(x1797 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1798 = x1747 - x1794;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1798 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1799 = x1748 - x1795;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1799 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1800 = x1749 - x1796;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1800 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1801 = x1750 - x1797;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1801 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1802 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x1802 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1803 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x1803 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1804 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x1804 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1805 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x1805 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1806 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x1806 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1807 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x1807 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1808 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x1808 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1809 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x1809 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1810 = x1802 - x1809;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1811 = (x1810 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1812 = x6 - x1811;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1812);
          reg = x1812;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1813 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x1813 != Fp::invalid());
      if (x1813 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1814 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x1814 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1815 = x1814 - x1802;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1816 = x1815 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1817 = Fp(x1816.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1817);
            reg = x1817;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1818 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1818 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1819 = x1816 - x1818;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1820 = x1819 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1821 = Fp(x1820.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1821);
            reg = x1821;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1822 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1822 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1823 = x1820 - x1822;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1824 = x1823 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1825 = Fp(x1824.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1825);
            reg = x1825;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1826 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1826 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1827 = x1824 - x1826;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1828 = x1827 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1828);
          reg = x1828;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1829 = x6 - x1813;
      if (x1829 != 0) {
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1830 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x1830 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1831 = x1802 - x1830;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1831 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1832 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x1832 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1833 = x1832 * x4;
        // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1834 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x1834 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1835 = x1833 + x1834;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1836 = x1803 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1837 = x1835 - x1836;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1838 = x1837 + x1804;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1839 = Fp(x1838.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1839);
            reg = x1839;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1840 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x1840 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1841 = x1838 - x1840;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1842 = x1841 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1843 = Fp(x1842.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1843);
            reg = x1843;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1844 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x1844 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1845 = x1842 - x1844;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1846 = x1845 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1847 = Fp(x1846.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1847);
            reg = x1847;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1848 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x1848 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1849 = x1846 - x1848;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1850 = x1849 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1850);
          reg = x1850;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1851 = x6 - x1834;
        if (x1851 != 0) {
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1852 = args[2][152 * steps + ((cycle - 0) & mask)];
          assert(x1852 != Fp::invalid());
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1853 = args[2][153 * steps + ((cycle - 0) & mask)];
          assert(x1853 != Fp::invalid());
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1854 = args[2][154 * steps + ((cycle - 0) & mask)];
          assert(x1854 != Fp::invalid());
          // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1855 = args[2][155 * steps + ((cycle - 0) & mask)];
          assert(x1855 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1856 = x1805 - x1852;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1856 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1857 = x1806 - x1853;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1857 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1858 = x1807 - x1854;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1858 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1859 = x1808 - x1855;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1859 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1860 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x1860 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1861 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x1861 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1862 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x1862 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1863 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x1863 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1864 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x1864 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1865 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x1865 != Fp::invalid());
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1866 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x1866 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1867 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1867 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1868 = x1860 - x1867;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1869 = (x1868 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1870 = x6 - x1869;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1870);
          reg = x1870;
        }
      }
      // loc("Top/Mux/4/Mux/5/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1871 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x1871 != Fp::invalid());
      if (x1871 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1872 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1872 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1873 = x1872 - x1860;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1874 = x1873 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1875 = Fp(x1874.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1875);
            reg = x1875;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1876 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1876 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1877 = x1874 - x1876;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1878 = x1877 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1879 = Fp(x1878.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1879);
            reg = x1879;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1880 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1880 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1881 = x1878 - x1880;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1882 = x1881 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1883 = Fp(x1882.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1883);
            reg = x1883;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1884 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1884 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1885 = x1882 - x1884;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1886 = x1885 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1886);
          reg = x1886;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1887 = x6 - x1871;
      if (x1887 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1888 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x1888 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1889 = x1860 - x1888;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1889 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1890 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x1890 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1891 = x1890 * x4;
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1892 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x1892 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1893 = x1891 + x1892;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1894 = x1861 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1895 = x1893 - x1894;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1896 = x1895 + x1862;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1897 = Fp(x1896.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1897);
            reg = x1897;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1898 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x1898 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1899 = x1896 - x1898;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1900 = x1899 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1901 = Fp(x1900.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1901);
            reg = x1901;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1902 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x1902 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1903 = x1900 - x1902;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1904 = x1903 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1905 = Fp(x1904.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1905);
            reg = x1905;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1906 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x1906 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1907 = x1904 - x1906;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1908 = x1907 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1908);
          reg = x1908;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x1909 = x6 - x1892;
        if (x1909 != 0) {
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1910 = args[2][5 * steps + ((cycle - 0) & mask)];
          assert(x1910 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1911 = args[2][6 * steps + ((cycle - 0) & mask)];
          assert(x1911 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1912 = args[2][7 * steps + ((cycle - 0) & mask)];
          assert(x1912 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x1913 = args[2][8 * steps + ((cycle - 0) & mask)];
          assert(x1913 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1914 = x1863 - x1910;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1914 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1915 = x1864 - x1911;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1915 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1916 = x1865 - x1912;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1916 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x1917 = x1866 - x1913;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x1917 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x1918 = args[2][100 * steps + ((cycle - 0) & mask)];
    assert(x1918 != Fp::invalid());
    if (x1918 != 0) {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1919 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1919 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1920 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1920 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1921 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1921 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1922 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1922 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1923 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1923 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1924 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1924 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1925 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1925 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":31:3)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1919);
        reg = x1919;
      }
      // loc("cirgen/components/ram.cpp":32:3)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1920);
        reg = x1920;
      }
      // loc("cirgen/components/ram.cpp":33:3)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1921);
        reg = x1921;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1922);
        reg = x1922;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1923);
        reg = x1923;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1924);
        reg = x1924;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1925);
        reg = x1925;
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x1926 = args[2][101 * steps + ((cycle - 0) & mask)];
    assert(x1926 != Fp::invalid());
    if (x1926 != 0) {
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1927 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1927 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1928 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1928 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1929 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1929 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1930 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1930 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1931 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1931 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1932 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1932 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1933 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1933 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":31:3)
      {
        auto& reg = args[2][2 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1927);
        reg = x1927;
      }
      // loc("cirgen/components/ram.cpp":32:3)
      {
        auto& reg = args[2][3 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1928);
        reg = x1928;
      }
      // loc("cirgen/components/ram.cpp":33:3)
      {
        auto& reg = args[2][4 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1929);
        reg = x1929;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][5 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1930);
        reg = x1930;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][6 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1931);
        reg = x1931;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][7 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1932);
        reg = x1932;
      }
      // loc("cirgen/components/u32.cpp":72:5)
      {
        auto& reg = args[2][8 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x1933);
        reg = x1933;
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x1934 = args[2][102 * steps + ((cycle - 0) & mask)];
    assert(x1934 != Fp::invalid());
    if (x1934 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1935 = host_outs.at(0);
        auto x1936 = host_outs.at(1);
        auto x1937 = host_outs.at(2);
        auto x1938 = host_outs.at(3);
        auto x1939 = host_outs.at(4);
        auto x1940 = host_outs.at(5);
        auto x1941 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][135 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1935);
          reg = x1935;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1936);
          reg = x1936;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1937);
          reg = x1937;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1938);
          reg = x1938;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1939);
          reg = x1939;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1940);
          reg = x1940;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1941);
          reg = x1941;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1942 = host_outs.at(0);
        auto x1943 = host_outs.at(1);
        auto x1944 = host_outs.at(2);
        auto x1945 = host_outs.at(3);
        auto x1946 = host_outs.at(4);
        auto x1947 = host_outs.at(5);
        auto x1948 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1942);
          reg = x1942;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1943);
          reg = x1943;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1944);
          reg = x1944;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1945);
          reg = x1945;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1946);
          reg = x1946;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1947);
          reg = x1947;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1948);
          reg = x1948;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1949 = host_outs.at(0);
        auto x1950 = host_outs.at(1);
        auto x1951 = host_outs.at(2);
        auto x1952 = host_outs.at(3);
        auto x1953 = host_outs.at(4);
        auto x1954 = host_outs.at(5);
        auto x1955 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1949);
          reg = x1949;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1950);
          reg = x1950;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1951);
          reg = x1951;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1952);
          reg = x1952;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1953);
          reg = x1953;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1954);
          reg = x1954;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1955);
          reg = x1955;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x1956 = host_outs.at(0);
        auto x1957 = host_outs.at(1);
        auto x1958 = host_outs.at(2);
        auto x1959 = host_outs.at(3);
        auto x1960 = host_outs.at(4);
        auto x1961 = host_outs.at(5);
        auto x1962 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1956);
          reg = x1956;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1957);
          reg = x1957;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1958);
          reg = x1958;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1959);
          reg = x1959;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1960);
          reg = x1960;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1961);
          reg = x1961;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1962);
          reg = x1962;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
      auto x1963 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x1963 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x1964 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x1964 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x1965 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x1965 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1966 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x1966 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1967 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x1967 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1968 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x1968 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1969 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x1969 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1970 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x1970 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1971 = x1963 - x1970;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x1972 = (x1971 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x1973 = x6 - x1972;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1973);
          reg = x1973;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x1974 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x1974 != Fp::invalid());
      if (x1974 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1975 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x1975 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1976 = x1975 - x1963;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x1977 = x1976 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1978 = Fp(x1977.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1978);
            reg = x1978;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1979 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x1979 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1980 = x1977 - x1979;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1981 = x1980 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1982 = Fp(x1981.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1982);
            reg = x1982;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x1983 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x1983 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1984 = x1981 - x1983;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1985 = x1984 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x1986 = Fp(x1985.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x1986);
            reg = x1986;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x1987 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x1987 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x1988 = x1985 - x1987;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x1989 = x1988 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x1989);
          reg = x1989;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x1990 = x6 - x1974;
      if (x1990 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1991 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x1991 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x1992 = x1963 - x1991;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x1992 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1993 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x1993 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1994 = x1993 * x4;
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x1995 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x1995 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1996 = x1994 + x1995;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x1997 = x1964 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1998 = x1996 - x1997;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x1999 = x1998 + x1965;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2000 = Fp(x1999.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2000);
            reg = x2000;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2001 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2001 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2002 = x1999 - x2001;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2003 = x2002 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2004 = Fp(x2003.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2004);
            reg = x2004;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2005 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2005 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2006 = x2003 - x2005;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2007 = x2006 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2008 = Fp(x2007.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2008);
            reg = x2008;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2009 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2009 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2010 = x2007 - x2009;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2011 = x2010 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2011);
          reg = x2011;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2012 = x6 - x1995;
        if (x2012 != 0) {
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2013 = args[2][138 * steps + ((cycle - 0) & mask)];
          assert(x2013 != Fp::invalid());
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2014 = args[2][139 * steps + ((cycle - 0) & mask)];
          assert(x2014 != Fp::invalid());
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2015 = args[2][140 * steps + ((cycle - 0) & mask)];
          assert(x2015 != Fp::invalid());
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2016 = args[2][141 * steps + ((cycle - 0) & mask)];
          assert(x2016 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2017 = x1966 - x2013;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2017 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2018 = x1967 - x2014;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2018 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2019 = x1968 - x2015;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2019 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2020 = x1969 - x2016;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2020 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2021 = args[2][135 * steps + ((cycle - 0) & mask)];
      assert(x2021 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2022 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x2022 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2023 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x2023 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2024 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x2024 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2025 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x2025 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2026 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x2026 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2027 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x2027 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2028 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x2028 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2029 = x2021 - x2028;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2030 = (x2029 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2031 = x6 - x2030;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2031);
          reg = x2031;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2032 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x2032 != Fp::invalid());
      if (x2032 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2033 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x2033 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2034 = x2033 - x2021;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2035 = x2034 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2036 = Fp(x2035.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2036);
            reg = x2036;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2037 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2037 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2038 = x2035 - x2037;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2039 = x2038 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2040 = Fp(x2039.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2040);
            reg = x2040;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2041 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2041 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2042 = x2039 - x2041;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2043 = x2042 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2044 = Fp(x2043.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2044);
            reg = x2044;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2045 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2045 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2046 = x2043 - x2045;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2047 = x2046 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2047);
          reg = x2047;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2048 = x6 - x2032;
      if (x2048 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2049 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x2049 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2050 = x2021 - x2049;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2050 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2051 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2051 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2052 = x2051 * x4;
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2053 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x2053 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2054 = x2052 + x2053;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2055 = x2022 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2056 = x2054 - x2055;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2057 = x2056 + x2023;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2058 = Fp(x2057.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2058);
            reg = x2058;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2059 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2059 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2060 = x2057 - x2059;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2061 = x2060 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2062 = Fp(x2061.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2062);
            reg = x2062;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2063 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2063 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2064 = x2061 - x2063;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2065 = x2064 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2066 = Fp(x2065.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2066);
            reg = x2066;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2067 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2067 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2068 = x2065 - x2067;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2069 = x2068 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2069);
          reg = x2069;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2070 = x6 - x2053;
        if (x2070 != 0) {
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2071 = args[2][145 * steps + ((cycle - 0) & mask)];
          assert(x2071 != Fp::invalid());
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2072 = args[2][146 * steps + ((cycle - 0) & mask)];
          assert(x2072 != Fp::invalid());
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2073 = args[2][147 * steps + ((cycle - 0) & mask)];
          assert(x2073 != Fp::invalid());
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2074 = args[2][148 * steps + ((cycle - 0) & mask)];
          assert(x2074 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2075 = x2024 - x2071;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2075 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2076 = x2025 - x2072;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2076 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2077 = x2026 - x2073;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2077 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2078 = x2027 - x2074;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2078 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2079 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x2079 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2080 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x2080 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2081 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x2081 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2082 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x2082 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2083 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x2083 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2084 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x2084 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2085 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x2085 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2086 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x2086 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2087 = x2079 - x2086;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2088 = (x2087 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2089 = x6 - x2088;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2089);
          reg = x2089;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2090 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x2090 != Fp::invalid());
      if (x2090 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2091 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x2091 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2092 = x2091 - x2079;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2093 = x2092 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2094 = Fp(x2093.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2094);
            reg = x2094;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2095 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2095 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2096 = x2093 - x2095;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2097 = x2096 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2098 = Fp(x2097.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2098);
            reg = x2098;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2099 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2099 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2100 = x2097 - x2099;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2101 = x2100 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2102 = Fp(x2101.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2102);
            reg = x2102;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2103 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2103 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2104 = x2101 - x2103;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2105 = x2104 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2105);
          reg = x2105;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2106 = x6 - x2090;
      if (x2106 != 0) {
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2107 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x2107 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2108 = x2079 - x2107;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2108 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2109 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2109 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2110 = x2109 * x4;
        // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2111 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x2111 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2112 = x2110 + x2111;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2113 = x2080 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2114 = x2112 - x2113;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2115 = x2114 + x2081;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2116 = Fp(x2115.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2116);
            reg = x2116;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2117 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2117 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2118 = x2115 - x2117;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2119 = x2118 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2120 = Fp(x2119.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2120);
            reg = x2120;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2121 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2121 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2122 = x2119 - x2121;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2123 = x2122 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2124 = Fp(x2123.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2124);
            reg = x2124;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2125 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2125 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2126 = x2123 - x2125;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2127 = x2126 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2127);
          reg = x2127;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2128 = x6 - x2111;
        if (x2128 != 0) {
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2129 = args[2][152 * steps + ((cycle - 0) & mask)];
          assert(x2129 != Fp::invalid());
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2130 = args[2][153 * steps + ((cycle - 0) & mask)];
          assert(x2130 != Fp::invalid());
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2131 = args[2][154 * steps + ((cycle - 0) & mask)];
          assert(x2131 != Fp::invalid());
          // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2132 = args[2][155 * steps + ((cycle - 0) & mask)];
          assert(x2132 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2133 = x2082 - x2129;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2133 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2134 = x2083 - x2130;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2134 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2135 = x2084 - x2131;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2135 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2136 = x2085 - x2132;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2136 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2137 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x2137 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2138 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x2138 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2139 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x2139 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2140 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x2140 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2141 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x2141 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2142 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x2142 != Fp::invalid());
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2143 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x2143 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2144 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2144 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2145 = x2137 - x2144;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2146 = (x2145 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2147 = x6 - x2146;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2147);
          reg = x2147;
        }
      }
      // loc("Top/Mux/4/Mux/8/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2148 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x2148 != Fp::invalid());
      if (x2148 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2149 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2149 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2150 = x2149 - x2137;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2151 = x2150 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2152 = Fp(x2151.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2152);
            reg = x2152;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2153 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2153 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2154 = x2151 - x2153;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2155 = x2154 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2156 = Fp(x2155.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2156);
            reg = x2156;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2157 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2157 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2158 = x2155 - x2157;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2159 = x2158 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2160 = Fp(x2159.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2160);
            reg = x2160;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2161 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2161 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2162 = x2159 - x2161;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2163 = x2162 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2163);
          reg = x2163;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2164 = x6 - x2148;
      if (x2164 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2165 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2165 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2166 = x2137 - x2165;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2166 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2167 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2167 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2168 = x2167 * x4;
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2169 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2169 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2170 = x2168 + x2169;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2171 = x2138 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2172 = x2170 - x2171;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2173 = x2172 + x2139;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2174 = Fp(x2173.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2174);
            reg = x2174;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2175 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2175 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2176 = x2173 - x2175;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2177 = x2176 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2178 = Fp(x2177.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2178);
            reg = x2178;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2179 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2179 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2180 = x2177 - x2179;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2181 = x2180 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2182 = Fp(x2181.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2182);
            reg = x2182;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2183 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2183 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2184 = x2181 - x2183;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2185 = x2184 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2185);
          reg = x2185;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2186 = x6 - x2169;
        if (x2186 != 0) {
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2187 = args[2][5 * steps + ((cycle - 0) & mask)];
          assert(x2187 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2188 = args[2][6 * steps + ((cycle - 0) & mask)];
          assert(x2188 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2189 = args[2][7 * steps + ((cycle - 0) & mask)];
          assert(x2189 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2190 = args[2][8 * steps + ((cycle - 0) & mask)];
          assert(x2190 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2191 = x2140 - x2187;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2191 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2192 = x2141 - x2188;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2192 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2193 = x2142 - x2189;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2193 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2194 = x2143 - x2190;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2194 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x2195 = args[2][103 * steps + ((cycle - 0) & mask)];
    assert(x2195 != Fp::invalid());
    if (x2195 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2196 = host_outs.at(0);
        auto x2197 = host_outs.at(1);
        auto x2198 = host_outs.at(2);
        auto x2199 = host_outs.at(3);
        auto x2200 = host_outs.at(4);
        auto x2201 = host_outs.at(5);
        auto x2202 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][121 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2196);
          reg = x2196;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][122 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2197);
          reg = x2197;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][123 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2198);
          reg = x2198;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][124 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2199);
          reg = x2199;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][125 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2200);
          reg = x2200;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][126 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2201);
          reg = x2201;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][127 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2202);
          reg = x2202;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2203 = host_outs.at(0);
        auto x2204 = host_outs.at(1);
        auto x2205 = host_outs.at(2);
        auto x2206 = host_outs.at(3);
        auto x2207 = host_outs.at(4);
        auto x2208 = host_outs.at(5);
        auto x2209 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2203);
          reg = x2203;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2204);
          reg = x2204;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2205);
          reg = x2205;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2206);
          reg = x2206;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2207);
          reg = x2207;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2208);
          reg = x2208;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2209);
          reg = x2209;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2210 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2210 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2211 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2211 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2212 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2212 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2213 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2213 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2214 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2214 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2215 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2215 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2216 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2216 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2217 = args[2][121 * steps + ((cycle - 0) & mask)];
        assert(x2217 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2218 = x2210 - x2217;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2219 = (x2218 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2220 = x6 - x2219;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][128 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2220);
          reg = x2220;
        }
      }
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2221 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x2221 != Fp::invalid());
      if (x2221 != 0) {
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2222 = args[2][121 * steps + ((cycle - 0) & mask)];
        assert(x2222 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2223 = x2222 - x2210;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2224 = x2223 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2225 = Fp(x2224.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2225);
            reg = x2225;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2226 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2226 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2227 = x2224 - x2226;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2228 = x2227 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2229 = Fp(x2228.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2229);
            reg = x2229;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2230 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2230 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2231 = x2228 - x2230;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2232 = x2231 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2233 = Fp(x2232.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2233);
            reg = x2233;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2234 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2234 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2235 = x2232 - x2234;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2236 = x2235 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2236);
          reg = x2236;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2237 = x6 - x2221;
      if (x2237 != 0) {
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2238 = args[2][121 * steps + ((cycle - 0) & mask)];
        assert(x2238 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2239 = x2210 - x2238;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2239 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2240 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2240 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2241 = x2240 * x4;
        // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2242 = args[2][123 * steps + ((cycle - 0) & mask)];
        assert(x2242 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2243 = x2241 + x2242;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2244 = x2211 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2245 = x2243 - x2244;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2246 = x2245 + x2212;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2247 = Fp(x2246.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2247);
            reg = x2247;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2248 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2248 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2249 = x2246 - x2248;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2250 = x2249 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2251 = Fp(x2250.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2251);
            reg = x2251;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2252 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2252 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2253 = x2250 - x2252;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2254 = x2253 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2255 = Fp(x2254.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2255);
            reg = x2255;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2256 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2256 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2257 = x2254 - x2256;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2258 = x2257 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2258);
          reg = x2258;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2259 = x6 - x2242;
        if (x2259 != 0) {
          // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2260 = args[2][124 * steps + ((cycle - 0) & mask)];
          assert(x2260 != Fp::invalid());
          // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2261 = args[2][125 * steps + ((cycle - 0) & mask)];
          assert(x2261 != Fp::invalid());
          // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2262 = args[2][126 * steps + ((cycle - 0) & mask)];
          assert(x2262 != Fp::invalid());
          // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2263 = args[2][127 * steps + ((cycle - 0) & mask)];
          assert(x2263 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2264 = x2213 - x2260;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2264 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2265 = x2214 - x2261;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2265 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2266 = x2215 - x2262;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2266 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2267 = x2216 - x2263;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2267 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2268 = args[2][121 * steps + ((cycle - 0) & mask)];
      assert(x2268 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2269 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x2269 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2270 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x2270 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2271 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x2271 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2272 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x2272 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2273 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x2273 != Fp::invalid());
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2274 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x2274 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2275 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2275 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2276 = x2268 - x2275;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2277 = (x2276 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2278 = x6 - x2277;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][129 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2278);
          reg = x2278;
        }
      }
      // loc("Top/Mux/4/Mux/9/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2279 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x2279 != Fp::invalid());
      if (x2279 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2280 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2280 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2281 = x2280 - x2268;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2282 = x2281 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2283 = Fp(x2282.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2283);
            reg = x2283;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2284 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2284 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2285 = x2282 - x2284;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2286 = x2285 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2287 = Fp(x2286.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2287);
            reg = x2287;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2288 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2288 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2289 = x2286 - x2288;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2290 = x2289 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2291 = Fp(x2290.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2291);
            reg = x2291;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2292 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2292 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2293 = x2290 - x2292;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2294 = x2293 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2294);
          reg = x2294;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2295 = x6 - x2279;
      if (x2295 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2296 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2296 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2297 = x2268 - x2296;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2297 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2298 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2298 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2299 = x2298 * x4;
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2300 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2300 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2301 = x2299 + x2300;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2302 = x2269 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2303 = x2301 - x2302;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2304 = x2303 + x2270;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2305 = Fp(x2304.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2305);
            reg = x2305;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2306 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2306 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2307 = x2304 - x2306;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2308 = x2307 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2309 = Fp(x2308.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2309);
            reg = x2309;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2310 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2310 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2311 = x2308 - x2310;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2312 = x2311 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2313 = Fp(x2312.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2313);
            reg = x2313;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2314 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2314 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2315 = x2312 - x2314;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2316 = x2315 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2316);
          reg = x2316;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2317 = x6 - x2300;
        if (x2317 != 0) {
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2318 = args[2][5 * steps + ((cycle - 0) & mask)];
          assert(x2318 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2319 = args[2][6 * steps + ((cycle - 0) & mask)];
          assert(x2319 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2320 = args[2][7 * steps + ((cycle - 0) & mask)];
          assert(x2320 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2321 = args[2][8 * steps + ((cycle - 0) & mask)];
          assert(x2321 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2322 = x2271 - x2318;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2322 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2323 = x2272 - x2319;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2323 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2324 = x2273 - x2320;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2324 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2325 = x2274 - x2321;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2325 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x2326 = args[2][104 * steps + ((cycle - 0) & mask)];
    assert(x2326 != Fp::invalid());
    if (x2326 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2327 = host_outs.at(0);
        auto x2328 = host_outs.at(1);
        auto x2329 = host_outs.at(2);
        auto x2330 = host_outs.at(3);
        auto x2331 = host_outs.at(4);
        auto x2332 = host_outs.at(5);
        auto x2333 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][121 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2327);
          reg = x2327;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][122 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2328);
          reg = x2328;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][123 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2329);
          reg = x2329;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][124 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2330);
          reg = x2330;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][125 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2331);
          reg = x2331;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][126 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2332);
          reg = x2332;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][127 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2333);
          reg = x2333;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2334 = host_outs.at(0);
        auto x2335 = host_outs.at(1);
        auto x2336 = host_outs.at(2);
        auto x2337 = host_outs.at(3);
        auto x2338 = host_outs.at(4);
        auto x2339 = host_outs.at(5);
        auto x2340 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2334);
          reg = x2334;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2335);
          reg = x2335;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2336);
          reg = x2336;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2337);
          reg = x2337;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2338);
          reg = x2338;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2339);
          reg = x2339;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2340);
          reg = x2340;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2341 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2341 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2342 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2342 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2343 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2343 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2344 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2344 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2345 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2345 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2346 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2346 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2347 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2347 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2348 = args[2][121 * steps + ((cycle - 0) & mask)];
        assert(x2348 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2349 = x2341 - x2348;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2350 = (x2349 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2351 = x6 - x2350;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][128 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2351);
          reg = x2351;
        }
      }
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2352 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x2352 != Fp::invalid());
      if (x2352 != 0) {
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2353 = args[2][121 * steps + ((cycle - 0) & mask)];
        assert(x2353 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2354 = x2353 - x2341;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2355 = x2354 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2356 = Fp(x2355.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2356);
            reg = x2356;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2357 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2357 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2358 = x2355 - x2357;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2359 = x2358 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2360 = Fp(x2359.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2360);
            reg = x2360;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2361 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2361 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2362 = x2359 - x2361;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2363 = x2362 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2364 = Fp(x2363.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2364);
            reg = x2364;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2365 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2365 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2366 = x2363 - x2365;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2367 = x2366 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2367);
          reg = x2367;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2368 = x6 - x2352;
      if (x2368 != 0) {
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2369 = args[2][121 * steps + ((cycle - 0) & mask)];
        assert(x2369 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2370 = x2341 - x2369;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2370 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2371 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2371 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2372 = x2371 * x4;
        // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2373 = args[2][123 * steps + ((cycle - 0) & mask)];
        assert(x2373 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2374 = x2372 + x2373;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2375 = x2342 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2376 = x2374 - x2375;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2377 = x2376 + x2343;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2378 = Fp(x2377.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2378);
            reg = x2378;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2379 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2379 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2380 = x2377 - x2379;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2381 = x2380 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2382 = Fp(x2381.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2382);
            reg = x2382;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2383 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2383 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2384 = x2381 - x2383;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2385 = x2384 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2386 = Fp(x2385.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2386);
            reg = x2386;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2387 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2387 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2388 = x2385 - x2387;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2389 = x2388 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2389);
          reg = x2389;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2390 = x6 - x2373;
        if (x2390 != 0) {
          // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2391 = args[2][124 * steps + ((cycle - 0) & mask)];
          assert(x2391 != Fp::invalid());
          // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2392 = args[2][125 * steps + ((cycle - 0) & mask)];
          assert(x2392 != Fp::invalid());
          // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2393 = args[2][126 * steps + ((cycle - 0) & mask)];
          assert(x2393 != Fp::invalid());
          // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2394 = args[2][127 * steps + ((cycle - 0) & mask)];
          assert(x2394 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2395 = x2344 - x2391;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2395 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2396 = x2345 - x2392;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2396 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2397 = x2346 - x2393;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2397 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2398 = x2347 - x2394;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2398 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2399 = args[2][121 * steps + ((cycle - 0) & mask)];
      assert(x2399 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2400 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x2400 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2401 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x2401 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2402 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x2402 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2403 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x2403 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2404 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x2404 != Fp::invalid());
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2405 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x2405 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2406 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2406 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2407 = x2399 - x2406;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2408 = (x2407 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2409 = x6 - x2408;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][129 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2409);
          reg = x2409;
        }
      }
      // loc("Top/Mux/4/Mux/10/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2410 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x2410 != Fp::invalid());
      if (x2410 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2411 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2411 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2412 = x2411 - x2399;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2413 = x2412 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2414 = Fp(x2413.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2414);
            reg = x2414;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2415 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2415 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2416 = x2413 - x2415;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2417 = x2416 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2418 = Fp(x2417.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2418);
            reg = x2418;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2419 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2419 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2420 = x2417 - x2419;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2421 = x2420 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2422 = Fp(x2421.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2422);
            reg = x2422;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2423 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2423 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2424 = x2421 - x2423;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2425 = x2424 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2425);
          reg = x2425;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2426 = x6 - x2410;
      if (x2426 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2427 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2427 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2428 = x2399 - x2427;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2428 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2429 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2429 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2430 = x2429 * x4;
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2431 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2431 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2432 = x2430 + x2431;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2433 = x2400 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2434 = x2432 - x2433;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2435 = x2434 + x2401;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2436 = Fp(x2435.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2436);
            reg = x2436;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2437 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2437 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2438 = x2435 - x2437;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2439 = x2438 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2440 = Fp(x2439.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2440);
            reg = x2440;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2441 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2441 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2442 = x2439 - x2441;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2443 = x2442 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2444 = Fp(x2443.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2444);
            reg = x2444;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2445 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2445 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2446 = x2443 - x2445;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2447 = x2446 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2447);
          reg = x2447;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2448 = x6 - x2431;
        if (x2448 != 0) {
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2449 = args[2][5 * steps + ((cycle - 0) & mask)];
          assert(x2449 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2450 = args[2][6 * steps + ((cycle - 0) & mask)];
          assert(x2450 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2451 = args[2][7 * steps + ((cycle - 0) & mask)];
          assert(x2451 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2452 = args[2][8 * steps + ((cycle - 0) & mask)];
          assert(x2452 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2453 = x2402 - x2449;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2453 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2454 = x2403 - x2450;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2454 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2455 = x2404 - x2451;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2455 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2456 = x2405 - x2452;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2456 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x2457 = args[2][105 * steps + ((cycle - 0) & mask)];
    assert(x2457 != Fp::invalid());
    if (x2457 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2458 = host_outs.at(0);
        auto x2459 = host_outs.at(1);
        auto x2460 = host_outs.at(2);
        auto x2461 = host_outs.at(3);
        auto x2462 = host_outs.at(4);
        auto x2463 = host_outs.at(5);
        auto x2464 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][121 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2458);
          reg = x2458;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][122 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2459);
          reg = x2459;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][123 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2460);
          reg = x2460;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][124 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2461);
          reg = x2461;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][125 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2462);
          reg = x2462;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][126 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2463);
          reg = x2463;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][127 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2464);
          reg = x2464;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2465 = host_outs.at(0);
        auto x2466 = host_outs.at(1);
        auto x2467 = host_outs.at(2);
        auto x2468 = host_outs.at(3);
        auto x2469 = host_outs.at(4);
        auto x2470 = host_outs.at(5);
        auto x2471 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2465);
          reg = x2465;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2466);
          reg = x2466;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2467);
          reg = x2467;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2468);
          reg = x2468;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2469);
          reg = x2469;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2470);
          reg = x2470;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2471);
          reg = x2471;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2472 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2472 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2473 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2473 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2474 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2474 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2475 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2475 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2476 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2476 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2477 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2477 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2478 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2478 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2479 = args[2][121 * steps + ((cycle - 0) & mask)];
        assert(x2479 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2480 = x2472 - x2479;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2481 = (x2480 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2482 = x6 - x2481;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][128 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2482);
          reg = x2482;
        }
      }
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2483 = args[2][128 * steps + ((cycle - 0) & mask)];
      assert(x2483 != Fp::invalid());
      if (x2483 != 0) {
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2484 = args[2][121 * steps + ((cycle - 0) & mask)];
        assert(x2484 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2485 = x2484 - x2472;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2486 = x2485 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2487 = Fp(x2486.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2487);
            reg = x2487;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2488 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2488 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2489 = x2486 - x2488;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2490 = x2489 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2491 = Fp(x2490.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2491);
            reg = x2491;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2492 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2492 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2493 = x2490 - x2492;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2494 = x2493 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2495 = Fp(x2494.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2495);
            reg = x2495;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2496 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2496 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2497 = x2494 - x2496;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2498 = x2497 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2498);
          reg = x2498;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2499 = x6 - x2483;
      if (x2499 != 0) {
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2500 = args[2][121 * steps + ((cycle - 0) & mask)];
        assert(x2500 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2501 = x2472 - x2500;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2501 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2502 = args[2][122 * steps + ((cycle - 0) & mask)];
        assert(x2502 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2503 = x2502 * x4;
        // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2504 = args[2][123 * steps + ((cycle - 0) & mask)];
        assert(x2504 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2505 = x2503 + x2504;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2506 = x2473 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2507 = x2505 - x2506;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2508 = x2507 + x2474;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2509 = Fp(x2508.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2509);
            reg = x2509;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2510 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2510 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2511 = x2508 - x2510;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2512 = x2511 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2513 = Fp(x2512.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2513);
            reg = x2513;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2514 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2514 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2515 = x2512 - x2514;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2516 = x2515 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2517 = Fp(x2516.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2517);
            reg = x2517;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2518 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2518 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2519 = x2516 - x2518;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2520 = x2519 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2520);
          reg = x2520;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2521 = x6 - x2504;
        if (x2521 != 0) {
          // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2522 = args[2][124 * steps + ((cycle - 0) & mask)];
          assert(x2522 != Fp::invalid());
          // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2523 = args[2][125 * steps + ((cycle - 0) & mask)];
          assert(x2523 != Fp::invalid());
          // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2524 = args[2][126 * steps + ((cycle - 0) & mask)];
          assert(x2524 != Fp::invalid());
          // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2525 = args[2][127 * steps + ((cycle - 0) & mask)];
          assert(x2525 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2526 = x2475 - x2522;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2526 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2527 = x2476 - x2523;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2527 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2528 = x2477 - x2524;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2528 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2529 = x2478 - x2525;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2529 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2530 = args[2][121 * steps + ((cycle - 0) & mask)];
      assert(x2530 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2531 = args[2][122 * steps + ((cycle - 0) & mask)];
      assert(x2531 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2532 = args[2][123 * steps + ((cycle - 0) & mask)];
      assert(x2532 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2533 = args[2][124 * steps + ((cycle - 0) & mask)];
      assert(x2533 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2534 = args[2][125 * steps + ((cycle - 0) & mask)];
      assert(x2534 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2535 = args[2][126 * steps + ((cycle - 0) & mask)];
      assert(x2535 != Fp::invalid());
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkElement2/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2536 = args[2][127 * steps + ((cycle - 0) & mask)];
      assert(x2536 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2537 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2537 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2538 = x2530 - x2537;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2539 = (x2538 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2540 = x6 - x2539;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][129 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2540);
          reg = x2540;
        }
      }
      // loc("Top/Mux/4/Mux/11/ShaCycle/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2541 = args[2][129 * steps + ((cycle - 0) & mask)];
      assert(x2541 != Fp::invalid());
      if (x2541 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2542 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2542 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2543 = x2542 - x2530;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2544 = x2543 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2545 = Fp(x2544.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2545);
            reg = x2545;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2546 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2546 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2547 = x2544 - x2546;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2548 = x2547 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2549 = Fp(x2548.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2549);
            reg = x2549;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2550 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2550 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2551 = x2548 - x2550;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2552 = x2551 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2553 = Fp(x2552.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2553);
            reg = x2553;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2554 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2554 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2555 = x2552 - x2554;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2556 = x2555 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2556);
          reg = x2556;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2557 = x6 - x2541;
      if (x2557 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2558 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2558 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2559 = x2530 - x2558;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2559 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2560 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2560 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2561 = x2560 * x4;
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2562 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2562 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2563 = x2561 + x2562;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2564 = x2531 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2565 = x2563 - x2564;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2566 = x2565 + x2532;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2567 = Fp(x2566.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2567);
            reg = x2567;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2568 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2568 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2569 = x2566 - x2568;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2570 = x2569 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2571 = Fp(x2570.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2571);
            reg = x2571;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2572 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2572 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2573 = x2570 - x2572;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2574 = x2573 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2575 = Fp(x2574.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2575);
            reg = x2575;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2576 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2576 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2577 = x2574 - x2576;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2578 = x2577 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2578);
          reg = x2578;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2579 = x6 - x2562;
        if (x2579 != 0) {
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2580 = args[2][5 * steps + ((cycle - 0) & mask)];
          assert(x2580 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2581 = args[2][6 * steps + ((cycle - 0) & mask)];
          assert(x2581 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2582 = args[2][7 * steps + ((cycle - 0) & mask)];
          assert(x2582 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2583 = args[2][8 * steps + ((cycle - 0) & mask)];
          assert(x2583 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2584 = x2533 - x2580;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2584 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2585 = x2534 - x2581;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2585 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2586 = x2535 - x2582;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2586 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2587 = x2536 - x2583;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2587 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
    }
    // loc("cirgen/compiler/edsl/component.cpp":35:15)
    auto x2588 = args[2][106 * steps + ((cycle - 0) & mask)];
    assert(x2588 != Fp::invalid());
    if (x2588 != 0) {
      {
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2589 = host_outs.at(0);
        auto x2590 = host_outs.at(1);
        auto x2591 = host_outs.at(2);
        auto x2592 = host_outs.at(3);
        auto x2593 = host_outs.at(4);
        auto x2594 = host_outs.at(5);
        auto x2595 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][135 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2589);
          reg = x2589;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][136 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2590);
          reg = x2590;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][137 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2591);
          reg = x2591;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][138 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2592);
          reg = x2592;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][139 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2593);
          reg = x2593;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][140 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2594);
          reg = x2594;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][141 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2595);
          reg = x2595;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2596 = host_outs.at(0);
        auto x2597 = host_outs.at(1);
        auto x2598 = host_outs.at(2);
        auto x2599 = host_outs.at(3);
        auto x2600 = host_outs.at(4);
        auto x2601 = host_outs.at(5);
        auto x2602 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][142 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2596);
          reg = x2596;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][143 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2597);
          reg = x2597;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][144 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2598);
          reg = x2598;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][145 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2599);
          reg = x2599;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][146 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2600);
          reg = x2600;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][147 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2601);
          reg = x2601;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][148 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2602);
          reg = x2602;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2603 = host_outs.at(0);
        auto x2604 = host_outs.at(1);
        auto x2605 = host_outs.at(2);
        auto x2606 = host_outs.at(3);
        auto x2607 = host_outs.at(4);
        auto x2608 = host_outs.at(5);
        auto x2609 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][149 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2603);
          reg = x2603;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][150 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2604);
          reg = x2604;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][151 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2605);
          reg = x2605;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][152 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2606);
          reg = x2606;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][153 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2607);
          reg = x2607;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][154 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2608);
          reg = x2608;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][155 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2609);
          reg = x2609;
        }
        host(ctx, "plonkRead", "ram", host_args.data(), 0, host_outs.data(), 7);
        auto x2610 = host_outs.at(0);
        auto x2611 = host_outs.at(1);
        auto x2612 = host_outs.at(2);
        auto x2613 = host_outs.at(3);
        auto x2614 = host_outs.at(4);
        auto x2615 = host_outs.at(5);
        auto x2616 = host_outs.at(6);
        // loc("cirgen/components/ram.cpp":31:3)
        {
          auto& reg = args[2][2 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2610);
          reg = x2610;
        }
        // loc("cirgen/components/ram.cpp":32:3)
        {
          auto& reg = args[2][3 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2611);
          reg = x2611;
        }
        // loc("cirgen/components/ram.cpp":33:3)
        {
          auto& reg = args[2][4 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2612);
          reg = x2612;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][5 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2613);
          reg = x2613;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][6 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2614);
          reg = x2614;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][7 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2615);
          reg = x2615;
        }
        // loc("cirgen/components/u32.cpp":72:5)
        {
          auto& reg = args[2][8 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2616);
          reg = x2616;
        }
      }
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2617 = args[2][2 * steps + ((cycle - 1) & mask)];
      assert(x2617 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2618 = args[2][3 * steps + ((cycle - 1) & mask)];
      assert(x2618 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2619 = args[2][4 * steps + ((cycle - 1) & mask)];
      assert(x2619 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2620 = args[2][5 * steps + ((cycle - 1) & mask)];
      assert(x2620 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2621 = args[2][6 * steps + ((cycle - 1) & mask)];
      assert(x2621 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2622 = args[2][7 * steps + ((cycle - 1) & mask)];
      assert(x2622 != Fp::invalid());
      // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2623 = args[2][8 * steps + ((cycle - 1) & mask)];
      assert(x2623 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2624 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x2624 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2625 = x2617 - x2624;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2626 = (x2625 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2627 = x6 - x2626;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][156 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2627);
          reg = x2627;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2628 = args[2][156 * steps + ((cycle - 0) & mask)];
      assert(x2628 != Fp::invalid());
      if (x2628 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2629 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x2629 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2630 = x2629 - x2617;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2631 = x2630 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2632 = Fp(x2631.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2632);
            reg = x2632;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2633 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2633 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2634 = x2631 - x2633;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2635 = x2634 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2636 = Fp(x2635.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2636);
            reg = x2636;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2637 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2637 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2638 = x2635 - x2637;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2639 = x2638 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2640 = Fp(x2639.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2640);
            reg = x2640;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2641 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2641 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2642 = x2639 - x2641;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2643 = x2642 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2643);
          reg = x2643;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2644 = x6 - x2628;
      if (x2644 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2645 = args[2][135 * steps + ((cycle - 0) & mask)];
        assert(x2645 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2646 = x2617 - x2645;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2646 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2647 = args[2][136 * steps + ((cycle - 0) & mask)];
        assert(x2647 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2648 = x2647 * x4;
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2649 = args[2][137 * steps + ((cycle - 0) & mask)];
        assert(x2649 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2650 = x2648 + x2649;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2651 = x2618 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2652 = x2650 - x2651;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2653 = x2652 + x2619;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2654 = Fp(x2653.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][13 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2654);
            reg = x2654;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2655 = args[2][13 * steps + ((cycle - 0) & mask)];
        assert(x2655 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2656 = x2653 - x2655;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2657 = x2656 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2658 = Fp(x2657.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][14 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2658);
            reg = x2658;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2659 = args[2][14 * steps + ((cycle - 0) & mask)];
        assert(x2659 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2660 = x2657 - x2659;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2661 = x2660 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2662 = Fp(x2661.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][15 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2662);
            reg = x2662;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2663 = args[2][15 * steps + ((cycle - 0) & mask)];
        assert(x2663 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2664 = x2661 - x2663;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2665 = x2664 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][74 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2665);
          reg = x2665;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2666 = x6 - x2649;
        if (x2666 != 0) {
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2667 = args[2][138 * steps + ((cycle - 0) & mask)];
          assert(x2667 != Fp::invalid());
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2668 = args[2][139 * steps + ((cycle - 0) & mask)];
          assert(x2668 != Fp::invalid());
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2669 = args[2][140 * steps + ((cycle - 0) & mask)];
          assert(x2669 != Fp::invalid());
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2670 = args[2][141 * steps + ((cycle - 0) & mask)];
          assert(x2670 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2671 = x2620 - x2667;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2671 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2672 = x2621 - x2668;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2672 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2673 = x2622 - x2669;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2673 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2674 = x2623 - x2670;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2674 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2675 = args[2][135 * steps + ((cycle - 0) & mask)];
      assert(x2675 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2676 = args[2][136 * steps + ((cycle - 0) & mask)];
      assert(x2676 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2677 = args[2][137 * steps + ((cycle - 0) & mask)];
      assert(x2677 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2678 = args[2][138 * steps + ((cycle - 0) & mask)];
      assert(x2678 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2679 = args[2][139 * steps + ((cycle - 0) & mask)];
      assert(x2679 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2680 = args[2][140 * steps + ((cycle - 0) & mask)];
      assert(x2680 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement4/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2681 = args[2][141 * steps + ((cycle - 0) & mask)];
      assert(x2681 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2682 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x2682 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2683 = x2675 - x2682;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2684 = (x2683 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2685 = x6 - x2684;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][157 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2685);
          reg = x2685;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2686 = args[2][157 * steps + ((cycle - 0) & mask)];
      assert(x2686 != Fp::invalid());
      if (x2686 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2687 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x2687 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2688 = x2687 - x2675;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2689 = x2688 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2690 = Fp(x2689.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2690);
            reg = x2690;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2691 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2691 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2692 = x2689 - x2691;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2693 = x2692 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2694 = Fp(x2693.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2694);
            reg = x2694;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2695 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2695 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2696 = x2693 - x2695;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2697 = x2696 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2698 = Fp(x2697.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2698);
            reg = x2698;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2699 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2699 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2700 = x2697 - x2699;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2701 = x2700 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2701);
          reg = x2701;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2702 = x6 - x2686;
      if (x2702 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2703 = args[2][142 * steps + ((cycle - 0) & mask)];
        assert(x2703 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2704 = x2675 - x2703;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2704 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2705 = args[2][143 * steps + ((cycle - 0) & mask)];
        assert(x2705 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2706 = x2705 * x4;
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2707 = args[2][144 * steps + ((cycle - 0) & mask)];
        assert(x2707 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2708 = x2706 + x2707;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2709 = x2676 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2710 = x2708 - x2709;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2711 = x2710 + x2677;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2712 = Fp(x2711.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][16 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2712);
            reg = x2712;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2713 = args[2][16 * steps + ((cycle - 0) & mask)];
        assert(x2713 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2714 = x2711 - x2713;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2715 = x2714 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2716 = Fp(x2715.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][17 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2716);
            reg = x2716;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2717 = args[2][17 * steps + ((cycle - 0) & mask)];
        assert(x2717 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2718 = x2715 - x2717;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2719 = x2718 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2720 = Fp(x2719.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][18 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2720);
            reg = x2720;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2721 = args[2][18 * steps + ((cycle - 0) & mask)];
        assert(x2721 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2722 = x2719 - x2721;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2723 = x2722 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][75 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2723);
          reg = x2723;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2724 = x6 - x2707;
        if (x2724 != 0) {
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2725 = args[2][145 * steps + ((cycle - 0) & mask)];
          assert(x2725 != Fp::invalid());
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2726 = args[2][146 * steps + ((cycle - 0) & mask)];
          assert(x2726 != Fp::invalid());
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2727 = args[2][147 * steps + ((cycle - 0) & mask)];
          assert(x2727 != Fp::invalid());
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2728 = args[2][148 * steps + ((cycle - 0) & mask)];
          assert(x2728 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2729 = x2678 - x2725;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2729 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2730 = x2679 - x2726;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2730 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2731 = x2680 - x2727;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2731 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2732 = x2681 - x2728;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2732 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2733 = args[2][142 * steps + ((cycle - 0) & mask)];
      assert(x2733 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2734 = args[2][143 * steps + ((cycle - 0) & mask)];
      assert(x2734 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2735 = args[2][144 * steps + ((cycle - 0) & mask)];
      assert(x2735 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2736 = args[2][145 * steps + ((cycle - 0) & mask)];
      assert(x2736 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2737 = args[2][146 * steps + ((cycle - 0) & mask)];
      assert(x2737 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2738 = args[2][147 * steps + ((cycle - 0) & mask)];
      assert(x2738 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement5/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2739 = args[2][148 * steps + ((cycle - 0) & mask)];
      assert(x2739 != Fp::invalid());
      {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2740 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x2740 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2741 = x2733 - x2740;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2742 = (x2741 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2743 = x6 - x2742;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][158 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2743);
          reg = x2743;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2744 = args[2][158 * steps + ((cycle - 0) & mask)];
      assert(x2744 != Fp::invalid());
      if (x2744 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2745 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x2745 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2746 = x2745 - x2733;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2747 = x2746 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2748 = Fp(x2747.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2748);
            reg = x2748;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2749 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2749 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2750 = x2747 - x2749;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2751 = x2750 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2752 = Fp(x2751.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2752);
            reg = x2752;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2753 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2753 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2754 = x2751 - x2753;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2755 = x2754 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2756 = Fp(x2755.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2756);
            reg = x2756;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2757 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2757 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2758 = x2755 - x2757;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2759 = x2758 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2759);
          reg = x2759;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2760 = x6 - x2744;
      if (x2760 != 0) {
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2761 = args[2][149 * steps + ((cycle - 0) & mask)];
        assert(x2761 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2762 = x2733 - x2761;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2762 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2763 = args[2][150 * steps + ((cycle - 0) & mask)];
        assert(x2763 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2764 = x2763 * x4;
        // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2765 = args[2][151 * steps + ((cycle - 0) & mask)];
        assert(x2765 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2766 = x2764 + x2765;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2767 = x2734 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2768 = x2766 - x2767;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2769 = x2768 + x2735;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2770 = Fp(x2769.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][19 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2770);
            reg = x2770;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2771 = args[2][19 * steps + ((cycle - 0) & mask)];
        assert(x2771 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2772 = x2769 - x2771;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2773 = x2772 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2774 = Fp(x2773.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][20 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2774);
            reg = x2774;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2775 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2775 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2776 = x2773 - x2775;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2777 = x2776 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2778 = Fp(x2777.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][21 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2778);
            reg = x2778;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2779 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2779 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2780 = x2777 - x2779;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2781 = x2780 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][76 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2781);
          reg = x2781;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2782 = x6 - x2765;
        if (x2782 != 0) {
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2783 = args[2][152 * steps + ((cycle - 0) & mask)];
          assert(x2783 != Fp::invalid());
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2784 = args[2][153 * steps + ((cycle - 0) & mask)];
          assert(x2784 != Fp::invalid());
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2785 = args[2][154 * steps + ((cycle - 0) & mask)];
          assert(x2785 != Fp::invalid());
          // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2786 = args[2][155 * steps + ((cycle - 0) & mask)];
          assert(x2786 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2787 = x2736 - x2783;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2787 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2788 = x2737 - x2784;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2788 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2789 = x2738 - x2785;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2789 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2790 = x2739 - x2786;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2790 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg"("cirgen/components/ram.cpp":47:40))
      auto x2791 = args[2][149 * steps + ((cycle - 0) & mask)];
      assert(x2791 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg1"("cirgen/components/ram.cpp":48:42))
      auto x2792 = args[2][150 * steps + ((cycle - 0) & mask)];
      assert(x2792 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/Reg2"("cirgen/components/ram.cpp":49:46))
      auto x2793 = args[2][151 * steps + ((cycle - 0) & mask)];
      assert(x2793 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2794 = args[2][152 * steps + ((cycle - 0) & mask)];
      assert(x2794 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2795 = args[2][153 * steps + ((cycle - 0) & mask)];
      assert(x2795 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2796 = args[2][154 * steps + ((cycle - 0) & mask)];
      assert(x2796 != Fp::invalid());
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkElement6/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2797 = args[2][155 * steps + ((cycle - 0) & mask)];
      assert(x2797 != Fp::invalid());
      {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2798 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2798 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2799 = x2791 - x2798;
        // loc("cirgen/components/ram.cpp":52:35)
        auto x2800 = (x2799 == 0) ? Fp(1) : Fp(0);
        // loc("cirgen/components/ram.cpp":52:27)
        auto x2801 = x6 - x2800;
        // loc("cirgen/components/ram.cpp":52:12)
        {
          auto& reg = args[2][159 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2801);
          reg = x2801;
        }
      }
      // loc("Top/Mux/4/Mux/12/RamBody/PlonkBody/RamPlonkVerifier3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2802 = args[2][159 * steps + ((cycle - 0) & mask)];
      assert(x2802 != Fp::invalid());
      if (x2802 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2803 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2803 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2804 = x2803 - x2791;
        // loc("cirgen/components/ram.cpp":62:31)
        auto x2805 = x2804 - x6;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2806 = Fp(x2805.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2806);
            reg = x2806;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2807 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2807 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2808 = x2805 - x2807;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2809 = x2808 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2810 = Fp(x2809.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2810);
            reg = x2810;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2811 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2811 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2812 = x2809 - x2811;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2813 = x2812 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2814 = Fp(x2813.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2814);
            reg = x2814;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2815 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2815 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2816 = x2813 - x2815;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2817 = x2816 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2817);
          reg = x2817;
        }
      }
      // loc("cirgen/components/ram.cpp":64:19)
      auto x2818 = x6 - x2802;
      if (x2818 != 0) {
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2819 = args[2][2 * steps + ((cycle - 0) & mask)];
        assert(x2819 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":66:9)
        auto x2820 = x2791 - x2819;
        // loc("cirgen/components/ram.cpp":66:9)
        if (x2820 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2821 = args[2][3 * steps + ((cycle - 0) & mask)];
        assert(x2821 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2822 = x2821 * x4;
        // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
        auto x2823 = args[2][4 * steps + ((cycle - 0) & mask)];
        assert(x2823 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2824 = x2822 + x2823;
        // loc("cirgen/components/ram.cpp":68:45)
        auto x2825 = x2792 * x4;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2826 = x2824 - x2825;
        // loc("cirgen/components/ram.cpp":68:17)
        auto x2827 = x2826 + x2793;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2828 = Fp(x2827.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][22 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2828);
            reg = x2828;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2829 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2829 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2830 = x2827 - x2829;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2831 = x2830 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2832 = Fp(x2831.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][23 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2832);
            reg = x2832;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("cirgen/components/bytes.cpp":79:16))
        auto x2833 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2833 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2834 = x2831 - x2833;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2835 = x2834 * x2;
        {
          // loc("cirgen/components/bytes.cpp":78:21)
          auto x2836 = Fp(x2835.asUInt32() & x3.asUInt32());
          // loc("cirgen/components/bytes.cpp":78:12)
          {
            auto& reg = args[2][24 * steps + cycle];
            assert(reg == Fp::invalid() || reg == x2836);
            reg = x2836;
          }
        }
        // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("cirgen/components/bytes.cpp":79:16))
        auto x2837 = args[2][24 * steps + ((cycle - 0) & mask)];
        assert(x2837 != Fp::invalid());
        // loc("cirgen/components/bytes.cpp":79:11)
        auto x2838 = x2835 - x2837;
        // loc("cirgen/components/bytes.cpp":79:10)
        auto x2839 = x2838 * x2;
        // loc("./cirgen/components/bits.h":53:23)
        {
          auto& reg = args[2][77 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2839);
          reg = x2839;
        }
        // loc("cirgen/components/ram.cpp":70:22)
        auto x2840 = x6 - x2823;
        if (x2840 != 0) {
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2841 = args[2][5 * steps + ((cycle - 0) & mask)];
          assert(x2841 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2842 = args[2][6 * steps + ((cycle - 0) & mask)];
          assert(x2842 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2843 = args[2][7 * steps + ((cycle - 0) & mask)];
          assert(x2843 != Fp::invalid());
          // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
          auto x2844 = args[2][8 * steps + ((cycle - 0) & mask)];
          assert(x2844 != Fp::invalid());
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2845 = x2794 - x2841;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2845 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2846 = x2795 - x2842;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2846 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2847 = x2796 - x2843;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2847 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
          // loc("cirgen/components/ram.cpp":70:26)
          auto x2848 = x2797 - x2844;
          // loc("cirgen/components/ram.cpp":70:26)
          if (x2848 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        }
      }
    }
  }
  if (x11 != 0) {
    // loc("cirgen/components/ram.cpp":17:3)
    {
      auto& reg = args[2][17 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x1);
      reg = x1;
    }
    // loc("cirgen/components/ram.cpp":18:3)
    {
      auto& reg = args[2][18 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x0);
      reg = x0;
    }
    // loc("cirgen/components/ram.cpp":19:3)
    {
      auto& reg = args[2][19 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x6);
      reg = x6;
    }
    // loc("cirgen/components/u32.cpp":18:5)
    {
      auto& reg = args[2][20 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x5);
      reg = x5;
    }
    // loc("cirgen/components/u32.cpp":18:5)
    {
      auto& reg = args[2][21 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x5);
      reg = x5;
    }
    // loc("cirgen/components/u32.cpp":18:5)
    {
      auto& reg = args[2][22 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x5);
      reg = x5;
    }
    // loc("cirgen/components/u32.cpp":18:5)
    {
      auto& reg = args[2][23 * steps + cycle];
      assert(reg == Fp::invalid() || reg == x5);
      reg = x5;
    }
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg"("cirgen/components/ram.cpp":47:40))
    auto x2849 = args[2][2 * steps + ((cycle - 1) & mask)];
    assert(x2849 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg1"("cirgen/components/ram.cpp":48:42))
    auto x2850 = args[2][3 * steps + ((cycle - 1) & mask)];
    assert(x2850 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/Reg2"("cirgen/components/ram.cpp":49:46))
    auto x2851 = args[2][4 * steps + ((cycle - 1) & mask)];
    assert(x2851 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x2852 = args[2][5 * steps + ((cycle - 1) & mask)];
    assert(x2852 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
    auto x2853 = args[2][6 * steps + ((cycle - 1) & mask)];
    assert(x2853 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
    auto x2854 = args[2][7 * steps + ((cycle - 1) & mask)];
    assert(x2854 != Fp::invalid());
    // loc("Top/PlonkHeader1/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
    auto x2855 = args[2][8 * steps + ((cycle - 1) & mask)];
    assert(x2855 != Fp::invalid());
    {
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x2856 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x2856 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":52:35)
      auto x2857 = x2849 - x2856;
      // loc("cirgen/components/ram.cpp":52:35)
      auto x2858 = (x2857 == 0) ? Fp(1) : Fp(0);
      // loc("cirgen/components/ram.cpp":52:27)
      auto x2859 = x6 - x2858;
      // loc("cirgen/components/ram.cpp":52:12)
      {
        auto& reg = args[2][24 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2859);
        reg = x2859;
      }
    }
    // loc("Top/Mux/5/PlonkFini/RamPlonkVerifier/Reg"("./cirgen/compiler/edsl/component.h":81:27))
    auto x2860 = args[2][24 * steps + ((cycle - 0) & mask)];
    assert(x2860 != Fp::invalid());
    if (x2860 != 0) {
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x2861 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x2861 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":62:31)
      auto x2862 = x2861 - x2849;
      // loc("cirgen/components/ram.cpp":62:31)
      auto x2863 = x2862 - x6;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x2864 = Fp(x2863.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2864);
          reg = x2864;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x2865 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x2865 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x2866 = x2863 - x2865;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x2867 = x2866 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x2868 = Fp(x2867.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2868);
          reg = x2868;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":79:16))
      auto x2869 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x2869 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x2870 = x2867 - x2869;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x2871 = x2870 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x2872 = Fp(x2871.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2872);
          reg = x2872;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x2873 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x2873 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x2874 = x2871 - x2873;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x2875 = x2874 * x2;
      // loc("./cirgen/components/bits.h":53:23)
      {
        auto& reg = args[2][16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2875);
        reg = x2875;
      }
    }
    // loc("cirgen/components/ram.cpp":64:19)
    auto x2876 = x6 - x2860;
    if (x2876 != 0) {
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x2877 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x2877 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":66:9)
      auto x2878 = x2849 - x2877;
      // loc("cirgen/components/ram.cpp":66:9)
      if (x2878 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:66");
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg1"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x2879 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x2879 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:17)
      auto x2880 = x2879 * x4;
      // loc("Top/Mux/5/PlonkFini/RamPlonkElement/Reg2"("./cirgen/compiler/edsl/edsl.h":106:61))
      auto x2881 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x2881 != Fp::invalid());
      // loc("cirgen/components/ram.cpp":68:17)
      auto x2882 = x2880 + x2881;
      // loc("cirgen/components/ram.cpp":68:45)
      auto x2883 = x2850 * x4;
      // loc("cirgen/components/ram.cpp":68:17)
      auto x2884 = x2882 - x2883;
      // loc("cirgen/components/ram.cpp":68:17)
      auto x2885 = x2884 + x2851;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x2886 = Fp(x2885.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][10 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2886);
          reg = x2886;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x2887 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x2887 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x2888 = x2885 - x2887;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x2889 = x2888 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x2890 = Fp(x2889.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][11 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2890);
          reg = x2890;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("cirgen/components/bytes.cpp":79:16))
      auto x2891 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x2891 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x2892 = x2889 - x2891;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x2893 = x2892 * x2;
      {
        // loc("cirgen/components/bytes.cpp":78:21)
        auto x2894 = Fp(x2893.asUInt32() & x3.asUInt32());
        // loc("cirgen/components/bytes.cpp":78:12)
        {
          auto& reg = args[2][12 * steps + cycle];
          assert(reg == Fp::invalid() || reg == x2894);
          reg = x2894;
        }
      }
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("cirgen/components/bytes.cpp":79:16))
      auto x2895 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x2895 != Fp::invalid());
      // loc("cirgen/components/bytes.cpp":79:11)
      auto x2896 = x2893 - x2895;
      // loc("cirgen/components/bytes.cpp":79:10)
      auto x2897 = x2896 * x2;
      // loc("./cirgen/components/bits.h":53:23)
      {
        auto& reg = args[2][16 * steps + cycle];
        assert(reg == Fp::invalid() || reg == x2897);
        reg = x2897;
      }
      // loc("cirgen/components/ram.cpp":70:22)
      auto x2898 = x6 - x2881;
      if (x2898 != 0) {
        // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg"("./cirgen/compiler/edsl/component.h":81:27))
        auto x2899 = args[2][20 * steps + ((cycle - 0) & mask)];
        assert(x2899 != Fp::invalid());
        // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
        auto x2900 = args[2][21 * steps + ((cycle - 0) & mask)];
        assert(x2900 != Fp::invalid());
        // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg2"("./cirgen/compiler/edsl/component.h":81:27))
        auto x2901 = args[2][22 * steps + ((cycle - 0) & mask)];
        assert(x2901 != Fp::invalid());
        // loc("Top/Mux/5/PlonkFini/RamPlonkElement/U32Reg/Reg3"("./cirgen/compiler/edsl/component.h":81:27))
        auto x2902 = args[2][23 * steps + ((cycle - 0) & mask)];
        assert(x2902 != Fp::invalid());
        // loc("cirgen/components/ram.cpp":70:26)
        auto x2903 = x2852 - x2899;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x2903 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x2904 = x2853 - x2900;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x2904 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x2905 = x2854 - x2901;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x2905 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
        // loc("cirgen/components/ram.cpp":70:26)
        auto x2906 = x2855 - x2902;
        // loc("cirgen/components/ram.cpp":70:26)
        if (x2906 != 0) throw std::runtime_error("eqz failed at: cirgen/components/ram.cpp:70");
      }
    }
  }
  if (x7 != 0) {
    {
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2907 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x2907 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2908 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x2908 != Fp::invalid());
      host_args.at(0) = x2907;
      host_args.at(1) = x2908;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2909 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x2909 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement1/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2910 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x2910 != Fp::invalid());
      host_args.at(0) = x2909;
      host_args.at(1) = x2910;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2911 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x2911 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2912 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x2912 != Fp::invalid());
      host_args.at(0) = x2911;
      host_args.at(1) = x2912;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2913 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x2913 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2914 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x2914 != Fp::invalid());
      host_args.at(0) = x2913;
      host_args.at(1) = x2914;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2915 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x2915 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2916 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x2916 != Fp::invalid());
      host_args.at(0) = x2915;
      host_args.at(1) = x2916;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2917 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x2917 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2918 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x2918 != Fp::invalid());
      host_args.at(0) = x2917;
      host_args.at(1) = x2918;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2919 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x2919 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2920 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x2920 != Fp::invalid());
      host_args.at(0) = x2919;
      host_args.at(1) = x2920;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2921 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x2921 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2922 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x2922 != Fp::invalid());
      host_args.at(0) = x2921;
      host_args.at(1) = x2922;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2923 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x2923 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2924 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x2924 != Fp::invalid());
      host_args.at(0) = x2923;
      host_args.at(1) = x2924;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2925 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x2925 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2926 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x2926 != Fp::invalid());
      host_args.at(0) = x2925;
      host_args.at(1) = x2926;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2927 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x2927 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2928 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x2928 != Fp::invalid());
      host_args.at(0) = x2927;
      host_args.at(1) = x2928;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement11/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2929 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x2929 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement11/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2930 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x2930 != Fp::invalid());
      host_args.at(0) = x2929;
      host_args.at(1) = x2930;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement12/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2931 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x2931 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement12/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2932 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x2932 != Fp::invalid());
      host_args.at(0) = x2931;
      host_args.at(1) = x2932;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement13/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2933 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x2933 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement13/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2934 = args[2][37 * steps + ((cycle - 0) & mask)];
      assert(x2934 != Fp::invalid());
      host_args.at(0) = x2933;
      host_args.at(1) = x2934;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement14/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2935 = args[2][38 * steps + ((cycle - 0) & mask)];
      assert(x2935 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement14/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2936 = args[2][39 * steps + ((cycle - 0) & mask)];
      assert(x2936 != Fp::invalid());
      host_args.at(0) = x2935;
      host_args.at(1) = x2936;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement15/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2937 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x2937 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement15/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2938 = args[2][41 * steps + ((cycle - 0) & mask)];
      assert(x2938 != Fp::invalid());
      host_args.at(0) = x2937;
      host_args.at(1) = x2938;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement16/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2939 = args[2][42 * steps + ((cycle - 0) & mask)];
      assert(x2939 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement16/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2940 = args[2][43 * steps + ((cycle - 0) & mask)];
      assert(x2940 != Fp::invalid());
      host_args.at(0) = x2939;
      host_args.at(1) = x2940;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement17/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2941 = args[2][44 * steps + ((cycle - 0) & mask)];
      assert(x2941 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement17/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2942 = args[2][45 * steps + ((cycle - 0) & mask)];
      assert(x2942 != Fp::invalid());
      host_args.at(0) = x2941;
      host_args.at(1) = x2942;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement18/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2943 = args[2][46 * steps + ((cycle - 0) & mask)];
      assert(x2943 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement18/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2944 = args[2][47 * steps + ((cycle - 0) & mask)];
      assert(x2944 != Fp::invalid());
      host_args.at(0) = x2943;
      host_args.at(1) = x2944;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement19/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2945 = args[2][48 * steps + ((cycle - 0) & mask)];
      assert(x2945 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement19/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2946 = args[2][49 * steps + ((cycle - 0) & mask)];
      assert(x2946 != Fp::invalid());
      host_args.at(0) = x2945;
      host_args.at(1) = x2946;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement20/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2947 = args[2][50 * steps + ((cycle - 0) & mask)];
      assert(x2947 != Fp::invalid());
      // loc("Top/Mux/1/BytesSetup/PlonkBody/BytesPlonkElement20/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2948 = args[2][51 * steps + ((cycle - 0) & mask)];
      assert(x2948 != Fp::invalid());
      host_args.at(0) = x2947;
      host_args.at(1) = x2948;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x8 != 0) {
    {
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2949 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x2949 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2950 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x2950 != Fp::invalid());
      host_args.at(0) = x2949;
      host_args.at(1) = x2950;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2951 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x2951 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2952 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x2952 != Fp::invalid());
      host_args.at(0) = x2951;
      host_args.at(1) = x2952;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2953 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x2953 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2954 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x2954 != Fp::invalid());
      host_args.at(0) = x2953;
      host_args.at(1) = x2954;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2955 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x2955 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2956 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x2956 != Fp::invalid());
      host_args.at(0) = x2955;
      host_args.at(1) = x2956;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2957 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x2957 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2958 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x2958 != Fp::invalid());
      host_args.at(0) = x2957;
      host_args.at(1) = x2958;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2959 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x2959 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2960 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x2960 != Fp::invalid());
      host_args.at(0) = x2959;
      host_args.at(1) = x2960;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2961 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x2961 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2962 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x2962 != Fp::invalid());
      host_args.at(0) = x2961;
      host_args.at(1) = x2962;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2963 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x2963 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2964 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x2964 != Fp::invalid());
      host_args.at(0) = x2963;
      host_args.at(1) = x2964;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2965 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x2965 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2966 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x2966 != Fp::invalid());
      host_args.at(0) = x2965;
      host_args.at(1) = x2966;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2967 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x2967 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2968 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x2968 != Fp::invalid());
      host_args.at(0) = x2967;
      host_args.at(1) = x2968;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2969 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x2969 != Fp::invalid());
      // loc("Top/Mux/2/BytesBody/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2970 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x2970 != Fp::invalid());
      host_args.at(0) = x2969;
      host_args.at(1) = x2970;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x9 != 0) {
    {
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2971 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x2971 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2972 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x2972 != Fp::invalid());
      host_args.at(0) = x2971;
      host_args.at(1) = x2972;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2973 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x2973 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2974 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x2974 != Fp::invalid());
      host_args.at(0) = x2973;
      host_args.at(1) = x2974;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2975 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x2975 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2976 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x2976 != Fp::invalid());
      host_args.at(0) = x2975;
      host_args.at(1) = x2976;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2977 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x2977 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2978 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x2978 != Fp::invalid());
      host_args.at(0) = x2977;
      host_args.at(1) = x2978;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2979 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x2979 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2980 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x2980 != Fp::invalid());
      host_args.at(0) = x2979;
      host_args.at(1) = x2980;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2981 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x2981 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2982 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x2982 != Fp::invalid());
      host_args.at(0) = x2981;
      host_args.at(1) = x2982;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2983 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x2983 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2984 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x2984 != Fp::invalid());
      host_args.at(0) = x2983;
      host_args.at(1) = x2984;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2985 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x2985 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2986 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x2986 != Fp::invalid());
      host_args.at(0) = x2985;
      host_args.at(1) = x2986;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2987 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x2987 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2988 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x2988 != Fp::invalid());
      host_args.at(0) = x2987;
      host_args.at(1) = x2988;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2989 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x2989 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2990 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x2990 != Fp::invalid());
      host_args.at(0) = x2989;
      host_args.at(1) = x2990;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2991 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x2991 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2992 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x2992 != Fp::invalid());
      host_args.at(0) = x2991;
      host_args.at(1) = x2992;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement11/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2993 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x2993 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement11/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2994 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x2994 != Fp::invalid());
      host_args.at(0) = x2993;
      host_args.at(1) = x2994;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement12/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2995 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x2995 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement12/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2996 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x2996 != Fp::invalid());
      host_args.at(0) = x2995;
      host_args.at(1) = x2996;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement13/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2997 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x2997 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement13/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2998 = args[2][37 * steps + ((cycle - 0) & mask)];
      assert(x2998 != Fp::invalid());
      host_args.at(0) = x2997;
      host_args.at(1) = x2998;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement14/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x2999 = args[2][38 * steps + ((cycle - 0) & mask)];
      assert(x2999 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement14/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3000 = args[2][39 * steps + ((cycle - 0) & mask)];
      assert(x3000 != Fp::invalid());
      host_args.at(0) = x2999;
      host_args.at(1) = x3000;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement15/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3001 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x3001 != Fp::invalid());
      // loc("Top/Mux/3/BytesBody/PlonkBody/BytesPlonkElement15/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3002 = args[2][41 * steps + ((cycle - 0) & mask)];
      assert(x3002 != Fp::invalid());
      host_args.at(0) = x3001;
      host_args.at(1) = x3002;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x10 != 0) {
    {
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3003 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3003 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3004 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3004 != Fp::invalid());
      host_args.at(0) = x3003;
      host_args.at(1) = x3004;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3005 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3005 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3006 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3006 != Fp::invalid());
      host_args.at(0) = x3005;
      host_args.at(1) = x3006;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3007 = args[2][14 * steps + ((cycle - 0) & mask)];
      assert(x3007 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement2/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3008 = args[2][15 * steps + ((cycle - 0) & mask)];
      assert(x3008 != Fp::invalid());
      host_args.at(0) = x3007;
      host_args.at(1) = x3008;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3009 = args[2][16 * steps + ((cycle - 0) & mask)];
      assert(x3009 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement3/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3010 = args[2][17 * steps + ((cycle - 0) & mask)];
      assert(x3010 != Fp::invalid());
      host_args.at(0) = x3009;
      host_args.at(1) = x3010;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3011 = args[2][18 * steps + ((cycle - 0) & mask)];
      assert(x3011 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement4/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3012 = args[2][19 * steps + ((cycle - 0) & mask)];
      assert(x3012 != Fp::invalid());
      host_args.at(0) = x3011;
      host_args.at(1) = x3012;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3013 = args[2][20 * steps + ((cycle - 0) & mask)];
      assert(x3013 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement5/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3014 = args[2][21 * steps + ((cycle - 0) & mask)];
      assert(x3014 != Fp::invalid());
      host_args.at(0) = x3013;
      host_args.at(1) = x3014;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3015 = args[2][22 * steps + ((cycle - 0) & mask)];
      assert(x3015 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement6/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3016 = args[2][23 * steps + ((cycle - 0) & mask)];
      assert(x3016 != Fp::invalid());
      host_args.at(0) = x3015;
      host_args.at(1) = x3016;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3017 = args[2][24 * steps + ((cycle - 0) & mask)];
      assert(x3017 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement7/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3018 = args[2][25 * steps + ((cycle - 0) & mask)];
      assert(x3018 != Fp::invalid());
      host_args.at(0) = x3017;
      host_args.at(1) = x3018;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3019 = args[2][26 * steps + ((cycle - 0) & mask)];
      assert(x3019 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement8/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3020 = args[2][27 * steps + ((cycle - 0) & mask)];
      assert(x3020 != Fp::invalid());
      host_args.at(0) = x3019;
      host_args.at(1) = x3020;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement9/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3021 = args[2][28 * steps + ((cycle - 0) & mask)];
      assert(x3021 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement9/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3022 = args[2][29 * steps + ((cycle - 0) & mask)];
      assert(x3022 != Fp::invalid());
      host_args.at(0) = x3021;
      host_args.at(1) = x3022;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement10/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3023 = args[2][30 * steps + ((cycle - 0) & mask)];
      assert(x3023 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement10/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3024 = args[2][31 * steps + ((cycle - 0) & mask)];
      assert(x3024 != Fp::invalid());
      host_args.at(0) = x3023;
      host_args.at(1) = x3024;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement11/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3025 = args[2][32 * steps + ((cycle - 0) & mask)];
      assert(x3025 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement11/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3026 = args[2][33 * steps + ((cycle - 0) & mask)];
      assert(x3026 != Fp::invalid());
      host_args.at(0) = x3025;
      host_args.at(1) = x3026;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement12/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3027 = args[2][34 * steps + ((cycle - 0) & mask)];
      assert(x3027 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement12/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3028 = args[2][35 * steps + ((cycle - 0) & mask)];
      assert(x3028 != Fp::invalid());
      host_args.at(0) = x3027;
      host_args.at(1) = x3028;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement13/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3029 = args[2][36 * steps + ((cycle - 0) & mask)];
      assert(x3029 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement13/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3030 = args[2][37 * steps + ((cycle - 0) & mask)];
      assert(x3030 != Fp::invalid());
      host_args.at(0) = x3029;
      host_args.at(1) = x3030;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement14/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3031 = args[2][38 * steps + ((cycle - 0) & mask)];
      assert(x3031 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement14/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3032 = args[2][39 * steps + ((cycle - 0) & mask)];
      assert(x3032 != Fp::invalid());
      host_args.at(0) = x3031;
      host_args.at(1) = x3032;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement15/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3033 = args[2][40 * steps + ((cycle - 0) & mask)];
      assert(x3033 != Fp::invalid());
      // loc("Top/Mux/4/BytesBody/PlonkBody/BytesPlonkElement15/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3034 = args[2][41 * steps + ((cycle - 0) & mask)];
      assert(x3034 != Fp::invalid());
      host_args.at(0) = x3033;
      host_args.at(1) = x3034;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  if (x11 != 0) {
    {
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3035 = args[2][10 * steps + ((cycle - 0) & mask)];
      assert(x3035 != Fp::invalid());
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3036 = args[2][11 * steps + ((cycle - 0) & mask)];
      assert(x3036 != Fp::invalid());
      host_args.at(0) = x3035;
      host_args.at(1) = x3036;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement1/Reg"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3037 = args[2][12 * steps + ((cycle - 0) & mask)];
      assert(x3037 != Fp::invalid());
      // loc("Top/Mux/5/BytesBody/PlonkBody/BytesPlonkElement1/Reg1"("./cirgen/compiler/edsl/component.h":81:27))
      auto x3038 = args[2][13 * steps + ((cycle - 0) & mask)];
      assert(x3038 != Fp::invalid());
      host_args.at(0) = x3037;
      host_args.at(1) = x3038;
      host(ctx, "plonkWrite", "bytes", host_args.data(), 2, host_outs.data(), 0);
    }
  }
  return x5;
}

} // namespace risc0::circuit::rv32im
// clang-format on
