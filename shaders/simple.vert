#version 450
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec4 vColor;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

uniform int pointSize;
uniform int zFactorValue;
uniform int zOffsetValue;

uniform int surfaceValue;

vec3 bed_colour_map[9] = vec3[9] (
    vec3(1.00000f, 1.00000f, 0.89804f),
    vec3(1.00000f, 1.00000f, 0.73725f),
    vec3(0.99608f, 0.89020f, 0.56863f),
    vec3(0.99608f, 0.76863f, 0.30980f),
    vec3(0.99608f, 0.60000f, 0.16078f),
    vec3(0.92549f, 0.43922f, 0.07843f),
    vec3(0.80000f, 0.29804f, 0.00784f),
    vec3(0.60000f, 0.20392f, 0.01569f),
    vec3(0.40000f, 0.14510f, 0.02353f)
);

vec3 ice_colour_map[9] = vec3[9] (
    vec3(1, 1, 0.850),
    vec3(0.929, 0.972, 0.694),
    vec3(0.780, 0.913, 0.705),
    vec3(0.498, 0.803, 0.733),
    vec3(0.254, 0.713, 0.768),
    vec3(0.113, 0.568, 0.752),
    vec3(0.133, 0.368, 0.658),
    vec3(0.145, 0.203, 0.580),
    vec3(0.031, 0.113, 0.345)
);


void main()
{
    float normal = (9 - 0) * (position.z - 0) / (4.621 - 0) + 0;
    int index = int(normal);
    vec3 colour;

    gl_PointSize = pointSize;
    gl_Position = cameraToView * worldToCamera * modelToWorld * vec4(position *vec3(1,1,zFactorValue) + vec3(0,0,zOffsetValue), 1.0);

    switch(surfaceValue)
    {
    case 0:
        colour = ice_colour_map[index];
        vColor = vec4(colour, 1);
        break;
    case 1:
        colour = bed_colour_map[index];
        vColor = vec4(colour, 1);
        break;
    case 2:
        vColor = vec4(color, 1.0);
        break;
    }

}



