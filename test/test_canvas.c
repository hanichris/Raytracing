#include "../src/headers/canvas.h"

#include "test_main.h"

#define EPSILON 1E-5

static
bool float_equal(float x, float y) {
	return fabsf(x - y) < EPSILON;
}

static
void test_canvas_creation(void) {
	__attribute__((cleanup(canvas_delete)))canvas* c = canvas_new(10, 20);

	assert(c->height == 20);
	assert(c->width == 10);
	assert(c->height == 20);

	for (uint16_t i = 0; i < (10 * 20); i++){
		col3* colour = &c->pixels[i];
		assert(float_equal(colour->blue, 0.0f));
		assert(float_equal(colour->green, 0.0f));
		assert(float_equal(colour->red, 0.0f));

	}
	putchar('.');

}

static
void test_canvas_write_pixel(void) {
	__attribute__((cleanup(canvas_delete)))canvas* c = canvas_new(10, 20);
	col3* red = COLOUR(1.0f, 0.0f, 0.0f);

	c = write_pixel(c, 2, 3, red);

	assert(c != NULL);
	col3 const* out = pixel_at(c, 2, 3);

	assert(out != NULL);
	assert(float_equal(out->blue, 0.0f));
	assert(float_equal(out->green, 0.0f));
	assert(float_equal(out->red, 1.0f));
	
	putchar('.');
}


void run_canvas_tests(void) {
	test_canvas_creation();
	test_canvas_write_pixel();
}
