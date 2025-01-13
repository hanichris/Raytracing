#ifndef MY_CANVAS_H
#define MY_CANVAS_H 1

#if __has_c_attribute(__gnu__::__malloc__) && !(defined(__clang_major__) && __clang_major__ <= 19)
# define __gnu_free__(...) __gnu__::__malloc__(__VA_ARGS__)
#else
# define __gnu_free__(...)
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "colour.h"

typedef struct canvas canvas;
struct canvas {
	uint16_t width;
	uint16_t height;
	col3 pixels[];
};
/**
 * canvas_init - initialises a canvas buffer with maximally `w` * `h` pixels.
 * Only use this function on an uninitialised canvas buffer.
 */
static
canvas* canvas_init(canvas *c, uint16_t w, uint16_t h) {
	if (c) {
		c->height = h;
		c->width = w;
		for (uint16_t i = 0; i < (w*h); i++)
			c->pixels[i] = (col3){ };
	}
	return c;
}

/**
 * write_pixel - writes a pixel to the canvas at the specified (x,y) position.
 * @c: pointer to the canvas where the pixel is written to.
 * @x: x-coordinate on the canvas. Goes from left to right.
 * @y: y-coordinate on the canvas. Goes from top to bottom.
 * @colour: pointer to the pixel colour.
 * @Returns: modified canvas or null.
 */
static
canvas* write_pixel(canvas* c, uint16_t x, uint16_t y, col3* colour) {
	if (c && colour) {
		c->pixels[(x * c->width) + y] = *colour;
		return c;
	}
	return nullptr;
}

/**
 * pixel_at - returns the address of the pixel at the given (x, y) position.
 * @c: pointer to the canvas where the pixel of interest will be found.
 * @x: x-coordinate on the canvas. Goes from left to right.
 * @y: y-coordinate on the canvas. Goes from top to bottom.
 * @Returns: pixel's address or null.
 */
static
col3 const* pixel_at(canvas const* c, uint16_t x, uint16_t y) {
	if (c && x < c->width && y < c->height)
		return &c->pixels[(x * c->width) + y];
	return nullptr;
}

/**
 * canvas_delete - delete a canvas buffer `c`. The buffer must have been
 * allocated with a call to `canvas_new`.
 */
static
inline
void canvas_delete(canvas** c) {
	free(*c);
	c = nullptr;
}

[[nodiscard("pointer to allocated canvas dropped.")]]
[[__gnu__::__malloc__, __gnu_free__(canvas_delete)]]
static
inline
canvas* canvas_new(uint16_t w, uint16_t h) {
	size_t size = offsetof(canvas, pixels) + sizeof(col3[w*h]);
	if (size < sizeof(canvas))
		size = sizeof(canvas);
	return canvas_init((canvas*)malloc(size), w, h);
}

#endif
