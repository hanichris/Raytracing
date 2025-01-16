#include "../src/headers/canvas.h"

#include "test_main.h"
#include <stdio.h>
#include <string.h>

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

static
void close_file(FILE** fp) {
	if (*fp) {
		fclose(*fp);
	}
}

static
void test_canvas_ppm_header_construction(void) {
	__attribute__((cleanup(canvas_delete)))canvas* c = canvas_new(5, 3);

	char* ppm_filename = canvas_2_ppm(c);
	assert(ppm_filename != NULL);
	__attribute__((cleanup(close_file)))FILE* fp = fopen(ppm_filename, "rb");
	assert(fp != NULL);
	char buffer[32];
	unsigned line = 0;
	while (fgets(buffer, 32, fp)){
		++line;
		switch (line) {
			case 1:
				assert(strcmp(buffer, "P3\n") == 0);
				break;
			case 2: {
					char str[100];
					snprintf(str, 100, "%u %u\n", c->width, c->height);
					assert(strcmp(buffer, str) == 0);
					break;
				}
			case 3: {
					char str[100];
					snprintf(str, 100, "%d\n", MAX_COL_VAL);
					assert(strcmp(buffer, str) == 0);
					break;
				}
			default:
				fseek(fp, 0, SEEK_END);
				break;

		}
	}

	putchar('.');
}

static
void test_canvas_ppm_terminated_by_newline(void) {
	__attribute__((cleanup(canvas_delete)))canvas* c = canvas_new(5, 3);

	char* ppm_filename = canvas_2_ppm(c);
	assert(ppm_filename != NULL);
	__attribute__((cleanup(close_file)))FILE* fp = fopen(ppm_filename, "rb");
	assert(fp != NULL);

	fseek(fp, -1, SEEK_END);
	char l = fgetc(fp);
	assert(l == '\n');
	putchar('.');
}


static
void test_canvas_ppm_pixel_data_construction(void) {
	__attribute__((cleanup(canvas_delete)))canvas* c = canvas_new(5, 3);

	col3* red = COLOUR(1.5f, 0, 0);
	col3* green = COLOUR(0, 0.5, 0);
	col3* blue = COLOUR(-0.5f, 0, 1);

	c = write_pixel(c, 0, 0, red);
	c = write_pixel(c, 2, 1, green);
	c = write_pixel(c, 4, 2, blue);

	char* ppm_filename = canvas_2_ppm(c);
	assert(ppm_filename != NULL);
	__attribute__((cleanup(close_file)))FILE* fp = fopen(ppm_filename, "rb");
	assert(fp != NULL);
	char buffer[32];
	unsigned line = 0;
	while (fgets(buffer, 32, fp)){
		++line;
		switch (line) {
			case 4:
				assert(strcmp(buffer, "255 0 0\n") == 0);
				break;
			case 11: {
					assert(strcmp(buffer, "0 128 0\n") == 0);
					break;
				}
			case 18: {
					assert(strcmp(buffer, "0 0 255") == 0);
					break;
				}
			default:
				fseek(fp, 0, SEEK_END);
				break;

		}
	}

	putchar('.');
}

void run_canvas_tests(void) {
	test_canvas_creation();
	test_canvas_write_pixel();
	test_canvas_ppm_header_construction();
	test_canvas_ppm_terminated_by_newline();
	test_canvas_ppm_pixel_data_construction();
}

