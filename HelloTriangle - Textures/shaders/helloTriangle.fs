#version 400

uniform vec4 inputColor;
out vec4 color;

in vec2 texcoord;
uniform sampler2D texbuffer;

void main()
{
	color = texture(texbuffer,texcoord);
}