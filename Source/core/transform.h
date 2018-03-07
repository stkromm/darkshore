#pragma once

#include <memory>
#include <iostream>

#include "math/mat4x4.h"
#include "math/vec3.h"
#include "math/vec2.h"

class Transform {
private:
	mutable bool dirty_local_to_world = true;
	mutable bool dirty_world_to_local = true;
	mutable math::Mat4x4 previous_local_to_world;

	mutable math::Mat4x4 local_to_world;
	mutable math::Mat4x4 world_to_local;
	std::shared_ptr<Transform> parent;

	math::Vec3 position;
	float rotation;
	math::Vec2 scale_factor;
public:
	Transform();
	~Transform();

	math::Mat4x4 get_local_to_world() const;
	math::Mat4x4 get_local_to_world(float interpolate) const;
	math::Mat4x4 get_world_to_local() const;

	void translate(const math::Vec2 translation);
	void set_position(const math::Vec2 position);
	void rotate(const float angle);
	void scale(const float scale_factor);
	void scale(const float scale_x, const float scale_y);

	void set_parent(std::shared_ptr<Transform> parent)
	{
		this->parent = parent;
	}

	float get_rotation() const
	{
		return rotation;
	}

	math::Vec2 get_position() const
	{
		return { position.x, position.y };
	}

	math::Vec2 get_scale() const
	{
		return scale_factor;
	}

	void update();

	std::string to_string() const;
};