#include <math.h>
#include <stdio.h>

#include "headers/canvas.h"

canvas* canvas_init(canvas *c, uint16_t w, uint16_t h) {
	if (c) {
		c->height = h;
		c->width = w;
		for (uint16_t i = 0; i < (w*h); i++)
			c->pixels[i] = (col3){ };
	}
	return c;
}

canvas* write_pixel(canvas* c, uint16_t x, uint16_t y, col3* colour) {
	if (c && colour) {
		c->pixels[(y * c->width) + x] = *colour;
		return c;
	}
	return nullptr;
}

col3 const* pixel_at(canvas const* c, uint16_t x, uint16_t y) {
	if (c && x < c->width && y < c->height)
		return &c->pixels[(y * c->width) + x];
	return nullptr;
}

static
float clamp(float const x) {
	float tmp = x < 0 ? 0: x;
	return tmp > MAX_COL_VAL ? MAX_COL_VAL : tmp;
}

static
void write_colour(FILE* fp, col3 const* pixel_colour) {
	if (fp && pixel_colour) {
		float r = ceilf(pixel_colour->red * MAX_COL_VAL);
		float g = ceilf(pixel_colour->green * MAX_COL_VAL);
		float b = ceilf(pixel_colour->blue * MAX_COL_VAL);

		r = clamp(r);
		g = clamp(g);
		b = clamp(b);

		fprintf(fp, "%g %g %g\n", r, g, b);
	}
}

char* canvas_2_ppm(canvas *c) {
	char* filename = nullptr;
	if (c) {
		FILE* fp = fopen("image.ppm", "wb");
		if (!fp) {
			perror("Unable to open `image.ppm`");
			return filename;
		}

		filename = "image.ppm";
		fprintf(fp, "P3\n%u %u\n%d\n", c->width, c->height, MAX_COL_VAL);
		for (uint16_t i = 0; i < c->height; ++i) {
			fprintf(stderr, "\rScanlines remaining: %u ", (c->height - i));
			fflush(stderr);
			for (uint16_t j = 0; j < c->width; ++j) {
				write_colour(fp, pixel_at(c, j, i));
			}
		}
		fclose(fp);

		fprintf(stderr, "\rDONE.                       \n");
	}
	return filename;
}

