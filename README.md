png2argb
===

A tool written in C to convert PNG image data into Xlib-compatible cardinal argb buffer.

Installation
---
````
make
sudo make install
````

Example usage
---
`png2argb image16.png image32.png > output.argb`

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
