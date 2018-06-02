#include "core/transform.h"
#include "core/logger/log.h"

using namespace ds;

Transform::Transform() :
	dirty_local_to_world(false),
	dirty_world_to_local(false),
	previous_local_to_world(ds::Mat4x4(1)),
	local_to_world(ds::Mat4x4(1)),
	world_to_local(ds::Mat4x4(1)),
	parent(nullptr),
	position({ 0, 0, 0 }),
	rotation(0),
	scale_factor({ 1, 1 })
{
}

Transform::~Transform()
{
	LOG_INFO << "Delete transform" << LOG_END;
}

ds::Mat4x4 Transform::get_local_to_world() const
{
	if (dirty_local_to_world)
	{
		local_to_world.set_translation(position);
		local_to_world.set_rotation(rotation);
		local_to_world.scale(scale_factor.x, scale_factor.y, 1);
		dirty_local_to_world = false;
	}
	if (parent)
	{
		return local_to_world * parent->get_local_to_world();
	}
	return local_to_world;
}

void Transform::update() const
{
	if (dirty_local_to_world)
	{
		local_to_world.set_translation(position);
		local_to_world.set_rotation(rotation);
		local_to_world.scale(scale_factor.x, scale_factor.y, 1);
		dirty_local_to_world = false;
	}
	if (dirty_world_to_local)
	{
		world_to_local.set_translation(-position.x, -position.y, -position.z);
		world_to_local.set_rotation(-rotation);
		world_to_local.scale(1 / scale_factor.x, 1 / scale_factor.y, 1);
		dirty_world_to_local = false;
	}
}

ds::Mat4x4 Transform::get_local_to_world(const float interpolate) const
{
	previous_local_to_world = local_to_world;
	const ds::Mat4x4 calc = get_local_to_world();
	if (interpolate > 0 && interpolate < 1)
	{
		if (parent)
			return previous_local_to_world.lerp(local_to_world, interpolate) * parent->get_local_to_world(interpolate);
		return previous_local_to_world.lerp(local_to_world, interpolate);
	}
	return calc;
}

ds::Mat4x4 Transform::get_world_to_local() const
{
	if (dirty_world_to_local)
	{
		world_to_local.set_translation(-position.x, -position.y, -position.z);
		world_to_local.set_rotation(-rotation);
		world_to_local.scale(1 / scale_factor.x, 1 / scale_factor.y, 1);
		dirty_world_to_local = false;
	}
	if (parent)
	{
		return parent->get_world_to_local() * world_to_local;
	}
	return world_to_local;
}

void Transform::translate(const ds::FVec2 translation)
{
	dirty_local_to_world = true;
	dirty_world_to_local = true;
	this->position.x += translation.x;
	this->position.y += translation.y;
}

void Transform::set_position(const ds::FVec2 position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	dirty_local_to_world = true;
	dirty_world_to_local = true;
}

void Transform::rotate(const float angle)
{
	rotation += angle;
	dirty_local_to_world = true;
	dirty_world_to_local = true;
}

void Transform::scale(const float scale_factor)
{
	this->scale_factor = this->scale_factor * scale_factor;
	dirty_local_to_world = true;
	dirty_world_to_local = true;
}

void Transform::scale(const float scale_x, const float scale_y)
{
	scale_factor.x = scale_factor.x * scale_x;
	scale_factor.y = scale_factor.y * scale_y;
	dirty_local_to_world = true;
	dirty_world_to_local = true;
}

std::string Transform::to_string() const
{
	std::stringstream ss;
	ss << "Transform(position:" << position.x << "," << position.y << "" << ",rotation:" << rotation << ",scale:";
	return ss.str();
}

void Transform::set_scale(const float zoom)
{
	scale_factor.x = zoom;
	scale_factor.y = zoom;
	dirty_local_to_world = true;
	dirty_world_to_local = true;
}
