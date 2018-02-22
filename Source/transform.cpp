#include "transform.h"

math::Mat4x4 Transform::get_local_to_world() const {
	if (dirty) {
		math::Mat4x4 local_to_world(1);
		local_to_world.data()[12] = position.x;
		local_to_world.data()[13] = position.y;
		float cos_phi = cosf(rotation);
		float sin_phi = sinf(rotation);
		local_to_world.data()[0] = cos_phi;
		local_to_world.data()[4] = -sin_phi;
		local_to_world.data()[1] = sin_phi;
		local_to_world.data()[5] = cos_phi;

		cache_local_to_world = local_to_world;
		dirty = false;
	}
	if (parent) {
		return cache_local_to_world * parent->get_local_to_world();
	}
	else {
		return cache_local_to_world;
	}
}

math::Mat4x4 Transform::get_world_to_local() const {
	if (dirty) {
		math::Mat4x4 world_to_local(1);
		world_to_local.data()[3 * 4] = -position.x;
		world_to_local.data()[3 * 4 + 1] = -position.y;
		float cos_phi = cosf(-rotation);
		float sin_phi = sinf(-rotation);
		world_to_local.data()[0] = cos_phi;
		world_to_local.data()[4] = -sin_phi;
		world_to_local.data()[1] = sin_phi;
		world_to_local.data()[5] = cos_phi;

		cache_world_to_local = world_to_local;
		dirty = false;
	}
	if (parent) {
		return parent->get_world_to_local() * cache_world_to_local;
	}
	else {
		return cache_world_to_local;
	}
}

void Transform::translate(math::Vec2 translation) {
	dirty = true;
	this->position += translation;
}

void Transform::rotate(float angle) {
	rotation += angle;
	dirty = true;
}