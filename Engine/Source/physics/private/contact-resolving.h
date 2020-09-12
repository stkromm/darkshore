#pragma once

#include "physics/private/contact.h"

namespace ds {
	namespace physics
	{
		void resolve(Contact contact)
		{
			const float total_inv_mass = contact.collision_pair.first->get_inversed_mass() + contact
				.collision_pair.second->
				get_inversed_mass();
			float total_mass = 0;

			if (!ds::is_nearly_zero(contact.penetration))
			{
				if (total_inv_mass == 0 || ds::is_nearly_zero(total_inv_mass))
				{
					const float collider_speed = contact.collision_pair.first->get_velocity().length();
					const ds::FVec2 impact_translation = contact.normal * contact.penetration;
					if (ds::is_nearly_zero(collider_speed))
					{
						contact.collision_pair.second->move(impact_translation);
					}
					else
					{
						const float collided_with_speed = contact.collision_pair.second->get_velocity().length();
						if (ds::is_nearly_zero(collided_with_speed))
						{
							contact.collision_pair.first->move(impact_translation * -1);
						}
						else
						{
							const float total_speed = collided_with_speed + collider_speed;
							if (total_speed != 0) {
							const float total_ispeed = 1 / total_speed;

							const ds::FVec2 collider_impact_translation = impact_translation * (-collider_speed * total_ispeed);
							contact.collision_pair.first->move(collider_impact_translation);

							const ds::FVec2 collided_with_impact_translation = impact_translation * (collided_with_speed * total_ispeed);
							contact.collision_pair.second->move(collided_with_impact_translation);
							}
						}
					}
				}
				else
				{
					total_mass = 1.f / total_inv_mass;
					const ds::FVec2 impact_translation = contact.normal * (contact.penetration * total_mass);

					contact.collision_pair.first->move(ds::FVec2{ -impact_translation.x, -impact_translation.y } * contact.collision_pair.first->get_inversed_mass());
					contact.collision_pair.second->move(impact_translation * contact.collision_pair.second->get_inversed_mass());
				}
			}

			if (total_mass == 0 && total_inv_mass != 0)
			{
				total_mass = 1.f / total_inv_mass;
			}
			ds::FVec2 rel_velocity = contact.collision_pair.second->get_velocity();
			rel_velocity = rel_velocity - contact.collision_pair.first->get_velocity();

			const float separation_speed = rel_velocity * contact.normal;
			if (!ds::is_nearly_zero(separation_speed) || (ds::is_nearly_zero(total_inv_mass)
				&& (contact.collision_pair.first->is_kinematic() || contact.collision_pair.second->is_kinematic())))
			{
				return;
			}

			const float post_separation_speed = -separation_speed * total_mass;
			const float delta_speed = post_separation_speed - separation_speed;

			const float impulse = delta_speed * total_mass;
			const ds::FVec2 impact_velocity = contact.normal * impulse;

			if (contact.collision_pair.first->is_kinematic())
			{
				ds::FVec2 collider_velocity = impact_velocity + contact.collision_pair.first->get_velocity();
				collider_velocity = collider_velocity * -contact.collision_pair.first->get_inversed_mass();
				contact.collision_pair.first->set_velocity(collider_velocity);
			}
			if (contact.collision_pair.second->is_kinematic())
			{
				ds::FVec2 collided_with_velocity = impact_velocity + contact.collision_pair.second->get_velocity();
				collided_with_velocity = collided_with_velocity * contact.collision_pair.second->get_inversed_mass();
				contact.collision_pair.second->set_velocity(collided_with_velocity);
			}
		}
	}
}