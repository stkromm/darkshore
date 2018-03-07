#pragma once

#include "core/game.h"
#include "core/entity.h"

#include "graphics/tiled_texture.h"

#include "gameplay/camera_component.h"
#include "gameplay/movement_controller_component.h"
#include "gameplay/rigid_body_component.h"
#include "gameplay/sprite_animation_component.h"
#include "gameplay/sprite_animation_clip.h"
#include "gameplay/sprite_component.h"

class Pawn : public Entity
{
private:
	std::shared_ptr<graphics::Texture> texture;
	std::shared_ptr<graphics::Sprite> sprite;
	std::shared_ptr<physics::RigidBody> rigid_body;
public:
	Pawn(std::string texture_name, int width, int height, int x, int y) : Entity()
	{
		texture = AssetManager::load_asset<graphics::Texture>(texture_name);
		graphics::TiledTexture tiled_texture = graphics::TiledTexture(std::shared_ptr<graphics::Texture>(texture), width, height);
		sprite = std::make_shared<graphics::Sprite>(transform, math::Vec2{ -width * 2.f, -height * 2.f }, math::Vec2{ width * 4.f, height * 4.f }, tiled_texture[x][y], 255);
		rigid_body = std::make_shared<physics::RigidBody>(transform);
	}

	void self_tick() override
	{
		Entity::self_tick();
	}

	void on_spawn() override
	{
		Entity::on_spawn();
		add_component<SpriteComponent>(sprite);
		add_component<RigidBodyComponent>(rigid_body);
	}
};

class Player : public Pawn
{
public:
	Player() : Pawn("hero-sheet.png", 24, 32, 1, 2)
	{
		this->tag = "player";
		std::function<platform::KeyCallback> key_callback = [this](const size_t k, const  size_t a, const  size_t b, const  size_t c) {
			this->key_press(k, a, b, c);
		};
		platform::WindowManager::get_window().add_key_callback(key_callback);
	}

	void on_spawn() override
	{
		Pawn::on_spawn();

		std::shared_ptr<graphics::Sprite> sprite = get_component<SpriteComponent>()->get_sprite();
		graphics::TiledTexture tiled_texture = graphics::TiledTexture(std::shared_ptr<graphics::Texture>(sprite->get_texture()), 24, 32);
		std::vector<Frame> frames = {
			{ tiled_texture[0][0], 200 },{ tiled_texture[1][0], 200 },{ tiled_texture[2][0], 200 },{ tiled_texture[1][0], 200 }
		};
		std::shared_ptr<AnimationClip> clip = std::make_shared<SpriteAnimationClip>(
			sprite, frames);
		std::shared_ptr<AnimationStateMachine> animation_state_machine = std::make_shared<AnimationStateMachine>();
		animation_state_machine->add_state({ "idle", clip});
		add_component<SpriteAnimationComponent>(animation_state_machine);

		add_component<MovementControllerComponent>();
		std::shared_ptr<graphics::Camera> camera = std::make_shared<graphics::Camera>();
		camera->transform->set_parent(transform);
		add_component<CameraComponent>(camera);
		get_component<CameraComponent>()->activate();
	}

	std::shared_ptr<Transform> get_transform() const
	{
		return transform;
	}

	void key_press(const size_t k, const  size_t m, const  size_t s, const  size_t a)
	{
		if (k == GLFW_KEY_H) {
			get_component<CameraComponent>()->activate();
		}
	}
};

class NPC : public Pawn
{
	std::weak_ptr<Transform> followed_transform;
public:
	NPC(float x, float y) : Pawn("hero-sheet.png", 24, 32, 1, 3)
	{
		std::function<platform::KeyCallback> key_callback = [this](const size_t k, const  size_t a, const  size_t b, const  size_t c) {
			this->key_press(k, a, b, c);
		};
		platform::WindowManager::get_window().add_key_callback(key_callback);
		transform->set_position({ x, y });
	}

	void on_spawn() override
	{
		Pawn::on_spawn();

		std::shared_ptr<graphics::Sprite> sprite = get_component<SpriteComponent>()->get_sprite();
		graphics::TiledTexture tiled_texture = graphics::TiledTexture(std::shared_ptr<graphics::Texture>(sprite->get_texture()), 24, 32);
		std::vector<Frame> frames = {
			{ tiled_texture[0][0], 200 },{ tiled_texture[1][0], 200 },{ tiled_texture[2][0], 200 },{ tiled_texture[1][0], 200 }
		};
		std::shared_ptr<AnimationClip> clip = std::make_shared<SpriteAnimationClip>(
			sprite, frames);
		std::vector<Frame> frames2 = {
			{ tiled_texture[0][1], 200 },{ tiled_texture[1][1], 200 },{ tiled_texture[2][1], 200 },{ tiled_texture[1][1], 200 }
		};
		std::shared_ptr<AnimationClip> clip2 = std::make_shared<SpriteAnimationClip>(
			sprite, frames2);
		std::shared_ptr<AnimationStateMachine> animation_state_machine = std::make_shared<AnimationStateMachine>();
		animation_state_machine->add_state({ "idle", clip, "idle2" });
		animation_state_machine->add_state({ "idle2", clip2 , "idle" });
		add_component<SpriteAnimationComponent>(animation_state_machine);

		get_component<RigidBodyComponent>()->get_rigid_body()->set_linea_damping(0.8f);
		get_component<RigidBodyComponent>()->get_rigid_body()->set_inverse_mass(1.f);
		std::shared_ptr<graphics::Camera> camera = std::make_shared<graphics::Camera>();
		camera->transform->set_parent(transform);
		add_component<CameraComponent>(camera);
	}

	void tick() override
	{
		Pawn::tick();
		if (followed_transform.expired())
		{
			followed_transform = game->find_by_tag<Player>("player")->get_transform();
		}

		math::Vec2 distance = (followed_transform.lock()->get_position() - transform->get_position());
		get_component<RigidBodyComponent>()->get_rigid_body()->add_force(distance * 0.1f);
	}

	void key_press(const size_t k, const  size_t m, const  size_t s, const  size_t a)
	{
		if (k == GLFW_KEY_J) {
			get_component<CameraComponent>()->activate();
		}
	}
};