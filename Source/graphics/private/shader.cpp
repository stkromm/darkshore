#include "graphics/shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "platform/resource_handle.h"

namespace graphics {
	struct ShaderSource {
		std::string vertex_source_code;
		std::string fragment_source_code;
	};

	static std::string to_string(Shader::Type type) {
		switch (type) {
		case Shader::Type::VERTEX:
			return "GL_VERTEX_SHADER";
		case Shader::Type::FRAGMENT:
			return "GL_FRAGMENT_SHADER";
		case Shader::Type::GEOMETRY:
			return "GL_GEOMETRY_SHADER";
		case Shader::Type::TESSELATION_CONTROL:
			return "GL_TESS_EVALUATION_SHADER";
		case Shader::Type::TESSELATION_EVAL:
			return "GL_TESS_CONTROL_SHADER";
		}
		ASSERT(false);
		return 0;
	}

	static uint32_t to_gl_shader_type(Shader::Type type) {
		switch (type) {
		case Shader::Type::VERTEX:
			return GL_VERTEX_SHADER;
		case Shader::Type::FRAGMENT:
			return GL_FRAGMENT_SHADER;
		case Shader::Type::GEOMETRY:
			return GL_GEOMETRY_SHADER;
		case Shader::Type::TESSELATION_CONTROL:
			return GL_TESS_EVALUATION_SHADER;
		case Shader::Type::TESSELATION_EVAL:
			return GL_TESS_CONTROL_SHADER;
		}
		ASSERT(false);
		return 0;
	}

	static ShaderSource parse_shader(const std::string file_path) {
		std::ifstream stream(file_path);
		std::string line;
		std::stringstream shader_stream[2];

		Shader::Type type = Shader::Type::NONE;
		while (getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("#shader vertex") != std::string::npos) {
					type = Shader::Type::VERTEX;
				}
				else if (line.find("#shader fragment") != std::string::npos) {
					type = Shader::Type::FRAGMENT;
				}
				else if (line.find("#shader geometry") != std::string::npos) {
					type = Shader::Type::GEOMETRY;
				}
				else if (line.find("#shader tesselation_control") != std::string::npos) {
					type = Shader::Type::TESSELATION_CONTROL;
				}
				else if (line.find("#shader tesselation_eval") != std::string::npos) {
					type = Shader::Type::TESSELATION_EVAL;
				}

			}
			else {
				shader_stream[(int)type] << line << "\n";
			}
		}

		return { shader_stream[0].str(), shader_stream[1].str() };
	}

	static uint32_t compile_shader(const Shader::Type type, const std::string& source_code) {
		GLCall(const uint32_t shader_id = glCreateShader(to_gl_shader_type(type)));
		const char* c_str_source_code = source_code.c_str();
		GLCall(glShaderSource(shader_id, 1, &c_str_source_code, nullptr));
		GLCall(glCompileShader(shader_id));

		int result;
		GLCall(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result));
		if (!result) {
			int length;
			GLCall(glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length));
			char* message = (char *)alloca(length * sizeof(char));
			GLCall(glGetShaderInfoLog(shader_id, length, &length, message));
			std::cout << "Failed shader compilation. Type: " << to_string(type) << std::endl;
			std::cout << message << std::endl;
			GLCall(glDeleteShader(shader_id));
			return 0;
		}

		return shader_id;
	}

	static uint32_t create_shader(const std::string& vertex_shader, const std::string& fragment_shader) {
		GLCall(const uint32_t program_id = glCreateProgram());
		const uint32_t vertex_shader_id = compile_shader(Shader::Type::VERTEX, vertex_shader);
		const uint32_t fragment_shader_id = compile_shader(Shader::Type::FRAGMENT, fragment_shader);

		GLCall(glAttachShader(program_id, vertex_shader_id));
		GLCall(glAttachShader(program_id, fragment_shader_id));
		GLCall(glLinkProgram(program_id));
		GLCall(glValidateProgram(program_id));

		GLCall(glDeleteShader(vertex_shader_id));
		GLCall(glDeleteShader(fragment_shader_id));

		return program_id;
	}

	Shader::Shader(const char* shader_name) {
		const ShaderSource shader_source = parse_shader(get_res_folder_path(AssetType::SHADER, shader_name));
		std::cout << "Shader created" << std::endl;
		id = create_shader(shader_source.vertex_source_code, shader_source.fragment_source_code);
	}

	Shader::~Shader() {
		unbind();
		GLCall(glDeleteProgram(id));
	}

	void Shader::bind() const {
		GLCall(glUseProgram(id));
	}


	void Shader::unbind() const {
		GLCall(glUseProgram(0));
	}


	void Shader::set_uniform_1i(const std::string name, int value)
	{
		GLCall(glUniform1i(get_uniform_location(name), value));
	}

	void Shader::set_uniform_1ui(const std::string name, uint32_t value)
	{
		GLCall(glUniform1ui(get_uniform_location(name), value));
	}

	void Shader::set_uniform_1f(const std::string name, float value)
	{
		GLCall(glUniform1f(get_uniform_location(name), value));
	}

	void Shader::set_uniform_2i(const std::string name, int i0, int i1)
	{
		GLCall(glUniform2i(get_uniform_location(name), i0, i1));
	}

	void Shader::set_uniform_2ui(const std::string name, uint32_t i0, uint32_t i1)
	{
		GLCall(glUniform2ui(get_uniform_location(name), i0, i1));
	}

	void Shader::set_uniform_2f(const std::string name, float f0, float f1)
	{
		GLCall(glUniform2f(get_uniform_location(name), f0, f1));
	}

	void Shader::set_uniform_3i(const std::string name, int i0, int i1, int i2)
	{
		GLCall(glUniform3i(get_uniform_location(name), i0, i1, i2));
	}

	void Shader::set_uniform_3ui(const std::string name, uint32_t i0, uint32_t i1, uint32_t i2)
	{
		GLCall(glUniform3ui(get_uniform_location(name), i0, i1, i2));
	}

	void Shader::set_uniform_3f(const std::string name, float f0, float f1, float f2)
	{
		GLCall(glUniform3f(get_uniform_location(name), f0, f1, f2));
	}

	void Shader::set_uniform_4f(const std::string name, float f0, float f1, float f2, float f3)
	{
		GLCall(glUniform4f(get_uniform_location(name), f0, f1, f2, f3));
	}

	void Shader::set_uniform_4ui(const std::string name, uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3)
	{
		GLCall(glUniform4ui(get_uniform_location(name), i0, i1, i2, i3));
	}

	void Shader::set_uniform_4i(const std::string name, int i0, int i1, int i2, int i3)
	{
		GLCall(glUniform4i(get_uniform_location(name), i0, i1, i2, i3));
	}

	void Shader::set_uniform_mat4x4(const std::string name, math::Mat4x4 mat)
	{
		GLCall(glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, mat.data()));
	}

	void Shader::set_uniform_vec3(const std::string name, math::Vec3 vec)
	{
		float d[3]{
			vec.x, vec.y, vec.z
		};
		GLCall(glUniform3fv(get_uniform_location(name), 1, d));
	}

	static std::unordered_map<std::string, int> location_look_up;

	int Shader::get_uniform_location(const std::string name) const {
		auto lookup = location_look_up.find(name);
		if (lookup != location_look_up.end()) {
			return lookup->second;
		}
		else {
			GLCall(const int location = glGetUniformLocation(id, name.c_str()));
			if (location == -1)
			{
				std::cout << "Non existing shader uniform location: " << name << std::endl;
			}
			location_look_up.emplace(name, location);
			return location;
		}
	}
}