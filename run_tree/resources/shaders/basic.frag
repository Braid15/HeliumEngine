#version 330 core

out vec4 frag_color;

uniform vec4 color;
uniform vec2 light_pos;

in vec4 pos;
in vec4 out_color;

void main() {
	float intensity = 1.0 / length(pos.xy - light_pos);
	frag_color = out_color * intensity;
}