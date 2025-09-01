QT += core widgets gui concurrent

TARGET = palmyrafm
TEMPLATE = app

CONFIG += c++17

HEADERS = palmyrafm.h

SOURCES = main.cpp \
          palmyrafm.cpp \
          dirview.cpp

# Installation targets for Linux/Unix
unix {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    
    target.path = $$PREFIX/bin
    desktop.path = /usr/share/applications
    desktop.files = palmyrafm.desktop
    icon.path = /usr/share/pixmaps
    icon.files = icons/palmyrafm.png
    
    INSTALLS += target desktop icon
    
    # Uninstall target
    uninstall.commands = rm -f $$PREFIX/bin/palmyrafm && rm -f /usr/share/applications/palmyrafm.desktop && rm -f /usr/share/pixmaps/palmyrafm.png
    QMAKE_EXTRA_TARGETS += uninstall
}

# macOS specific settings
macx {
    QMAKE_INFO_PLIST = Info.plist
    
    # App bundle configuration
    ICON = icons/palmyrafm.icns
    
    # Installation targets for macOS
    isEmpty(PREFIX) {
        PREFIX = /Applications
    }
    
    target.path = $$PREFIX
    INSTALLS += target
    
    # Create .icns from PNG (requires iconutil)
    icns.commands = mkdir -p palmyrafm.iconset && \
                   sips -z 16 16 icons/palmyrafm.png --out palmyrafm.iconset/icon_16x16.png && \
                   sips -z 32 32 icons/palmyrafm.png --out palmyrafm.iconset/icon_16x16@2x.png && \
                   sips -z 32 32 icons/palmyrafm.png --out palmyrafm.iconset/icon_32x32.png && \
                   sips -z 64 64 icons/palmyrafm.png --out palmyrafm.iconset/icon_32x32@2x.png && \
                   sips -z 128 128 icons/palmyrafm.png --out palmyrafm.iconset/icon_128x128.png && \
                   sips -z 256 256 icons/palmyrafm.png --out palmyrafm.iconset/icon_128x128@2x.png && \
                   sips -z 256 256 icons/palmyrafm.png --out palmyrafm.iconset/icon_256x256.png && \
                   sips -z 512 512 icons/palmyrafm.png --out palmyrafm.iconset/icon_256x256@2x.png && \
                   sips -z 512 512 icons/palmyrafm.png --out palmyrafm.iconset/icon_512x512.png && \
                   iconutil -c icns palmyrafm.iconset -o icons/palmyrafm.icns && \
                   rm -rf palmyrafm.iconset
    
    # Uninstall target for macOS
    uninstall.commands = rm -rf $$PREFIX/palmyrafm.app
    
    QMAKE_EXTRA_TARGETS += icns uninstall
}
