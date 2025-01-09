#include <stdio.h>

#include "headers/colour.h"


void print_colour(colour *c) {
	if (c) {
		double r = c->x;
		double g = c->y;
		double b = c->z;

		int ir = (int)(255.999 * r);
		int ig = (int)(255.999 * g);
		int ib = (int)(255.999 * b);

		printf("%d %d %d\n", ir, ig, ib);
	}
}
