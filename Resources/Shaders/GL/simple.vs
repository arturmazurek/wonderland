#version 150

uniform mat4 uModelView;
uniform mat4 uProjection;

in vec3 aPosition;

void main() {
	gl_Position = uModelView * uProjection * vec4(aPosition, 1.0);
}