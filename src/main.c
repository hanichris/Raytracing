#include <assert.h>
#include <stdio.h>

#include "headers/canvas.h"
#include "headers/vec3.h"

typedef struct projectile projectile;
struct projectile {
	point3 *position;
	vec3 *velocity;
};

typedef struct environ environ;
struct environ {
	vec3 *gravity;
	vec3 *wind;
};

projectile *tick(environ const* env, projectile* proj) {
	if (env && proj) {
		*proj->position = *VEC3_ADD(proj->velocity, proj->position);
		*proj->velocity = *VEC3_ADD(VEC3_ADD(proj->velocity, env->gravity), env->wind);
		return proj;
	}
	return nullptr;
}

int main(void) {
	__attribute__((cleanup(canvas_delete))) canvas *c = canvas_new(900, 550);
	if (!c) {
		perror("Unable to allocate memory for the canvas.");
		return EXIT_FAILURE;
	}

	projectile p = {
		.position = POINT(0, 1, 0),
		.velocity = VEC3_MUL(VEC3_UNIT(VECTOR(1, 1.8, 0)), 11.25),
	};

	environ e = {
		.gravity = VECTOR(0, -0.1, 0),
		.wind = VECTOR(-0.01, 0, 0),
	};

	printf("Start position <x, y>: <%g, %g>\n", p.position->x, p.position->y);
	printf("Start velocity <x, y>: <%g, %g>\n", p.velocity->x, p.velocity->y);
	write_pixel(c, p.position->x, c->height - p.position->y, COLOUR(0, 1, 0));
	while (p.position->y > 0) {
		tick(&e, &p);
		uint16_t ix = (uint16_t)p.position->x;
		uint16_t iy = (uint16_t)(c->height - p.position->y);
		write_pixel(c, ix, iy, COLOUR(0, 1, 0));
	}
	printf("End position <x, y>: <%g, %g>\n", p.position->x, p.position->y);
	printf("Canvas saved to file '%s'.\n", canvas_2_ppm(c));

	return EXIT_SUCCESS;
}
