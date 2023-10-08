#version 400

layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 model;

void main()
{
	
	//...pode ter mais linhas de código aqui!
	gl_Position = projection * model * vec4(position.x, position.y, position.z, 1.0);
}