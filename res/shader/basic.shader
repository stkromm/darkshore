#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tc;
layout(location = 2) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix;

out DATA{
	vec4 color;
	vec2 tc;
} vs_out;

void main() 
{
	gl_Position = pr_matrix * vw_matrix * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in DATA{
	vec4 color;
	vec2 tc;
} fs_in;

uniform sampler2D tex;

void main() 
{
	color = texture(tex, fs_in.tc * 0.001);
	if (color.a == 0)
	{
		discard;
	}
	color.a -= fs_in.color.a;
};