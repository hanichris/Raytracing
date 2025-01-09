#include "headers/vec3.h"

vec3* unit_vec3(vec3* u) {
	return u ? scalar_div(u, len(u)) : u;
}

vec3* sub(vec3 const* u, vec3 const* v, vec3* out) {
	if (u && v && out) {
		out->x = u->x - v->x;
		out->y = u->y - v->y;
		out->z = u->z - v->z;
	}
	return out;
}

vec3* add(vec3 const* u, vec3 const* v, vec3* out) {
	if (u && v && out) {
		out->x = u->x + v->x;
		out->y = u->y + v->y;
		out->z = u->z + v->z;
	}
	return out;
}

vec3* cross(vec3* u, vec3* v, vec3* out) {
	if (u && v && out) {
		out->x = (u->y * v->z) - (u->z * v->y);
		out->y = (u->z * v->x) - (u->x * v->z);
		out->z = (u->x * v->y) - (u->y * v->x);
	}
	return out;
}


