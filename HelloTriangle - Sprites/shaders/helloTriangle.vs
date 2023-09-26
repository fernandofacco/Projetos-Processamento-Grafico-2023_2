#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texc;

uniform mat4 projection;
uniform mat4 model;

out vec2 texcoord;

void main()
{
	
	//...pode ter mais linhas de código aqui!
	gl_Position = projection * model * vec4(position, 1.0);
	texcoord = texc;
}