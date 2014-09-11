#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define PNG_DEBUG 3
#include <png.h>

int argb(int a, int r, int g, int b)
{
  int argb = a;
  argb = (argb << 8) + r;
  argb = (argb << 8) + g;
  argb = (argb << 8) + b;
  return argb;
}

void __exit(const char *s, ...)
{
  va_list args;
  va_start(args, s);
  vfprintf(stderr, s, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(1);
}

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep *row_pointers;

void read_png_file(char *file_name)
{
  char header[8];    // 8 is the maximum size that can be checked

  /* open file and test for it being a png */
  FILE *fp = fopen(file_name, "rb");
  if (!fp) {
    __exit("[read_png_file] File %s could not be opened for reading", file_name);
  }

  fread(header, 1, 8, fp);
  if (png_sig_cmp(header, 0, 8)) {
    __exit("[read_png_file] File %s is not recognized as a PNG file", file_name);
  }


  /* initialize stuff */
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr) {
    __exit("[read_png_file] png_create_read_struct failed");
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    __exit("[read_png_file] png_create_info_struct failed");
  }

  if (setjmp(png_jmpbuf(png_ptr))) {
    __exit("[read_png_file] Error during init_io");
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);


  /* read file */
  if (setjmp(png_jmpbuf(png_ptr))) {
    __exit("[read_png_file] Error during read_image");
  }

  row_pointers = (png_bytep*) malloc(sizeof(png_bytep) *height);
  for (y=0; y<height; y++) {
    row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
  }

  png_read_image(png_ptr, row_pointers);

  fclose(fp);
}


void process_file(void)
{
  int file_color_type = png_get_color_type(png_ptr, info_ptr);

  if (file_color_type != PNG_COLOR_TYPE_RGB &&
      file_color_type != PNG_COLOR_TYPE_RGBA) {
    __exit("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGB (%d) "
           "or PNG_COLOR_TYPE_RGBA (%d), (is %d)",
           PNG_COLOR_TYPE_RGB, PNG_COLOR_TYPE_RGBA, png_get_color_type(png_ptr, info_ptr));
  }

  printf("\n\t%d, %d,\n\t", width, height);

  for (y = 0; y < height; y++) {
    png_byte *row = row_pointers[y];
    for (x = 0; x < width; x++) {
      if (file_color_type == PNG_COLOR_TYPE_RGBA) { // RGBA
        png_byte *ptr = &(row[x*4]);
        printf("%d, ", argb(ptr[3], ptr[0], ptr[1], ptr[2]));
      } else { // RGB
        png_byte *ptr = &(row[x*3]);
        printf("%d, ", argb(255, ptr[0], ptr[1], ptr[2]));
      }

      /* set red value to 0 and green value to the blue one */
      ptr[0] = 0;
      ptr[1] = ptr[2];
    }
  }

  printf("\n");
}


void main(int argc, char **argv)
{
  if (argc < 2) {
    __exit("Usage: png2argb image.png [image2.png [image3.png [...]]] > output.argb\n");
  }

  printf("unsigned long buffer[] = {");

  int l = 1;
  for ( ; l < argc; ) {
    read_png_file(argv[l++]);
    process_file();
  }

  printf("};\n");
}

