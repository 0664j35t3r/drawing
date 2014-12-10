#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
  size_t         width;
  size_t         height;
  unsigned char *data;
} Image;

static Image *
image_new (size_t width,
           size_t height)
{
  Image *image;

  image = malloc (sizeof *image);
  image->width = width;
  image->height = height;
  image->data = malloc (width * height);

  return image;
}

static void
image_free (Image *image)
{
  free (image->data);
  free (image);
}

static void
image_fill (Image         *image,
            unsigned char  value)
{
  memset (image->data, value, image->width * image->height);
}

/**
 * image_set_pixel:
 *
 * Sets a pixel passed in signed (x, y) coordinates, where (0,0) is at
 * the center of the image.
 **/
static void
image_set_pixel (Image         *image,
                 ssize_t        x,
                 ssize_t        y,
                 unsigned char  value)
{
  size_t tx, ty;
  unsigned char *p;

  tx = (image->width / 2) + x;
  ty = (image->height / 2) + y;

  p = image->data + (ty * image->width) + tx;

  *p = value;
}

static void
image_save (const Image *image,
            const char  *filename)
{
  FILE *out;

  out = fopen (filename, "wb");
  if (!out)
    return;

  fprintf (out, "P5\n");
  fprintf (out, "%zu %zu\n", image->width, image->height);
  fprintf (out, "255\n");

  fwrite (image->data, 1, image->width * image->height, out);

  fclose (out);
}

static void
draw_circle (Image         *image,
             int            radius,
             unsigned char  value)
{
  int x, y;
  int l;
  int r2, y2;
  int y2_new;
  int ty;

  /* cos pi/4 = 185363 / 2^18 (approx) */
  l = (radius * 185363) >> 18;

  /* At x=0, y=radius */
  y = radius;

  r2 = y2 = y * y;
  ty = (2 * y) - 1;
  y2_new = r2 + 3;

  for (x = 0; x <= l; x++) {
    y2_new -= (2 * x) - 3;

    if ((y2 - y2_new) >= ty) {
      y2 -= ty;
      y -= 1;
      ty -= 2;
    }

    image_set_pixel (image, x, y, value);
    image_set_pixel (image, x, -y, value);
    image_set_pixel (image, -x, y, value);
    image_set_pixel (image, -x, -y, value);

    image_set_pixel (image, y, x, value);
    image_set_pixel (image, y, -x, value);
    image_set_pixel (image, -y, x, value);
    image_set_pixel (image, -y, -x, value);
  }
}

int
main (int argc, char *argv[])
{
  Image *image;

  image = image_new (600, 600);

  image_fill (image, 0xff);
  draw_circle (image, 200, 0);
  image_save (image, "circle.pgm");

  image_free (image);

  return 0;
}
