#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in float rotation;
layout(location = 2) in float lifetime;
layout(location = 3) in vec2 speed;
layout(location = 4) in vec4 color;
layout(location = 5) in float size;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix;

out vec2 tex_coord;
out vec4 tint;

void main()
{
	gl_Position = pr_matrix * vw_matrix * position;
	tex_coord = tc;
	tint = color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 tex_coord;
in vec4 tint;

void main()
{
	color = texture(tex, tex_coord);
	//color += tint;
	if (color.a == 0)
	{
		discard;
	}
};
