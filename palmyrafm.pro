QT += core widgets gui concurrent

TARGET = palmyrafm
TEMPLATE = app

CONFIG += c++17

HEADERS = palmyrafm.h

SOURCES = main.cpp \
          palmyrafm.cpp \
          dirview.cpp

RESOURCES = palmyrafm.qrc

# Installation targets for Linux/Unix (excluding macOS)
unix:!macx {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    
    # Don't use default INSTALLS mechanism to avoid directory cleanup issues
    # Instead, implement custom install/uninstall targets
    
    # Custom install target
    install.target = install
    install.commands = \
        /usr/lib/qt6/bin/qmake -install qinstall -exe palmyrafm $$PREFIX/bin/palmyrafm && \
        strip $$PREFIX/bin/palmyrafm && \
        /usr/lib/qt6/bin/qmake -install qinstall palmyrafm.desktop /usr/share/applications/palmyrafm.desktop && \
        /usr/lib/qt6/bin/qmake -install qinstall icons/palmyrafm.png /usr/share/pixmaps/palmyrafm.png
    install.CONFIG += phony
    
    # Custom uninstall target
    uninstall.target = uninstall
    uninstall.commands = \
        rm -f $$PREFIX/bin/palmyrafm && \
        rm -f /usr/share/applications/palmyrafm.desktop && \
        rm -f /usr/share/pixmaps/palmyrafm.png
    uninstall.CONFIG += phony
    
    QMAKE_EXTRA_TARGETS += install uninstall
}

# macOS specific settings
macx {
    QMAKE_INFO_PLIST = Info.plist
    
    # App bundle configuration
    ICON = icons/palmyrafm.icns
    
    # Installation targets for macOS - custom implementation
    isEmpty(PREFIX) {
        PREFIX = /Applications
    }
    
    # Don't use default INSTALLS mechanism to avoid directory cleanup issues
    # Instead, implement custom install/uninstall targets
    
    # Custom install target
    install.target = install
    install.commands = rm -rf $$PREFIX/palmyrafm.app && \
                      /opt/local/libexec/qt6/bin/qmake -install qinstall palmyrafm.app $$PREFIX/palmyrafm.app && \
                      strip $$PREFIX/palmyrafm.app/Contents/MacOS/palmyrafm
    install.CONFIG += phony
    
    # Custom uninstall target
    uninstall.target = uninstall
    uninstall.commands = rm -rf $$PREFIX/palmyrafm.app
    uninstall.CONFIG += phony
    
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
    
    QMAKE_EXTRA_TARGETS += icns install uninstall
}
