#version 450
in vec4 vColor;
in vec3 vNormal;
in vec3 vPos;
in vec3 lightPos;
in vec3 lightColour;

out vec4 fColor;

void main()
{
//    vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);
//    vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColour;
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - vPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour;

    vec4 result = vec4((ambient + diffuse), 1.0) * vColor;

    fColor = result;

    //fColor = vColor;
}
