# PalmyraFM

## Overview

PalmyraFM is a simple, two-pane file manager for Linux that has been developed using QT6 libraries.

## Files Structure

### Qt6 Project Files
- `palmyrafm.pro` - project file
- `main.cpp` - main file
- `palmyrafm.h/cpp` - main implementation
- `dirview.cpp` - directory tree view implementation

## Project Configuration

```qmake
# Qt6 project file
QT += core widgets gui concurrent
CONFIG += c++17
TARGET = palmyrafm
```

## Building

### Prerequisites
- Qt6 development packages
- C++17 compiler
- qmake

### Build Commands
```bash
# Generate Makefile
/usr/lib/qt6/bin/qmake palmyrafm.pro

# Build
make

# Run (requires display)
./palmyrafm
```
