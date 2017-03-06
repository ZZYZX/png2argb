#include <stdlib.h>
#include <X11/Xlib.h>

#include "buffer.h"

int main(void)
{
    Display *display = XOpenDisplay(0);
    int screen = DefaultScreen(display);
    Window window = XCreateWindow(display, RootWindow(display, screen), 0, 0, 200, 200, 0, CopyFromParent, InputOutput, CopyFromParent, 0, 0);
    Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);
    Atom cardinal = XInternAtom(display, "CARDINAL", False);

    int length = 2 + 16 * 16 + 2 + 32 * 32;

    XChangeProperty(display, window, net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char *)buffer, length);
    XMapWindow(display, window);

    XNextEvent(display, NULL);

    return 0;
}
