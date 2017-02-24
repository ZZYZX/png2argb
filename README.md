# png2argb
A tool written in C to convert PNG image data into Xlib-compatible cardinal argb buffer.  
Can be used as the data parameter to `XChangeProperty()` like so:
    ...
    Atom net_wm_icon = XInternAtom(window.dpy, "_NET_WM_ICON", False);
    Atom cardinal = XInternAtom(window.dpy, "CARDINAL", False);
    unsigned int length = 2 + 16 * 16 + 2 + 32 * 32; // Or whatever it is you get in your image buffer
    XChangeProperty(window.dpy, window.win, net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*)buffer, length);
    ...

### Installation
    make clean all
    sudo make install

(requires libpng-dev to compile, libpng to work)

### Example usage
 - `png2argb image16.png image32.png > argb-buffers.h`
 - `cat image.png | png2argb > argb-buffer.h`
 - `cat image.png | png2argb image2.png > argb-buffers.h`

### Output
    unsigned long buffer[] = {
        16, 16,
        0, 0, 0, 0, [...],

        32, 32,
        0, 0, 0, 0, 0, 0, 0, 0, [...],
    };
