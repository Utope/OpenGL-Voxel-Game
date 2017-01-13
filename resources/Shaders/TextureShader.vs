#version 440

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;

layout(location = 0) uniform mat4 projectionView;
layout(location = 1) uniform float loopCounter;

out VS_OUT { 
	vec2 texcoord;
	vec3 position;
	float loopCounter;
} vs_out;

void main(){
	gl_Position = projectionView * vec4(position,1);
	vs_out.position = position;
	vs_out.texcoord = texcoord;
	vs_out.loopCounter = loopCounter;
}