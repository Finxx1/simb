#line 1
#ifdef VERT

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

out vec2 st;

uniform vec4 pos;
uniform mat4 rot;
uniform mat4 proj;

void main() {
    gl_Position = proj * ((pos + vec4(position, 1.0)) * rot);
    st = uv;
}

#elif defined(FRAG)

out vec4 color;
uniform sampler2D tex;
in vec2 st;

void main() {
    color = texture(tex, vec2(st.s, 1 - st.t));
}

#endif