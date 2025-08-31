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

## Features

### Core Functionality
- **Dual-pane interface** with directory tree and file list
- **Complete file operations**: copy, cut, paste, delete, new folder
- **Progress dialogs** for long-running operations
- **Native Qt6 APIs** for reliable file handling

### Keyboard Shortcuts
- **Backspace**: Go up directory
- **Enter**: Enter directory or open file
- **F7**: Create new directory
- **F8 / Shift+Delete**: Delete selected files
- **Ctrl+C**: Copy files
- **Ctrl+X**: Cut files  
- **Ctrl+V / Shift+Insert**: Paste files
- **F1**: About dialog (includes key bindings reference)
- **F10**: Exit application
