#version 330 core

in vec3 vert_color;
out vec4 frag_color;

vec3 lum = vec3(0.299f, 0.587f, 0.114f);

void main()
{
		frag_color = vec4(vert_color, 1.0f);
};
