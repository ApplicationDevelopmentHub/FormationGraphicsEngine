#version 330 core
layout(location=0) in vec3 pos;
layout(location=1) in vec4 color;
out vec4 fragmentColor;
void main(){
	gl_Position=vec4(pos,1.0);  //4th param is homogenous coordinate
	fragmentColor=color;
}