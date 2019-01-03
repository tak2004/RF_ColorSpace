# Radon framework Color space
This project provide the most common color spaces, converter, interpolation, processing and util functions.

## Features
- [x] Color gradient support.
- [x] Interpolation between two colors of the same color space.
- [x] Conversion between RGB and an other color space.
- [ ] Color space specific interpolation options(short/long path for Hue based).
- [ ] Brighter and darker color of a specified color.
- [ ] RGB Workspace support.
- [ ] Gamma correction.
- [ ] Reference white conversion.
- [ ] Detect used color space.
- [ ] Detect used RGB Workspace.
- [ ] Batch processing of color values.
- [ ] SIMD support.

## Supported color spaces
- [x] RGB color space.
- [x] XYZ color space.
- [x] LAB color space.
- [x] HSV color space.
- [x] HSL color space.
- [x] LCH color space.
- [x] HWB color space.

## RGB Workspace
- [ ] Lab Gamut
- [ ] Adobe RGB
- [ ] Apple RGB
- [ ] CIE RGB
- [ ] NTSC RGB
- [ ] PAL/SECAM RGB
- [x] sRGB

## Batch processing of color values
- [ ] Concurrency support.
### Read and write
- [ ] Clamp
- [ ] Saturate
- [ ] Brightness
- [ ] Hue
- [ ] Invert
- [ ] Lambda expression
### Read but write to seperate buffers
- [ ] Resize
- [ ] Lambda expression
### Read only
- [ ] Max
- [ ] Min
- [ ] Average
- [ ] Color count
- [ ] Lambda expression

## Todo
- [ ] merge the hue based interpolation in one function, to reduce the code
- [ ] add to Gradient a cache for the picking of the nearest colors

http://www.brucelindbloom.com/index.html?WorkingSpaceInfo.html