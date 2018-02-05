#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 in_color;

uniform mat4 projection_matrix = mat4(1.0);
uniform mat4 view_matrix	   = mat4(1.0);
uniform mat4 model_matrix	   = mat4(1.0);

out vec4 pos;
out vec4 out_color;

void main() {
	gl_Position = projection_matrix * view_matrix * model_matrix * position;
	pos			= model_matrix * position;
	out_color   = in_color;
}