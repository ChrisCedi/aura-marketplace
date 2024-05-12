#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

const float amplitude = 0.1;  
const float frequency = 1.7;  
const float PI = 3.14159265359;

void main()
{
    float wave = amplitude * sin(PI * aPos.x * frequency + time);
    vec3 newPosition = vec3(aPos.x, aPos.y, aPos.z  + wave );
    gl_Position = projection * view * model * vec4(newPosition, 1.0);
    TexCoords = aTexCoords;
}
