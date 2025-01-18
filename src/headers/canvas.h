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

#define MAX_COL_VAL 255

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
canvas* canvas_init(canvas *c, uint16_t w, uint16_t h);

/**
 * write_pixel - writes a pixel to the canvas at the specified (x,y) position.
 * @c: pointer to the canvas where the pixel is written to.
 * @x: x-coordinate on the canvas. Goes from left to right.
 * @y: y-coordinate on the canvas. Goes from top to bottom.
 * @colour: pointer to the pixel colour.
 * @Returns: modified canvas or null.
 */
canvas* write_pixel(canvas* c, uint16_t x, uint16_t y, col3* colour);

/**
 * pixel_at - returns the address of the pixel at the given (x, y) position.
 * @c: pointer to the canvas where the pixel of interest will be found.
 * @x: x-coordinate on the canvas. Goes from left to right.
 * @y: y-coordinate on the canvas. Goes from top to bottom.
 * @Returns: pixel's address or null.
 */
col3 const* pixel_at(canvas const* c, uint16_t x, uint16_t y);

/**
 * canvas_2_ppm - generates a string representation of the canvas
 * that will be written out to a file with the ppm format.
 * @c: pointer to the canvas.
 * @Returns: string buffer holding the canvas information.
 * Otherwise, null if the string buffer could not be allocated.
 */
char* canvas_2_ppm(canvas* c);

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
	return canvas_init((canvas*)calloc(1, size), w, h);
}

#endif
