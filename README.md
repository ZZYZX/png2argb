# png2argb
A tool to convert PNG image data into Xlib-compatible cardinal ARGB buffer.  
It basically lets you embed raw image resources into your X11 programs.  
Can be used as the data parameter to `XChangeProperty()`. See the example program for reference.

## Dependencies
Requires `libpng-dev` to compile, `libpng` to work.

## Installation
    make clean all
    sudo make install

## Example usage
    png2argb image16.png image32.png > buffer.h

## Output
    unsigned long buffer[] = {
        16, 16,
        0, 0, 0, 0, [...],

        32, 32,
        0, 0, 0, 0, 0, 0, 0, 0, [...],
    };
