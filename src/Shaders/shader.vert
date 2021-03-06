#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;

out vec3 pass_pos;
out vec3 pass_color;
out vec3 pass_normal;
out vec2 pass_uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);

	pass_pos = (model * vec4(pos, 1.0)).xyz;
	// Only apply rotation to normal
	pass_normal = (model * vec4(normal, 0)).xyz;
	pass_uv = uv;
	pass_color = color;
}