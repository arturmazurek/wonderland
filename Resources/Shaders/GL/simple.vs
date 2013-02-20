#version 150

uniform mat4 uModelView;
uniform mat4 uProjection;

in vec3 aPosition;
in vec3 aColor;
in vec3 aUv;

void main() {
	gl_Position = uModelView * uProjection * vec4(aPosition, 1.0);
}