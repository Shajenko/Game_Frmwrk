#version 330

in DATA{
 vec4 position;
 vec2 texCoord;
 vec3 normal;
 vec4 color;
 float tid;
} vs_in;

out vec4 color;

uniform sampler2D textures[32];

void main()
{
	// Calculate gradients - cannot have automatic gradients with non-uniform control flow
	vec2 texDx = dFdx(vs_in.texCoord);
	vec2 texDy = dFdy(vs_in.texCoord);

    color = vs_in.color;
    if(vs_in.tid > 0.0)
    { 
       int tid = int(vs_in.tid + 0.5);

       if(tid == 0)
			color = textureGrad(textures[0], vs_in.texCoord, texDx, texDy);
//            color = texture(textures[0], vs_in.texCoord) * vs_in.color;
       if(tid == 1)
			color = textureGrad(textures[1], vs_in.texCoord, texDx, texDy);
       if(tid == 2)
			color = textureGrad(textures[2], vs_in.texCoord, texDx, texDy);
       if(tid == 3)
			color = textureGrad(textures[3], vs_in.texCoord, texDx, texDy);
       if(tid == 4)
			color = textureGrad(textures[4], vs_in.texCoord, texDx, texDy);
       if(tid == 5)
			color = textureGrad(textures[5], vs_in.texCoord, texDx, texDy);
       if(tid == 6)
			color = textureGrad(textures[6], vs_in.texCoord, texDx, texDy);
       if(tid == 7)
			color = textureGrad(textures[7], vs_in.texCoord, texDx, texDy);
       if(tid == 8)
			color = textureGrad(textures[8], vs_in.texCoord, texDx, texDy);
       if(tid == 9)
			color = textureGrad(textures[9], vs_in.texCoord, texDx, texDy);
       if(tid == 10)
			color = textureGrad(textures[10], vs_in.texCoord, texDx, texDy);
       if(tid == 11)
			color = textureGrad(textures[11], vs_in.texCoord, texDx, texDy);
       if(tid == 12)
			color = textureGrad(textures[12], vs_in.texCoord, texDx, texDy);
       if(tid == 13)
			color = textureGrad(textures[13], vs_in.texCoord, texDx, texDy);
       if(tid == 14)
			color = textureGrad(textures[14], vs_in.texCoord, texDx, texDy);
       if(tid == 15)
			color = textureGrad(textures[15], vs_in.texCoord, texDx, texDy);
       if(tid == 16)
			color = textureGrad(textures[16], vs_in.texCoord, texDx, texDy);
       if(tid == 17)
			color = textureGrad(textures[17], vs_in.texCoord, texDx, texDy);
       if(tid == 18)
			color = textureGrad(textures[18], vs_in.texCoord, texDx, texDy);
       if(tid == 19)
			color = textureGrad(textures[19], vs_in.texCoord, texDx, texDy);
       if(tid == 20)
			color = textureGrad(textures[20], vs_in.texCoord, texDx, texDy);
       if(tid == 21)
			color = textureGrad(textures[21], vs_in.texCoord, texDx, texDy);
       if(tid == 22)
			color = textureGrad(textures[22], vs_in.texCoord, texDx, texDy);
       if(tid == 23)
			color = textureGrad(textures[23], vs_in.texCoord, texDx, texDy);
       if(tid == 24)
			color = textureGrad(textures[24], vs_in.texCoord, texDx, texDy);
       if(tid == 25)
			color = textureGrad(textures[25], vs_in.texCoord, texDx, texDy);
       if(tid == 26)
			color = textureGrad(textures[26], vs_in.texCoord, texDx, texDy);
       if(tid == 27)
			color = textureGrad(textures[27], vs_in.texCoord, texDx, texDy);
       if(tid == 28)
			color = textureGrad(textures[28], vs_in.texCoord, texDx, texDy);
       if(tid == 29)
			color = textureGrad(textures[29], vs_in.texCoord, texDx, texDy);
       if(tid == 30)
			color = textureGrad(textures[30], vs_in.texCoord, texDx, texDy);
       if(tid == 31)
			color = textureGrad(textures[31], vs_in.texCoord, texDx, texDy);
		color = color * vs_in.color;
    }
}
