#version 330

// Take in our texture coordinate from our vertex shader
in vec2 texCoords;
// And our normal
in vec3 norm;
// And our fragment position for lighting
in vec3 fragPos;

// We always define a fragment color that we output.
out vec4 fragColor;

// Define our light(s)
struct PointLight {
    vec3 color;
    vec3 position;
    float ambientIntensity;
    float specularIntensity;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Maintain our uniforms.
uniform sampler2D tex;              // our primary texture
uniform mat4 view;                  // we need the view matrix for highlights
uniform PointLight pointLights[1];  // Our lights

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

  vec3 lightDir = normalize(light.position - fragPos);

  // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);

  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 10);

  // attenuation
  float distance = length(light.position - fragPos);

  vec3 ambient = light.ambientIntensity * light.color;
  vec3 diffuse = light.color * diff;
  vec3 specular = light.specularIntensity * spec * light.color;

  return (ambient + diffuse + specular);

}

void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  vec3 diffuse = texture(tex, texCoords).rgb;

  vec3 normal = normalize(norm);
  vec3 viewPos = vec3(0.0, 0.0, 0.0);
  vec3 viewDir = normalize(viewPos - fragPos);

  vec3 lighting;
  lighting = CalcPointLight(pointLights[0], norm, fragPos, viewDir);

  fragColor = vec4(diffuse * lighting, 1.0); 
}