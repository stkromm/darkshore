#include "graphics/shader.h"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "graphics/graphics.h"
#include "shader_type.h"
#include "core/logger/log.h"

namespace ds {
	namespace graphics
	{
		static int currently_bound_shader_look_up = -1;
		static std::unordered_map<std::string, int> location_look_up;

		struct ShaderSource
		{
			std::string vertex_source_code;
			std::string fragment_source_code;
		};

		static bool contains(const std::string& checked, std::string&& part)
		{
			return checked.find(part) != std::string::npos;
		}

		static ShaderSource parse_shader(const std::string& file_path)
		{
			std::ifstream stream(file_path);
			std::string line;
			std::stringstream shader_stream[2];

			ShaderType type = ShaderType::NONE;
			while (getline(stream, line))
			{
				if (contains(line, "#shader"))
				{
					if (contains(line, "#shader vertex"))
					{
						type = ShaderType::VERTEX;
					}
					else if (contains(line, "#shader fragment"))
					{
						type = ShaderType::FRAGMENT;
					}
					else if (contains(line, "#shader geometry"))
					{
						type = ShaderType::GEOMETRY;
					}
					else if (contains(line, "#shader tesselation_control"))
					{
						type = ShaderType::TESSELATION_CONTROL;
					}
					else if (contains(line, "#shader tesselation_eval"))
					{
						type = ShaderType::TESSELATION_EVAL;
					}
				}
				else
				{
					shader_stream[int(type)] << line << "\n";
				}
			}

			return { shader_stream[0].str(), shader_stream[1].str() };
		}

		static uint32_t compile_shader(const ShaderType type, const std::string& source_code)
		{
			GLCall(const uint32_t shader_id = glCreateShader(to_gl_shader_type(type)));
			const char* c_str_source_code = source_code.c_str();
			GLCall(glShaderSource(shader_id, 1, &c_str_source_code, nullptr));
			GLCall(glCompileShader(shader_id));

			int result;
			GLCall(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result));
			if (!result)
			{
				int length;
				GLCall(glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length));
				auto* message = static_cast<char *>(alloca(length * sizeof(char)));
				GLCall(glGetShaderInfoLog(shader_id, length, &length, message));
				LOG_INFO << "Failed shader compilation. Type: " << to_string(type) << LOG_END;
				LOG_INFO << message << LOG_END;
				GLCall(glDeleteShader(shader_id));
				return 0;
			}

			return shader_id;
		}

		static uint32_t create_shader(const std::string& vertex_shader, const std::string& fragment_shader)
		{
			GLCall(const uint32_t program_id = glCreateProgram());
			const uint32_t vertex_shader_id = compile_shader(ShaderType::VERTEX, vertex_shader);
			const uint32_t fragment_shader_id = compile_shader(ShaderType::FRAGMENT, fragment_shader);

			GLCall(glAttachShader(program_id, vertex_shader_id));
			GLCall(glAttachShader(program_id, fragment_shader_id));
			GLCall(glLinkProgram(program_id));
			GLCall(glValidateProgram(program_id));

			GLCall(glDeleteShader(vertex_shader_id));
			GLCall(glDeleteShader(fragment_shader_id));

			return program_id;
		}

		Shader::Shader(const char* shader_name)
		{
			const ShaderSource shader_source = parse_shader(shader_name);
			id = create_shader(shader_source.vertex_source_code, shader_source.fragment_source_code);
		}

		Shader::~Shader()
		{
			unbind();
			GLCall(glDeleteProgram(id));
			LOG_INFO << "Delete shader" << LOG_END;
		}

		void Shader::bind() const
		{
			if (currently_bound_shader_look_up != id)
			{
				LOG_INFO << "Binding shader " << id << LOG_END;
				currently_bound_shader_look_up = id;
				GLCall(glUseProgram(id));
			}
		}

		void Shader::unbind() const
		{
			if (currently_bound_shader_look_up != 0)
			{
				LOG_INFO << "Unbinding shader " << id << LOG_END;
				currently_bound_shader_look_up = 0;
				GLCall(glUseProgram(0));
			}
		}

		void Shader::set_uniform_1i(std::string name, const int value)
		{
			GLCall(glUniform1i(get_uniform_location(std::move(name)), value));
		}

		void Shader::set_uniform_1ui(std::string name, const uint32_t value)
		{
			GLCall(glUniform1ui(get_uniform_location(std::move(name)), value));
		}

		void Shader::set_uniform_1f(std::string name, const float value)
		{
			GLCall(glUniform1f(get_uniform_location(std::move(name)), value));
		}

		void Shader::set_uniform_2i(std::string name, const int32_t i0, const int32_t i1)
		{
			GLCall(glUniform2i(get_uniform_location(std::move(name)), i0, i1));
		}

		void Shader::set_uniform_2ui(std::string name, const uint32_t i0, const uint32_t i1) const
		{
			GLCall(glUniform2ui(get_uniform_location(std::move(name)), i0, i1));
		}

		void Shader::set_uniform_2f(std::string name, const float f0, const float f1)
		{
			GLCall(glUniform2f(get_uniform_location(std::move(name)), f0, f1));
		}

		void Shader::set_uniform_3i(std::string name, const  int32_t i0, const int32_t i1, const int32_t i2)
		{
			GLCall(glUniform3i(get_uniform_location(std::move(name)), i0, i1, i2));
		}

		void Shader::set_uniform_3ui(std::string name, const uint32_t i0, const uint32_t i1, const  uint32_t i2)
		{
			GLCall(glUniform3ui(get_uniform_location(std::move(name)), i0, i1, i2));
		}

		void Shader::set_uniform_3f(std::string name, const float f0, const float f1, const float f2)
		{
			GLCall(glUniform3f(get_uniform_location(std::move(name)), f0, f1, f2));
		}

		void Shader::set_uniform_4f(std::string name, const float f0, const float f1, const float f2, const  float f3)
		{
			GLCall(glUniform4f(get_uniform_location(std::move(name)), f0, f1, f2, f3));
		}

		void Shader::set_uniform_4ui(std::string name, const uint32_t i0, const uint32_t i1, const uint32_t i2, const uint32_t i3)
		{
			GLCall(glUniform4ui(get_uniform_location(std::move(name)), i0, i1, i2, i3));
		}

		void Shader::set_uniform_4i(std::string name, const int32_t i0, const int32_t i1, const int32_t i2, const  int32_t i3)
		{
			GLCall(glUniform4i(get_uniform_location(std::move(name)), i0, i1, i2, i3));
		}

		void Shader::set_uniform_mat4x4(std::string name, math::Mat4x4 mat)
		{
			GLCall(glUniformMatrix4fv(get_uniform_location(std::move(name)), 1, GL_FALSE, mat.data()));
		}

		void Shader::set_uniform_vec3(std::string name, const math::Vec3 vec)
		{
			float d[3]{
				vec.x, vec.y, vec.z
			};
			GLCall(glUniform3fv(get_uniform_location(std::move(name)), 1, d));
		}

		int Shader::get_uniform_location(std::string name) const
		{
			const auto lookup = location_look_up.find(name);
			if (lookup != location_look_up.end())
			{
				return lookup->second;
			}
			const int location = glGetUniformLocation(id, name.c_str());
			if (location == -1)
			{
				LOG_INFO << "Non existing shader uniform location: " << name << LOG_END;
			}
			location_look_up.emplace(name, location);
			return location;
		}
	}
}