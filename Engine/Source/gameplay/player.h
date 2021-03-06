#pragma once

#include "game/game.h"
#include "game/entity.h"

#include "graphics/tiled_texture.h"

#include "gameplay/camera_component.h"
#include "gameplay/movement_controller_component.h"
#include "gameplay/rigid_body_component.h"
#include "gameplay/sprite_animation_component.h"
#include "gameplay/sprite_animation_clip.h"
#include "gameplay/sprite_component.h"

#include "platform/asset_manager.h"
#include "platform/input.h"
#include "sprite_animation_reader.h"
#include <fstream>
#include "game/entity.h"
#include "scene/sprite.h"
#include "platform/window.h"
#include "scene/texture_asset.h"

namespace ds {
	namespace game {
		class Pawn : public Entity
		{
		private:
			std::shared_ptr<ds::graphics::Texture> texture;
			std::shared_ptr<TextureAsset> texture_asset;
			std::shared_ptr<scene::Sprite> sprite;
			std::shared_ptr<physics::RigidBody> rigid_body;
		public:
			Pawn(std::string texture_name, const int width, const int height, const int x, const int y)
			{
				texture_asset = AssetManager::load_asset<TextureAsset>(std::move(texture_name));
				texture = texture_asset->texture;
				const ds::graphics::TiledTexture tiled_texture = ds::graphics::TiledTexture(std::shared_ptr<ds::graphics::Texture>(texture),
					width,
					height);
				sprite = std::make_shared<scene::Sprite>(transform, ds::FVec2{ -width * 2.f, -height * 2.f },
					ds::FVec2{ width * 4.f, height * 4.f }, tiled_texture[x][y], 255);
				physics::CollisionBody collider;
				collider.hull = { {-48, -64}, { 96, 128 } };
				std::vector<physics::CollisionBody> colliders;
				colliders.push_back(std::move(collider));
				rigid_body = std::make_shared<physics::RigidBody>(transform, colliders);
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
				const std::function<platform::KeyCallback> key_callback = [this
				](const size_t k, const size_t a, const size_t b, const size_t c)
				{
					this->key_press(k, a, b, c);
				};
				platform::WindowManager::get_window().add_key_callback(key_callback);
			}

			void on_spawn() override
			{
				Pawn::on_spawn();

				const std::shared_ptr<scene::Sprite> sprite = get_component<SpriteComponent>()->get_sprite();
				const ds::graphics::TiledTexture tiled_texture = ds::graphics::TiledTexture(
					std::shared_ptr<ds::graphics::Texture>(sprite->get_texture()), 24, 32);
				std::ifstream config_file("res/animation/hero-anim.json");
				json settings;
				if (config_file.is_open())
					config_file >> settings;
				else
					settings = {};
				std::shared_ptr<AnimationStateMachine> animation_state_machine = read_sprite_animation_file(sprite, settings);
				add_component<AnimationComponent>(animation_state_machine);
				add_component<MovementControllerComponent>();
				std::shared_ptr<scene::Camera> camera = std::make_shared<scene::Camera>();
				camera->get_transform()->set_parent(transform);
				const platform::Screen screen = platform::WindowManager::get_window().get_screen();
				const float aspect = float(screen.height) / screen.width;
				const float width = 1920;
				const float height = 1920 * aspect;
				camera->set_bounds(width / 2, height / 2 + 16, width / 2 + 32 * 100, height / 2 + 32 * 47 + 16);
				add_component<CameraComponent>(camera);
				get_component<CameraComponent>()->activate();
			}

			std::shared_ptr<Transform> get_transform() const
			{
				return transform;
			}

			void self_tick() override
			{
				Pawn::self_tick();

				const auto animation_component = get_component<AnimationComponent>();
				const auto rigid_body_component = get_component<RigidBodyComponent>();

				bool moved = false;
				// Check input
				if (platform::is_pressed(GLFW_KEY_W))
				{
					moved = true;
					rigid_body_component->get_rigid_body()->add_impuls({ 0, 0.16f });
					animation_component->get_animation()->transition("up_walking", true);
				}
				if (platform::is_pressed(GLFW_KEY_S))
				{
					moved = true;

					rigid_body_component->get_rigid_body()->add_impuls({ 0, -0.16f });
					animation_component->get_animation()->transition("down_walking", true);
				}
				if (platform::is_pressed(GLFW_KEY_A))
				{
					moved = true;

					rigid_body_component->get_rigid_body()->add_impuls({ -0.16f, 0 });
					animation_component->get_animation()->transition("left_walking", true);
				}
				if (platform::is_pressed(GLFW_KEY_D))
				{
					moved = true;

					rigid_body_component->get_rigid_body()->add_impuls({ 0.16f, 0 });
					animation_component->get_animation()->transition("right_walking", true);
				}

				if (!moved)
				{
					if (animation_component->get_animation()->get_current_state() == "right_walking")
					{
						animation_component->get_animation()->transition("right_idle", true);
					}
					else if (animation_component->get_animation()->get_current_state() == "up_walking")
					{
						animation_component->get_animation()->transition("up_idle", true);
					}
					else if (animation_component->get_animation()->get_current_state() == "down_walking")
					{
						animation_component->get_animation()->transition("down_idle", true);
					}
					else if (animation_component->get_animation()->get_current_state() == "left_walking")
					{
						animation_component->get_animation()->transition("left_idle", true);
					}
				}

			}
			void key_press(const size_t k, const size_t m, const size_t s, const size_t a) const
			{
				if (k == GLFW_KEY_H)
				{
					LOG_INFO << this->transform->to_string() << LOG_END;
				}
			}
		};

		class NPC : public Pawn
		{
			std::weak_ptr<Transform> followed_transform;
		public:
			NPC(const float x, const float y) : Pawn("hero-sheet.png", 24, 32, 1, 3)
			{
				const std::function<platform::KeyCallback> key_callback = [this
				](const size_t k, const size_t a, const size_t b, const size_t c)
				{
					this->key_press(k, a, b, c);
				};
				platform::WindowManager::get_window().add_key_callback(key_callback);
				transform->set_position({ x, y });
			}

			void on_spawn() override
			{
				Pawn::on_spawn();

				std::shared_ptr<scene::Sprite> sprite = get_component<SpriteComponent>()->get_sprite();
				const ds::graphics::TiledTexture tiled_texture = ds::graphics::TiledTexture(
					std::shared_ptr<ds::graphics::Texture>(sprite->get_texture()), 24, 32);
				std::vector<Frame> frames = {
					{tiled_texture[0][0], 200}, {tiled_texture[1][0], 200}, {tiled_texture[2][0], 200}, {tiled_texture[1][0], 200}
				};
				const std::shared_ptr<AnimationClip> clip = std::make_shared<SpriteAnimationClip>(
					sprite, frames);
				std::vector<Frame> frames2 = {
					{tiled_texture[0][1], 200}, {tiled_texture[1][1], 200}, {tiled_texture[2][1], 200}, {tiled_texture[1][1], 200}
				};
				const std::shared_ptr<AnimationClip> clip2 = std::make_shared<SpriteAnimationClip>(
					sprite, frames2);
				std::shared_ptr<AnimationStateMachine> animation_state_machine = std::make_shared<AnimationStateMachine>();
				animation_state_machine->add_state({ "idle", clip, "idle2" });
				animation_state_machine->add_state({ "idle2", clip2, "idle" });
				add_component<AnimationComponent>(animation_state_machine);

				get_component<RigidBodyComponent>()->get_rigid_body()->set_linea_damping(0.8f);
				get_component<RigidBodyComponent>()->get_rigid_body()->set_inverse_mass(1.f);
				std::shared_ptr<scene::Camera> camera = std::make_shared<scene::Camera>();
				camera->get_transform()->set_parent(transform.get());
				add_component<CameraComponent>(camera);
			}

			void tick() override
			{
				Pawn::tick();
				if (followed_transform.expired())
				{
					followed_transform = game->find_by_tag<Player>("player")->get_transform();
				}

				const ds::FVec2 distance = (followed_transform.lock()->get_position() - transform->get_position());
				get_component<RigidBodyComponent>()->get_rigid_body()->add_force(distance * 0.1f);
			}

			void key_press(const size_t k, const size_t m, const size_t s, const size_t a) const
			{
				if (k == GLFW_KEY_J)
				{
					get_component<CameraComponent>()->activate();
				}
			}
		};
	}
}