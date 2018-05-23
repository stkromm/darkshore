#pragma once

#include <string>

#include "core/math/mat4x4.h"

namespace ds {
	namespace graphics {

		class Shader
		{
			uint32_t id;
		public:
			explicit Shader(const std::string& file_path) : Shader(file_path.c_str())
			{
			}

			explicit Shader(const char* file_path);
			~Shader();

			void bind() const;
			void unbind() const;

			void set_uniform_1i(std::string name, int value);
			void set_uniform_1ui(std::string name, uint32_t value);
			void set_uniform_1f(std::string name, float value);

			void set_uniform_2i(std::string name, int i0, int i1);
			void set_uniform_2ui(std::string name, uint32_t i0, uint32_t i1) const;
			void set_uniform_2f(std::string name, float f0, float f1);

			void set_uniform_3i(std::string name, int i0, int i1, int i2);
			void set_uniform_3ui(std::string name, uint32_t i0, uint32_t i1, uint32_t i2);
			void set_uniform_3f(std::string name, float f0, float f1, float f2);

			void set_uniform_4i(std::string name, int i0, int i1, int i2, int i3);
			void set_uniform_4ui(std::string name, uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3);
			void set_uniform_4f(std::string name, float f0, float f1, float f2, float f3);

			void set_uniform_mat4x4(std::string name, math::Mat4x4 mat);
			void set_uniform_vec3(std::string name, math::Vec3 vec);

			int get_uniform_location(std::string name) const;

			bool operator==(const Shader& shader) const
			{
				return id == shader.id;
			}
		};
	}
}