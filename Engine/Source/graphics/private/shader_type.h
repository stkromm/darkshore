#pragma once

namespace ds {
	namespace graphics
	{
		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1,
			GEOMETRY = 2,
			TESSELATION_CONTROL = 3,
			TESSELATION_EVAL = 4
		};

		inline std::string to_string(const ShaderType type)
		{
			switch (type)
			{
			case ShaderType::VERTEX:
				return "GL_VERTEX_SHADER";
			case ShaderType::FRAGMENT:
				return "GL_FRAGMENT_SHADER";
			case ShaderType::GEOMETRY:
				return "GL_GEOMETRY_SHADER";
			case ShaderType::TESSELATION_CONTROL:
				return "GL_TESS_EVALUATION_SHADER";
			case ShaderType::TESSELATION_EVAL:
				return "GL_TESS_CONTROL_SHADER";
			default:
				break;
			}
			ASSERT(false);
			return nullptr;
		}

		inline uint32_t to_gl_shader_type(const ShaderType type)
		{
			switch (type)
			{
			case ShaderType::VERTEX:
				return GL_VERTEX_SHADER;
			case ShaderType::FRAGMENT:
				return GL_FRAGMENT_SHADER;
			case ShaderType::GEOMETRY:
				return GL_GEOMETRY_SHADER;
			case ShaderType::TESSELATION_CONTROL:
				return GL_TESS_EVALUATION_SHADER;
			case ShaderType::TESSELATION_EVAL:
				return GL_TESS_CONTROL_SHADER;
			default:
				break;
			}
			ASSERT(false);
			return 0;
		}
	}
}