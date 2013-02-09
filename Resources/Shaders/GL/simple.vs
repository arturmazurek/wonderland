uniform mat4 uModelView;
uniform mat4 uProjection;

attribute vec3 aPosition;

void main() {
	gl_Position = uModelView * uProjection * aPosition;
}