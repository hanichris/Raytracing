#include "headers/vec3.h"


vec3* unit_vec3(vec3 const* u, vec3* out) {
	return u && out ? scalar_div(u, len(u), out) : nullptr;
}

tuple* sub(tuple const* u, tuple const* v, tuple* out) {
	if (u && v && out) {
		out->x = u->x - v->x;
		out->y = u->y - v->y;
		out->z = u->z - v->z;
		out->w = u->w - v->w;
		return out;
	}
	return nullptr;
}

tuple* add(tuple const* u, tuple const* v, tuple* out) {
	if (u && v && out) {
		out->x = u->x + v->x;
		out->y = u->y + v->y;
		out->z = u->z + v->z;
		out->w = u->w + v->w;
		return out;
	}
	return nullptr;
}

vec3* cross(vec3 const* u, vec3 const* v, vec3* out) {
	if (u && v && out) {
		out->x = (u->y * v->z) - (u->z * v->y);
		out->y = (u->z * v->x) - (u->x * v->z);
		out->z = (u->x * v->y) - (u->y * v->x);
		return out;
	}
	return nullptr;
}

