#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "game.h"
#include "sprite.h"
#include "platform/window.h"

void poll_input() {
	glfwPollEvents();
}
namespace graphics {

	namespace SceneManager
	{
		bool init()
		{
			if (glewInit() != GLEW_OK)
			{
				std::cout << "GLEW init failed" << std::endl;
				return false;
			}

			std::cout << glGetString(GL_VERSION) << std::endl;
			std::cout << glGetString(GL_VENDOR) << std::endl;
			std::cout << glGetString(GL_RENDERER) << std::endl;
			std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

			return true;
		}

		void shutdown()
		{

		}
	};
}

Transform* transform1;

void key_press(const size_t k, const  size_t m, const  size_t s, const  size_t a) {
	std::cout << "Key press oO" << std::endl;

	if (k == GLFW_KEY_W) {
		transform1->translate({ 0,1 });
	}
	else if (k == GLFW_KEY_S) {
		transform1->translate({ 0,-1 });
	}
	else if (k == GLFW_KEY_A) {
		transform1->translate({ -1,0 });
	}
	else if (k == GLFW_KEY_D) {
		transform1->translate({ 1,0 });
	}
}


int main(const int argc, const char** argv) {
	graphics::Scene* scene;
	Game* game;

	std::cout << "Vine Engine started" << std::endl;
	// Init platform
	if (!platform::WindowManager::init())
	{
		return -1;
	}

	platform::WindowManager::get_window().add_key_callback(key_press);

	game = new Game();

	if (!graphics::SceneManager::init())
	{
		return -1;
	}
	scene = new graphics::Scene();

	graphics::Texture* texture = new graphics::Texture("res/image/hero.png");
	transform1 = new Transform();
	graphics::Sprite* sprite = new graphics::Sprite(transform1, { -16.f, -32.f }, { 32.f, 64.f
		}, graphics::TexturePatch{
				std::shared_ptr<graphics::Texture>(texture),
				0.f,0.f,1.f,1.f
		});

	scene->add_renderable(sprite);
	Transform* transform2 = new Transform();
	transform2->set_parent(std::shared_ptr<Transform>(transform1));
	transform2->translate({ 50.f,50.f });
	graphics::Sprite* sprite2 = new graphics::Sprite(transform2, { 0.f, 0.f }, { 32.f, 64.f
		}, graphics::TexturePatch{
			std::shared_ptr<graphics::Texture>(texture),
			0.f,0.f,1.f,1.f
		});
	scene->add_renderable(sprite2);
	Transform* transform3 = new Transform();
	transform3->set_parent(std::shared_ptr<Transform>(transform2));
	transform3->translate({ 200.f,100.f });
	graphics::Sprite* sprite3 = new graphics::Sprite(transform3, { 0.f, 0.f }, { 32.f, 64.f
		}, graphics::TexturePatch{
			std::shared_ptr<graphics::Texture>(texture),
			0.f,0.f,1.f,1.f
		});
	scene->add_renderable(sprite3);
	// Game Loop
	int loops = 0;
	const auto tick_delta_nanos = std::chrono::nanoseconds((int)(game->TICK_DELTA_MILLIS * 1000000.0f));
	game->start();
	while (game->is_running) {
		poll_input();
		game->is_running = !platform::WindowManager::get_window().should_close();

		loops = 0;

		while (loops < game->MAX_FRAME_SKIP &&
			std::chrono::high_resolution_clock::now() > game->frame_fixed_end)
		{
			game->simulate_step();

			transform2->set_position({
			sinf(game->ticks * 0.02f) * 100.f,
			cosf(game->ticks * 0.02f) * 100.f
				});
			transform1->rotate(.01f);
			transform3->rotate(-.08f);
			loops++;
		}

		scene->render(game->get_tick_interpolation());

		platform::WindowManager::get_window().swap_buffers();
	}

	// Manager shutdown
	graphics::SceneManager::shutdown();

	delete scene;
	delete game;

	platform::WindowManager::shutdown();

	return 0;
}