#include "transform.h"

math::Mat4x4 Transform::get_local_to_world() const
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
	else
	{
		return local_to_world;
	}
}

math::Mat4x4 Transform::get_world_to_local() const
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
	else
	{
		return world_to_local;
	}
}

void Transform::translate(const math::Vec2 translation)
{
	dirty_local_to_world = true;
	dirty_world_to_local = true;
	this->position.x += translation.x;
	this->position.y += translation.y;
}

void Transform::set_position(const math::Vec2 position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	dirty_local_to_world = true;
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