#ifndef MY_RAY_H
#define MY_RAY_H 1

#include "vec3.h"

typedef struct ray ray;
struct ray {
	point3 orig;
	vec3 dir;
};

static
point3* at(ray const* r, double t, point3* out) {
	if (r && out) {
		vec3 tmp = {
			.x = r->dir.x,
			.y = r->dir.y,
			.z = r->dir.z
		};
		add(&r->orig, scalar_mul(&tmp, t), out);
		return out;
	}
	return nullptr;
}


#endif
