#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec4 color;
layout (location = 4) in float tid;


uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view = mat4(1.0);
uniform mat4 model = mat4(1.0);

out DATA{
 vec4 position;
 vec2 texCoord;
 vec3 normal;
 vec4 color;
 float tid;
} vs_out;


void main()
{
	gl_Position = projection * transform * vec4(position, 1.0);
	vs_out.position = gl_Position;
	vs_out.texCoord = texCoord;
	vs_out.normal = normal;
	vs_out.color = color;
	vs_out.tid = tid;
}
