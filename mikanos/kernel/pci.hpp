#pragma once

#include <cstdint>
#include <array>

#include "error.hpp"

namespace pci {
  // CONFIG_ADDRESS register IO port address
  const uint16_t kConfigAddress = 0x0cf8;
  // CONFIG_DATA register IO port address
  const uint16_t kConfigData = 0x0cfc;

  // write address in CONFIG_ADDRESS
  void WriteAddress(uint32_t address);
  // write value in CONFIG_DATA
  void WriteData(uint32_t value);
  // read 32bit decimal data from CONFIG_DATA
  uint32_t ReadData();

  // read vender id
  uint16_t ReadVendorId(uint8_t bus, uint8_t device, uint8_t function);
  // read device id
  uint16_t ReadDeviceId(uint8_t bus, uint8_t device, uint8_t function);
  // read header type
  uint8_t ReadHeaderType(uint8_t bus, uint8_t device, uint8_t function);
  // read class code
  uint32_t ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);
  // read bus numbers
  uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);

  bool IsSingleFunctionDevice(uint8_t header_type);

  struct Device {
    uint8_t bus, device, function, header_type;
  };

  inline std::array<Device, 32> devices;
  inline int num_device;

  // scan all PCI device and save in devices.
  Error ScanAllBus();
}