#version 150

uniform vec4 uColor;

in vec3 aPositionPs;

out vec4 fragColor;

void main() {
    vec4 color = uColor;
    color.r = aPositionPs.x / 5;
    color.g = aPositionPs.y / 5;
    color.b = aPositionPs.z / 5;
	fragColor = color;
}