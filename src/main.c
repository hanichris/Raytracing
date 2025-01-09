#include <stdio.h>

#include "headers/colour.h"

int main(void) {
	// Image.
	unsigned image_width = 256;
	unsigned image_height = 256;

	// Render. Use PPM Image format
	printf("P3\n%u %u\n255\n", image_width, image_height);

	for (unsigned i = 0; i < image_height; i++) {
		fprintf(stderr, "\rScanlines remaining: %u ", (image_height - i));
		fflush(stderr);
		for (unsigned j = 0; j < image_width; j++) {
			print_colour(&(colour){
				.x = (double)j / (image_width - 1),
				.y = (double)i / (image_width - 1),
				.z = 0,
			});
		}
	}
	fprintf(stderr, "\rDone.                   \n");

	return 0;
}
