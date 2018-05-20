#pragma once

#include <memory>

#include "math/mat4x4.h"
#include "math/vec3.h"
#include "math/vec2.h"

class Transform
{
private:
	mutable bool dirty_local_to_world = true;
	mutable bool dirty_world_to_local = true;
	mutable math::Mat4x4 previous_local_to_world;

	mutable math::Mat4x4 local_to_world;
	mutable math::Mat4x4 world_to_local;
	Transform* parent;
	
	math::Vec3 position;
	float rotation;
	math::FVec2 scale_factor;
public:
	Transform();
	~Transform();

	math::Mat4x4 get_local_to_world() const;
	math::Mat4x4 get_local_to_world(float interpolate) const;
	math::Mat4x4 get_world_to_local() const;

	void translate(math::FVec2 translation);
	void set_position(math::FVec2 position);
	void rotate(float angle);
	void scale(float scale_factor);
	void scale(float scale_x, float scale_y);
	void set_scale(float zoom);

	void set_parent(std::shared_ptr<Transform> parent)
	{
		set_parent(parent.get());
	}

	void set_parent(Transform* parent)
	{
		this->parent = parent;
		dirty_local_to_world = true;
		dirty_world_to_local = true;
	}

	float get_rotation() const
	{
		return rotation;
	}

	math::FVec2 get_position() const
	{
		return {position.x, position.y};
	}

	math::FVec2 get_scale() const
	{
		return scale_factor;
	}

	void update() const;

	std::string to_string() const;
};
