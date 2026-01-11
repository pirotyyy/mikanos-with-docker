# MikanOS
## What is MikanOS

A minimal x86-64 operating system written in C/C++.

## Current Features

<img width="816" height="616" alt="スクリーンショット 2026-01-12 0 51 56" src="https://github.com/user-attachments/assets/5eadb8a6-fc1c-4bce-9aec-7b5afdc2feae" />

- Memory management is under development and not complete.

- **UEFI Boot Loader** - Loads kernel ELF, prepares frame buffer and memory map
- **Graphics & Console** - Pixel drawing, font rendering, text console with logging
- **Interrupt Handling** - IDT setup with queue-based event processing
- **PCI Device Support** - PCI device enumeration and MSI configuration
- **USB Stack** - xHCI controller driver with HID keyboard/mouse support
- **Mouse Cursor** - Interactive mouse pointer with USB mouse input
