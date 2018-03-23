#pragma once

#include "physics/rigid_body.h"

namespace physics
{
	struct Contact
	{
		std::pair<RigidBody*, RigidBody*> collision_pair;
		math::Vec2 normal;
		float penetration;
		float friction = 1;
		float restituition = 1;
	};

	inline void resolve(Contact contact)
	{
		const float total_inv_mass = contact.collision_pair.first->get_inversed_mass() + contact
		                                                                                 .collision_pair.second->
		                                                                                 get_inversed_mass();

		if (!math::is_nearly_zero(contact.penetration))
		{
			if (math::is_nearly_zero(total_inv_mass))
			{
				const float collider_speed = contact.collision_pair.first->get_velocity().length();
				const math::Vec2 impact_translation = contact.normal * contact.penetration;
				if (math::is_nearly_zero(collider_speed))
				{
					contact.collision_pair.second->move(impact_translation);
				}
				else
				{
					const float collided_with_speed = contact.collision_pair.second->get_velocity().length();
					if (math::is_nearly_zero(collided_with_speed))
					{
						contact.collision_pair.first->move(impact_translation * -1);
					}
					else
					{
						const float total_speed = collided_with_speed + collider_speed;

						const math::Vec2 collider_impact_translation = impact_translation * (-collider_speed / total_speed);
						contact.collision_pair.first->move(collider_impact_translation);

						const math::Vec2 collided_with_impact_translation = impact_translation * (collided_with_speed / total_speed);
						contact.collision_pair.second->move(collided_with_impact_translation);
					}
				}
			}
			else
			{
				const math::Vec2 impact_translation = contact.normal * (contact.penetration / total_inv_mass);

				contact.collision_pair.first->move(impact_translation * -contact.collision_pair.first->get_inversed_mass());
				contact.collision_pair.second->move(impact_translation * contact.collision_pair.second->get_inversed_mass());
			}
		}

		math::Vec2 rel_velocity = contact.collision_pair.second->get_velocity();
		rel_velocity = rel_velocity - contact.collision_pair.first->get_velocity();

		const float separation_speed = rel_velocity * contact.normal;
		if (!math::is_nearly_zero(separation_speed) || (math::is_nearly_zero(total_inv_mass)
			&& (contact.collision_pair.first->is_kinematic() || contact.collision_pair.second->is_kinematic())))
		{
			return;
		}

		const float post_separation_speed = -separation_speed / total_inv_mass;
		const float delta_speed = post_separation_speed - separation_speed;

		const float impulse = delta_speed / total_inv_mass;
		const math::Vec2 impact_velocity = contact.normal * impulse;

		if (contact.collision_pair.first->is_kinematic())
		{
			math::Vec2 collider_velocity = impact_velocity + contact.collision_pair.first->get_velocity();
			collider_velocity = collider_velocity * -contact.collision_pair.first->get_inversed_mass();
			contact.collision_pair.first->set_velocity(collider_velocity);
		}
		if (contact.collision_pair.second->is_kinematic())
		{
			math::Vec2 collided_with_velocity = impact_velocity + contact.collision_pair.second->get_velocity();
			collided_with_velocity = collided_with_velocity * contact.collision_pair.second->get_inversed_mass();
			contact.collision_pair.second->set_velocity(collided_with_velocity);
		}
	}
}
