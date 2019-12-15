#version 400 core

const float exposure=0.0034;
const float decay=1.f;
const float density=0.84;
const float weight=2.15; // 7.65
uniform sampler2D firstPass;
uniform sampler2D secondPass;
in vec2 uv;
const vec2 lightPositionOnScreen = vec2(0.5,0.5);
out vec4 fragColor;
const int NUM_SAMPLES = 100;

void main()
{
    vec2 deltaTextCoord = vec2( uv - lightPositionOnScreen);
    vec2 textCoord = uv;
    deltaTextCoord *= 1.0 /  float(NUM_SAMPLES) * density;
    float illuminationDecay = 1.0;

    vec4 crep = vec4(0.0);
    for(int i=0; i < NUM_SAMPLES ; i++) {
             textCoord -= deltaTextCoord;
             vec4 s = texture2D(firstPass, textCoord);
             s *= illuminationDecay * weight;
             crep += s;
             illuminationDecay *= decay;
     }
     crep *= exposure;
     vec4 normalColor = texture2D(secondPass, uv);
     fragColor = normalColor + 0.5*crep;

}
