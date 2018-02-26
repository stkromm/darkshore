#pragma once

#include <memory>

#include "object.h"
#include "transform.h"
#include "sprite.h"
#include "tiled_texture.h"
#include "graphics/scene.h"
#include "platform/asset.h"

class Player : public GameObject
{
private:
	std::shared_ptr<Transform> transform;
	std::shared_ptr<graphics::Texture> texture;
	std::shared_ptr<graphics::Sprite> sprite;
public:
	Player()
	{
		transform = std::make_shared<Transform>();
		texture = AssetManager::load_asset<graphics::Texture>("hero-sheet.png");
		graphics::TiledTexture tiled_texture = graphics::TiledTexture(std::shared_ptr<graphics::Texture>(texture), 24, 32);
		sprite = std::make_shared<graphics::Sprite>(transform, math::Vec2{ -16.f, -32.f }, math::Vec2{ 96.f, 128.f }, tiled_texture[1][2],255);

		std::function<platform::KeyCallback> key_callback = [this](const size_t k, const  size_t a, const  size_t b, const  size_t c) {
			this->key_press(k, a, b, c);
		};
		platform::WindowManager::get_window().add_key_callback(key_callback);
	}
	~Player()
	{
	}

	void on_spawn() override
	{
		graphics::SceneManager::get_scene()->add_renderable(sprite);
	}

	void tick() override
	{
	}

	void on_destroy() override
	{
		//graphics::SceneManager::get_scene()->remove_renderable(sprite);
	}

	void key_press(const size_t k, const  size_t m, const  size_t s, const  size_t a)
	{
		std::cout << "Key press oO" << std::endl;

		if (k == GLFW_KEY_W) {
			transform->translate({ 0,3 });
		}
		if (k == GLFW_KEY_S) {
			transform->translate({ 0,-3 });
		}
		if (k == GLFW_KEY_A) {
			transform->translate({ -3,0 });
		}
		if (k == GLFW_KEY_D) {
			transform->translate({ 3,0 });
		}
	}

	std::shared_ptr<Transform> get_transform() const
	{
		return transform;
	}
};