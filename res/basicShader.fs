#version 120

varying vec2 texCoord0;

uniform sampler2D diffuse;

varying vec3 in_position;
varying vec2 in_texCoord;
varying vec3 in_normal;
varying vec4 in_color
varying float in_tid;

void main()
{
//    vec4 texColor = fs_in.color;
//	if (fs_in.tid > 0.0)
//	{
//		int tid = int(fs_in.tid - 0.5);
//      texColor = fs_in.color * texture(textures[tid], fs_in.uv);
//  }
//    color = texColor;
    gl_FragColor = texture2D(diffuse, in_texCoord);
	

//	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
