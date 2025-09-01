# PalmyraFM

## Overview

PalmyraFM is a simple, two-pane file manager for Linux and macOS that has been developed using Qt6 libraries. It provides an intuitive dual-pane interface for efficient file management operations.

## Files Structure

### Qt6 Project Files

- `palmyrafm.pro` - Qt project file
- `main.cpp` - application entry point
- `palmyrafm.h/cpp` - main window implementation
- `dirview.cpp` - directory tree view implementation

### Distribution Files

- `palmyrafm.desktop` - Linux desktop entry file
- `icons/palmyrafm.svg` - Application icon (SVG source)
- `icons/palmyrafm.png` - Application icon (512x512 PNG, included)
- `icons/palmyrafm.icns` - macOS application icon (included)
- `icons/palmyrafm-*.png` - Additional PNG sizes (16, 32, 48, 128, 256px)
- `README.md` - this documentation
- `LICENSE` - GPL v3.0 license
- `NOTICE` - third-party software notices (Qt attribution)

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

### Linux Build Instructions

#### Install Dependencies

**Ubuntu/Debian:**

```bash
# Update package list
sudo apt update

# Install Qt6 development packages
sudo apt install qt6-base-dev qt6-tools-dev qt6-tools-dev-tools

# Install additional Qt6 modules (if needed)
sudo apt install qt6-declarative-dev qt6-multimedia-dev

# Install build tools
sudo apt install build-essential cmake
```

**Fedora/RHEL/CentOS:**

```bash
# Install Qt6 development packages
sudo dnf install qt6-qtbase-devel qt6-qttools-devel

# Install build tools
sudo dnf install gcc-c++ make cmake

# For older versions, use yum instead of dnf
```

**Arch Linux:**

```bash
# Install Qt6 packages
sudo pacman -S qt6-base qt6-tools

# Install build tools (usually already installed)
sudo pacman -S base-devel cmake
```

**openSUSE:**

```bash
# Install Qt6 development packages
sudo zypper install qt6-base-devel qt6-tools-devel

# Install build tools
sudo zypper install gcc-c++ make cmake
```

#### Build Commands

```bash
# Clone the repository (if not already done)
git clone https://github.com/nagornyi/palmyrafm.git
cd palmyrafm

# Generate icon (optional - PNG files included in repository)
# The commented steps are only needed if you want to regenerate the icon:
# sudo apt install inkscape  # Ubuntu/Debian
# sudo dnf install inkscape  # Fedora
# sudo zypper install inkscape  # openSUSE
# inkscape icons/palmyrafm.svg --export-png=icons/palmyrafm.png --export-width=512 --export-height=512

# Generate Makefile using system Qt6
qmake palmyrafm.pro
# Alternative: use full path if qmake is not in PATH
# /usr/lib/qt6/bin/qmake palmyrafm.pro

# Build the application
make

# Run the application
./palmyrafm
```

#### Installation (Optional)

```bash
# Install to system (requires sudo)
sudo make install

# Or install to custom prefix
qmake PREFIX=/usr/local palmyrafm.pro
make
sudo make install

# Uninstall the application
sudo make uninstall
```

#### Troubleshooting Linux Build

**Qt6 not found:**

```bash
# Find Qt6 installation
find /usr -name "qmake*" 2>/dev/null | grep qt6

# Set Qt6 path explicitly
export PATH="/usr/lib/qt6/bin:$PATH"
```

**Missing dependencies:**

```bash
# Check for missing Qt6 modules
ldd ./palmyrafm

# Install additional Qt6 packages as needed
sudo apt install qt6-*-dev  # Ubuntu/Debian
sudo dnf install qt6-*-devel # Fedora
```

**Build errors:**

```bash
# Clean build
make clean
make distclean

# Regenerate Makefile
qmake palmyrafm.pro
make
```

#### Creating Portable AppImage (Advanced)

```bash
# Install linuxdeploy and qt plugin
wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
wget https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage
chmod +x linuxdeploy*.AppImage

# Create AppDir structure
mkdir -p AppDir/usr/bin
mkdir -p AppDir/usr/share/icons/hicolor/512x512/apps
cp palmyrafm AppDir/usr/bin/
cp palmyrafm.desktop AppDir/
cp icons/palmyrafm.png AppDir/usr/share/icons/hicolor/512x512/apps/

# Create AppImage
./linuxdeploy-x86_64.AppImage --appdir AppDir --plugin qt --output appimage

# Result: PalmyraFM-x86_64.AppImage (portable, runs on most Linux distros)
```

### macOS Build Instructions

#### Install Dependencies (using MacPorts)

```bash
# Install MacPorts if not already installed
# Download from: https://www.macports.org/install.php

# Update MacPorts
sudo port selfupdate

# Install Qt6 (includes qtbase and qttools)
sudo port install qt6 +universal

# Set up Qt6 environment (add to ~/.zshrc for permanent setup)
export PATH=/opt/local/libexec/qt6/bin:$PATH
```

#### Alternative: Using Homebrew

```bash
# Install Qt6 via Homebrew
brew install qt@6

# Add Qt6 to PATH
export PATH="/opt/homebrew/opt/qt@6/bin:$PATH"
```

#### Build Commands

```bash
# Generate icon (optional - PNG and ICNS files included in repository)
# The commented steps are only needed if you want to regenerate the icons:
# brew install inkscape  # macOS with Homebrew
# or: sudo port install inkscape +universal  # macOS with MacPorts
# inkscape icons/palmyrafm.svg --export-png=icons/palmyrafm.png --export-width=512 --export-height=512

# Create .icns icon (optional, ICNS file already included)
# make icns

# Generate Makefile using Qt6 qmake
qmake palmyrafm.pro

# Build
make

# Run
./palmyrafm.app/Contents/MacOS/palmyrafm

# Or create .app bundle and run
open palmyrafm.app
```

#### Installation (Optional)

```bash
# Install to Applications folder
sudo make install

# This copies palmyrafm.app to /Applications/
# The app will then be available in Launchpad and Applications folder

# Uninstall the application (removes completely)
sudo make uninstall
```

**Note:** On macOS, the installation process only installs the app bundle to `/Applications/`. Desktop entries are not used on macOS as they are on Linux systems. The app will appear in Launchpad and the Applications folder after installation. The uninstall process cleanly removes only the application without affecting system directories.

#### Build Notes for macOS

- The application builds as `palmyrafm.app` bundle on macOS
- Ensure Xcode Command Line Tools are installed: `xcode-select --install`
- For universal binaries, use the `+universal` variant with MacPorts
- Qt6 on macOS requires macOS 10.15 (Catalina) or later
- The `make icns` command creates a proper macOS icon from the PNG
- Installation copies the app bundle to `/Applications/`

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

## Platform Compatibility

### Supported Platforms

- **Linux**: Primary development platform
- **macOS**: 10.15 (Catalina) or later with Qt6 support

### Platform-Specific Notes

- **Linux**: Uses system Qt6 packages, typically found in `/usr/lib/qt6/`
- **macOS**: Builds as `.app` bundle, requires Xcode Command Line Tools
- **Windows**: Should work with Qt6 for Windows (not tested)

## License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for details.

### Qt Framework License

This application uses the Qt framework under the GNU Lesser General Public License (LGPL) v3. Qt is a cross-platform application framework developed by The Qt Company.

- **Qt Source Code**: Available at [qt.io/download-open-source](https://www.qt.io/download-open-source)
- **Qt Licensing Information**: [doc.qt.io/qt-6/licensing.html](https://doc.qt.io/qt-6/licensing.html)
- **LGPL v3 License**: [gnu.org/licenses/lgpl-3.0.html](https://www.gnu.org/licenses/lgpl-3.0.html)

### Attribution

- Qt Framework © The Qt Company Ltd
- PalmyraFM © Artem Nagornyi, 2025
