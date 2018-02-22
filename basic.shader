#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tc;
layout(location = 2) in vec4 color;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix;

out vec2 tex_coord;
out vec4 tint;

void main() 
{
	//gl_Position = pr_matrix * position;
	gl_Position = pr_matrix * vw_matrix * position;
	tex_coord = tc;
	tint = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 tex_coord;
in vec4 tint;

uniform sampler2D tex;

void main() 
{
	//color = vec4(0, 1, 0, 1);
	//color = texture(tex, tex_coord);

	color = texture(tex, tex_coord);
	if (color.a == 0)
	{
		discard;
	}
	color.a -= tint.a;
};