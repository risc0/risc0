#pragma once

namespace risc0 {

constexpr size_t kGPIO_SHA = 0x001C0000;
constexpr size_t kGPIO_Read = 0x001C0004;
constexpr size_t kGPIO_Write = 0x001C0008;
constexpr size_t kGPIO_Fault = 0x001C000C;
constexpr size_t kGPIO_Log = 0x001C0010;
constexpr size_t kGPIO_GetKey = 0x001C0014;

struct IoDescriptor {
  uint32_t size;
  uint32_t addr;
};

struct FaultDescriptor {
  uint32_t addr;
};

struct GetKeyDescriptor {
  uint32_t name;
  uint32_t addr;
  uint32_t mode;
};

static volatile IoDescriptor* volatile* GPIO_Read =
    reinterpret_cast<volatile IoDescriptor* volatile*>(kGPIO_Read);

static volatile IoDescriptor* volatile* GPIO_Write =
    reinterpret_cast<volatile IoDescriptor* volatile*>(kGPIO_Write);

static volatile FaultDescriptor* volatile* GPIO_Fault =
    reinterpret_cast<volatile FaultDescriptor* volatile*>(kGPIO_Fault);

static volatile IoDescriptor* volatile* GPIO_Log =
    reinterpret_cast<volatile IoDescriptor* volatile*>(kGPIO_Log);

static volatile GetKeyDescriptor* volatile* GPIO_GetKey =
    reinterpret_cast<volatile GetKeyDescriptor* volatile*>(kGPIO_GetKey);

} // namespace risc0
