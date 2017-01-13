#version 440
layout(binding = 0) uniform sampler2DArray base_Texture;

in VS_OUT{
	vec3 texcoord;
	vec3 position;
	float spriteCounter;
} fs_in;

void main(){
	
	gl_FragColor = texture(base_Texture,vec3(fs_in.texcoord.x,fs_in.texcoord.y,fs_in.spriteCounter));
}