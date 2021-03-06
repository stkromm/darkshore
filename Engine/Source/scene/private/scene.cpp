#include "scene/scene.h"
#include "scene/render_manager.h"
#include "core/math/mat4x4.h"
#include "core/transform.h"
#include "scene/scene.h"
#include "darkshore.h"

using namespace ds::scene;

void Scene::add_renderable(const std::shared_ptr<Renderable> renderable)
{
	renderables.push_back(renderable);
}

void Scene::render(const float interpolation)
{
	if (!get_camera()) return;

	RenderManager::prepare();
	RenderManager::get_sprite_renderer()->get_shader()->bind();
	RenderManager::get_sprite_renderer()->get_shader()->set_uniform_mat4x4("pr_matrix", get_camera()->get_projection());

	for (const auto& renderable : renderables)
	{
		renderable->draw(interpolation);
	}

	RenderManager::flush();
}
