#pragma once

#include <vector>
#include <memory>

#include "platform/platform.h"
#include "math/vec2.h"

namespace platform {
	constexpr uint32_t FULLSCREEN = 0;
	constexpr uint32_t BORDERLESS_WINDOWED = 1;
	constexpr uint32_t WINDOWED = 2;

	using KeyCallback = void(*)(const size_t, const  size_t, const  size_t, const  size_t);
	using CursorPositionCallback = void(*)(const double, const double);
	using MouseButtonCallback = void(*)(const size_t, const size_t, const size_t);

	struct Cursor {
		math::Vec2 position;
	};
	struct Screen {
		 int width;
		 int height;
	};
	class Window {
	public:
		std::vector<KeyCallback> keyCallbacks;
		std::vector<CursorPositionCallback> cursorPositionCallbacks;
		std::vector<MouseButtonCallback> mouseButtonCallbacks;
	private:
		int32_t width, height;
		math::Vec2 position;

		String title;
		bool closed = false;
	public:
		Window();
		~Window();

		const std::shared_ptr<Cursor> get_cursor();

		const Screen& get_screen();

		void update();
		void close();

		void swap_buffers() const;
		bool should_close() const;

		void add_key_callback(KeyCallback keyCallback) {
			keyCallbacks.push_back(keyCallback);
		}

		void add_mouse_button_callback(MouseButtonCallback mouseButtonCallback) {
			mouseButtonCallbacks.push_back(mouseButtonCallback);
		}

		void add_cursor_position_callback(CursorPositionCallback cursorPositionCallback) {
			cursorPositionCallbacks.push_back(cursorPositionCallback);
		}

		void set_clipboard_content(const char * content) const;
		const char* get_clipboard_content() const;

		void resize(const uint32_t width, const uint32_t height);

		void go_windowed();
		void go_borderless();
		void go_fullscreen();
	private:
		void recreate();
	};
	namespace WindowManager {
		bool init();
		void shutdown();
		Window& get_window();

	};
};