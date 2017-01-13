#version 440
layout(binding = 0) uniform sampler2D tex_Object;
layout(binding = 1) uniform sampler2D joshTex_Object;

in VS_OUT{
	vec2 texcoord;
	vec3 position;
	float loopCounter;
} fs_in;

out vec3 color;

void main(){
	vec4 josh = texture(joshTex_Object,fs_in.texcoord);
	vec4 tex = texture(tex_Object,fs_in.texcoord);
	gl_FragColor = mix(josh,tex,sin(fs_in.loopCounter));
}