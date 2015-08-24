#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;
attribute vec4 color;
attribute float tid;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view = mat4(1.0);
uniform mat4 model = mat4(1.0);

varying vec3 in_position;
varying vec2 in_texCoord;
varying vec3 in_normal;
varying vec4 in_color;
varying float in_tid;


void main()
{
	gl_Position = projection * transform * vec4(position, 1.0);
	in_position = gl_Position;
	in_texCoord = texCoord;
	in_normal = normal;
	in_color = color;
	in_tid = tid;
}
