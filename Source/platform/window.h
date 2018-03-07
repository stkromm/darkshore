#pragma once

#include <vector>
#include <memory>
#include <functional>

#include "platform/platform.h"
#include "core/types.h"
#include "core/math/vec2.h"
#include "platform/cursor.h"

namespace platform {
	constexpr uint32_t FULLSCREEN = 0;
	constexpr uint32_t BORDERLESS_WINDOWED = 1;
	constexpr uint32_t WINDOWED = 2;

	using KeyCallback = void(const size_t, const  size_t, const  size_t, const  size_t);
	using CursorPositionCallback = void(const double, const double);
	using MouseButtonCallback = void(const size_t, const size_t, const size_t);

	struct Screen {
		int32_t width;
		int32_t height;
	};
	class Window {
	public:
		std::vector<std::function<KeyCallback>> keyCallbacks;
		std::vector<std::function<CursorPositionCallback>> cursorPositionCallbacks;
		std::vector<std::function<MouseButtonCallback>> mouseButtonCallbacks;
	private:
		int32_t width = 1024;
		int32_t height = 720;
	
		math::Vec2 position = { 0,0 };
		String title = "";
		bool closed = false;
	public:
		Window();
		~Window();

		const Cursor get_cursor();

		const Screen get_screen();

		void poll_input();
		void update();
		void close();

		void swap_buffers() const;
		bool should_close() const;

		void add_key_callback(std::function<KeyCallback> keyCallback);

		void add_mouse_button_callback(std::function<MouseButtonCallback> mouseButtonCallback);

		void add_cursor_position_callback(std::function<CursorPositionCallback> cursorPositionCallback);

		void set_clipboard_content(const char * content) const;
		const char* get_clipboard_content() const;

		void resize(const uint32_t width, const uint32_t height);

		void go_windowed();
		void go_borderless();
		void go_fullscreen();
	private:
		void recreate();
	};
};