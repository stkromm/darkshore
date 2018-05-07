#include "tilemap/tile_map.h"

#include "gameplay/player.h"

tilemap::TileMap::TileMap(const uint32_t size_x, const uint32_t size_y,
	std::shared_ptr<graphics::TiledTexture> texture,
	std::vector<std::shared_ptr<tilemap::TileLayer>> layers, std::vector<std::shared_ptr<TileAnimationClip>> animations) :
	layers(std::move(layers)), tiled_texture(std::move(texture)), animations(std::move(animations)), size_x(size_x), size_y(size_y)
{
	this->tag = "map";
	transform = std::make_shared<Transform>();
	transform->translate({ -260, -160 });
	std::vector<graphics::Vertex> vertices;
	std::vector<uint32_t> indices;
	shader = AssetManager::load_asset<graphics::Shader>("basic.shader");

}

tilemap::TileMap::~TileMap()
{
	std::cout << "Delete tilemap" << std::endl;
}

void tilemap::TileMap::on_spawn() 
{
	for (auto& animation : animations)
	{
		std::shared_ptr<AnimationStateMachine> animation_state_machine = std::make_shared<AnimationStateMachine>();
		animation_state_machine->add_state({ "tile_anim", animation });
		add_component<AnimationComponent>(animation_state_machine);
	}
	const auto player = game->find_by_tag<Player>("player");
	if (player)
	{
		transform->set_parent(player->get_transform());
	}
}

void tilemap::TileMap::tick() 
{
	const auto local_to_world = graphics::SceneManager::get_scene()->get_camera()->get_transform()->get_local_to_world();
	const math::Vec2 position = { float(platform::WindowManager::get_window().get_screen().width * -0.5f + fmod(local_to_world[3 * 4], 32 * 2)), float(platform::WindowManager::get_window().get_screen().height * -0.5f - (fmod(-local_to_world[3 * 4 + 1], 32 * 2))) };

	set_render_window(local_to_world[12] - float(platform::WindowManager::get_window().get_screen().width * -0.5f), local_to_world[13] - float(platform::WindowManager::get_window().get_screen().height * -0.5f));
	transform->set_position(position);
}

void tilemap::TileMap::draw(const float interpolation) const
{
	for (auto& layer : layers)
	{
		shader->bind();
		shader->set_uniform_mat4x4("pr_matrix", graphics::SceneManager::get_scene()->get_camera()->get_projection());
		shader->set_uniform_mat4x4("vw_matrix", transform->get_local_to_world());
		tiled_texture->get_texture()->bind();
		shader->set_uniform_1i("tex", 0);
		layer->get_render_view()->draw(shader.get());
	}
}

void tilemap::TileMap::set_render_window(const float x, const float y)
{
	for (auto& layer : layers)
	{
		layer->get_render_view()->update_render_window(x, y);
	}
}