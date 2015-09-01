#version 330

in DATA{
 vec4 position;
 vec2 texCoord;
 vec3 normal;
 vec4 color;
 float tid;
} vs_in;

out vec4 color;


//uniform sampler2D diffuse;
uniform sampler2D textures[32];

void main()
{
    color = vs_in.color;
    if(vs_in.tid > 0.0)
    { // Correct to use multiple textures - texture2D(mytexture, mycoord)
       //gl_FragColor = texture2D(diffuse, vs_in.texCoord) * vs_in.color;
       int tid = int(vs_in.tid + 0.5);
       color = texture(textures[tid], vs_in.texCoord) * vs_in.color;
    }
}
