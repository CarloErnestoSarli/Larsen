#version 450
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 vNormal;
out vec4 vColor;
out vec3 vPos;
out vec3 lightPos;
out vec3 lightColour;

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;

uniform vec3 lightlPositionValue;
uniform vec3 lightColourValue;

uniform int pointSize;
uniform int zFactorValue;
uniform int zOffsetValue;
uniform int iceThicknessMapSelValue;
uniform int bedMapSelValue;
uniform int surfaceValue;

vec3 ice_colour_map1[9] = vec3[9] (
    vec3(1, 1, 0.850),
    vec3(0.929, 0.972, 0.694),
    vec3(0.815, 0.819, 0.901),
    vec3(0.498, 0.803, 0.733),
    vec3(0.254, 0.713, 0.768),
    vec3(0.113, 0.568, 0.752),
    vec3(0.133, 0.368, 0.658),
    vec3(0.145, 0.203, 0.580),
    vec3(0.031, 0.113, 0.345)
);

vec3 ice_colour_map2[9] = vec3[9] (
    vec3(1, 0.968, 0.984),
    vec3(0.925, 0.905, 0.949),
    vec3(0.780, 0.913, 0.705),
    vec3(0.650, 0.741, 0.858),
    vec3(0.454, 0.662, 0.811),
    vec3(0.211, 0.564, 0.752),
    vec3(0.019, 0.439, 0.690),
    vec3(0.015, 0.352, 0.552),
    vec3(0.007, 0.219, 0.345)
);

vec3 ice_colour_map3[9] = vec3[9] (
    vec3(1, 1, 1),
    vec3(0.941, 0.941, 0.941),
    vec3(0.850, 0.850, 0.850),
    vec3(0.741, 0.741, 0.741),
    vec3(0.588, 0.588, 0.588),
    vec3(0.450, 0.450, 0.450),
    vec3(0.321, 0.321, 0.321),
    vec3(0.145, 0.145, 0.145),
    vec3(0, 0, 0)
);

vec3 bed_colour_map1[9] = vec3[9] (
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

vec3 bed_colour_map2[9] = vec3[9] (
    vec3(1, 0.960, 0.941),
    vec3(0.996, 0.878, 0.823),
    vec3(0.988, 0.733, 0.631),
    vec3(0.988, 0.572, 0.447),
    vec3(0.984, 0.415, 0.290),
    vec3(0.937, 0.231, 0.172),
    vec3(0.796, 0.094, 0.113),
    vec3(0.647, 0.058, 0.082),
    vec3(0.403, 0, 0.050)
);

vec3 bed_colour_map3[9] = vec3[9] (
    vec3(0.968, 0.988, 0.992),
    vec3(0.898, 0.960, 0.976),
    vec3(0.8, 0.925, 0.901),
    vec3(0.6, 0.847, 0.788),
    vec3(0.4, 0.760, 0.643),
    vec3(0.254, 0.682, 0.462),
    vec3(0.137, 0.545, 0.270),
    vec3(0, 0.427, 0.172),
    vec3(0, 0.266, 0.105)
);

vec3 surface_colour_map[9] = vec3[9] (
    vec3(0.968, 0.988, 0.992),
    vec3(0.898, 0.960, 0.976),
    vec3(0.8, 0.925, 0.901),
    vec3(0.6, 0.847, 0.788),
    vec3(0.4, 0.760, 0.643),
    vec3(0.254, 0.682, 0.462),
    vec3(0.137, 0.545, 0.270),
    vec3(0, 0.427, 0.172),
    vec3(0, 0.266, 0.105)
);

void main()
{
    float norm= (9 - 0) * (position.z - 0) / (4.621 - 0) + 0;
    int index = int(norm);
    vec3 colour;
    vec3 ice_colour_map[9];
    vec3 bed_colour_map[9];

    gl_PointSize = pointSize;
    gl_Position = cameraToView * worldToCamera * modelToWorld * vec4(position *vec3(1,1,zFactorValue) + vec3(0,0,zOffsetValue), 1.0);

    vPos = vec3(modelToWorld * vec4(position, 1.0));

    lightPos = lightlPositionValue;

    lightColour = lightColourValue;

    vNormal = mat3(transpose(inverse(modelToWorld))) * normal;

    switch(iceThicknessMapSelValue)
    {
    case 0:
        ice_colour_map = ice_colour_map1;
        break;
    case 1:
        ice_colour_map = ice_colour_map2;
        break;
    case 2:
        ice_colour_map = ice_colour_map3;
        break;
//    case 3:
//        break;
    }

    switch(bedMapSelValue)
    {
    case 0:
        bed_colour_map = bed_colour_map1;
        break;
    case 1:
        bed_colour_map = bed_colour_map2;
        break;
    case 2:
        bed_colour_map = bed_colour_map3;
        break;
//    case 3:
//        break;
    }

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
        colour  = surface_colour_map[index];
        vColor = vec4(colour, 1.0);
        break;
    case 3:
        vColor = vec4(vec3(1,1,1), 1.0);
        break;
    }

}



