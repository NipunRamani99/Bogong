#version 330 core
in vec2 tex_coord;
out vec4 frag_colour;
uniform sampler2D s;
void main() {
	frag_colour = texture(s,tex_coord);
}