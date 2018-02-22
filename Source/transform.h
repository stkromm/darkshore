#pragma once

#include <memory>

#include "math/mat4x4.h"
#include "math/vec2.h"

class Transform {
private:
	mutable bool dirty = true;
	mutable math::Mat4x4 cache_local_to_world;
	mutable math::Mat4x4 cache_world_to_local;
	std::shared_ptr<Transform> parent;

	math::Vec2 position;
	float rotation;
	math::Vec2 scale;
public:
	Transform() : cache_local_to_world(math::Mat4x4(1)), cache_world_to_local(math::Mat4x4(1))
	{
	}

	math::Mat4x4 get_local_to_world() const;
	math::Mat4x4 get_world_to_local() const;

	void translate(const math::Vec2 translation);
	void set_position(const math::Vec2 position) {
		this->position = position;
		dirty = true;
	}
	void rotate(const float angle);
	void set_parent(const std::shared_ptr<Transform>& parent) {
		this->parent = parent;
	}
};