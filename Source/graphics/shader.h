#pragma once

#include <string>

#include "platform/asset.h"

#include "graphics/graphics.h"

#include "math/mat4x4.h"

namespace graphics {
	class Shader : public Asset {
	private:
		unsigned int id;
	public:
		static AssetType get_resource_type()
		{
			return AssetType::SHADER;
		}

		enum class Type
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2, TESSELATION_CONTROL = 3, TESSELATION_EVAL = 4
		};

		Shader(std::string file_path) : Shader(file_path.c_str()) {};
		Shader(const char* file_path);
		~Shader();

		void bind() const;
		void unbind() const;

		void set_uniform_1i(const std::string name, int value);
		void set_uniform_1ui(const std::string name, unsigned int value);
		void set_uniform_1f(const std::string name, float value);

		void set_uniform_2i(const std::string name, int i0, int i1);
		void set_uniform_2ui(const std::string name, unsigned int i0, unsigned int i1);
		void set_uniform_2f(const std::string name, float f0, float f1);

		void set_uniform_3i(const std::string name, int i0, int i1, int i2);
		void set_uniform_3ui(const std::string name, unsigned int i0, unsigned int i1, unsigned int i2);
		void set_uniform_3f(const std::string name, float f0, float f1, float f2);

		void set_uniform_4i(const std::string name, int i0, int i1, int i2, int i3);
		void set_uniform_4ui(const std::string name, unsigned int i0, unsigned int i1, unsigned int i2, unsigned int i3);
		void set_uniform_4f(const std::string name, float f0, float f1, float f2, float f3);

		void set_uniform_mat4x4(const std::string name, math::Mat4x4 mat);
		void set_uniform_vec3(const std::string name, math::Vec3 mat);

		int get_uniform_location(const std::string name) const;

		bool operator==(const Shader& shader) const {
			return id == shader.id;
		}
	};
}