png2argb
===

A tool written in C to convert PNG image data into Xlib-compatible cardinal argb buffer.

Installation
---
````
make clean all
sudo make install
````
(requires libpng-dev to compile, libpng to work)

Example usage
---
```
    png2argb image16.png image32.png > buffer.argb
or: cat image.png | png2argb > buffer.argb
or: cat image.png | png2argb image2.png > buffer.argb
```

Output
---
````
unsigned long buffer[] = {
	16, 16,
	0, 0, 0, 0, [...],

	32, 32,
	0, 0, 0, 0, 0, 0, 0, 0, [...],
};
````
