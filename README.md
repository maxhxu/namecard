# mgnamecard

A C++ utility using Magick++ to generate a stylized digital namecard from an embedded SVG template.

## Prerequisites
- ImageMagick
- A C++20 compile compiler

## Usage
1. Build: `make`
2. Run: `./mgnamecard`
3. Find `namecard.png` in the root directory

## Customization
Edit the following varibles in `src/main.cpp` to customize the card
- svgTemplate
- name
- title
- tagline
- email
- website
