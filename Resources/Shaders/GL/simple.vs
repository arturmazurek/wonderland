#version 150

uniform mat4 uModelView;
uniform mat4 uProjection;

in vec3 aPosition;
in vec3 aNormal;
in vec2 aUv;

out vec3 aPositionPs;

void main() {
	gl_Position =  uProjection * uModelView * vec4(aPosition, 1.0);
    aPositionPs = aPosition;
}