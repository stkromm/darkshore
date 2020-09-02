#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tc;
layout(location = 2) in uint tindex;
layout(location = 3) in vec4 color;

uniform mat4 pr_matrix;

out uint index;
out vec2 tex_coord;
out vec4 tint;

void main()
{
	gl_Position = pr_matrix * position;
	index = tindex;
	tex_coord = tc;
	tint = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in uint index;
in vec2 tex_coord;
in vec4 tint;

uniform sampler2D tex[8];

void main()
{
	color = texture(tex[0], tex_coord);
	if (color.a == 0)
	{
		discard;
	}
	color = vec4(1,1,1,color.a);
};
