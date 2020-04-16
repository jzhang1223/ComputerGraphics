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
uniform sampler2D colorTex;              // our primary texture
uniform mat4 view;                  // we need the view matrix for highlights
uniform PointLight pointLights[1];  // Our lights

void main() {
  // Set our output fragment color to whatever we pull from our input texture (Note, change 'tex' to whatever the sampler is named)
  //fragColor = texture(colorTex, texCoords);
  //fragColor = vec4(vec3(1.0 - texture(colorTex, texCoords)), 1.0);

  float offset = 1.0/30.0;

  vec2 offsets[9] = vec2[](
        vec2(-offset, offset),
        vec2(0.0f, offset),
        vec2(offset, offset),
        vec2(-offset, 0.0f),
        vec2(0.0f, 0.0f),
        vec2(offset, 0.0f),
        vec2(-offset, -offset),
        vec2(0.0f, -offset),
        vec2(offset, -offset)
        );

  float kernel[9] = float[](1, 1, 1,
                            1, -8, 1,
                            1, 1, 1);

  
  vec3 sampleTex[9];
  for(int i = 0; i < 9; i++) {
    sampleTex[i] = vec3(texture(colorTex, texCoords.st + offsets[i]));
  }

  vec3 col = vec3(0.0);
  for(int i = 0; i < 9; i++) {
    col += sampleTex[i] * kernel[i];
  }

  fragColor = vec4(col, 1.0);

}