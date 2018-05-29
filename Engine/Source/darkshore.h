#pragma once

#include "core/core.h"
#include "game/game.h"

#include "scene/render_manager.h"
#include "scene/scene_manager.h"
#include "platform/window_manager.h"
#include "physics/physics.h"
#include "animation/animation_manager.h"
#include "dslevel/level_loader.h"

#ifdef WIN32
#else
#define DS_MAIN main
#endif