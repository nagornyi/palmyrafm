# Icon Generation Instructions

**Note: Pre-generated PNG and ICNS files are included in the repository for convenience. You only need to regenerate them if you modify the SVG source.**

## Included Files

- `palmyrafm.svg` - Vector source (Palmyra ruins design)
- `palmyrafm.png` - Main icon (512x512px)
- `palmyrafm.icns` - macOS app icon
- `palmyrafm-16.png` through `palmyrafm-256.png` - Various sizes

## SVG to PNG Conversion

To create PNG icons from the SVG source, use one of these methods:

### Method 1: Using Inkscape (Recommended)
```bash
# Install Inkscape
sudo apt install inkscape  # Ubuntu/Debian
sudo dnf install inkscape  # Fedora
brew install inkscape      # macOS

# Convert to different sizes
inkscape icons/palmyrafm.svg --export-png=icons/palmyrafm-16.png --export-width=16 --export-height=16
inkscape icons/palmyrafm.svg --export-png=icons/palmyrafm-32.png --export-width=32 --export-height=32
inkscape icons/palmyrafm.svg --export-png=icons/palmyrafm-48.png --export-width=48 --export-height=48
inkscape icons/palmyrafm.svg --export-png=icons/palmyrafm-128.png --export-width=128 --export-height=128

# Create the main icon (64x64 is standard for desktop entries)
inkscape icons/palmyrafm.svg --export-png=icons/palmyrafm.png --export-width=64 --export-height=64
```

### Method 2: Using ImageMagick
```bash
# Install ImageMagick
sudo apt install imagemagick  # Ubuntu/Debian
sudo dnf install ImageMagick  # Fedora
brew install imagemagick      # macOS

# Convert to PNG
convert icons/palmyrafm.svg -resize 64x64 icons/palmyrafm.png
```

### Method 3: Using rsvg-convert
```bash
# Install librsvg
sudo apt install librsvg2-bin  # Ubuntu/Debian

# Convert to PNG
rsvg-convert -w 64 -h 64 icons/palmyrafm.svg > icons/palmyrafm.png
```

## Icon Description

The icon represents:
- **Ancient Palmyra ruins**: Stylized columns and archway
- **Desert setting**: Sandy background with sun
- **File manager context**: Small folder icon overlay
- **Color scheme**: Desert tones (beige, brown, blue accents)

The design is simple, scalable, and recognizable at small sizes typical for desktop environments.
