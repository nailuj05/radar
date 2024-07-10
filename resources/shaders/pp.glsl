#version 330

in vec4 fragColor;
in vec2 fragTexCoord;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

const vec2 size = vec2(800, 600);   // Framebuffer size
const float samples = 50.0;          // Pixels per axis; higher = bigger glow, worse performance
const float quality = 2.5;          // Defines size factor: Lower = smaller glow, better quality

out vec4 fragColor;

const float renderWidth = 800;
const float renderHeight = 600;
float offset = 0.0;

uniform float time;

void main()
{    
    float frequency = renderHeight/3.0;

    vec4 sum = vec4(0);
    vec2 sizeFactor = vec2(1)/size*quality;

    // Texel color fetching from texture sampler
    vec4 source = texture(texture0, fragTexCoord);

    const int range = 2;            // should be = (samples - 1)/2;

    for (int x = -range; x <= range; x++)
    {
        for (int y = -range; y <= range; y++)
        {
            sum += texture(texture0, fragTexCoord + vec2(x, y)*sizeFactor);
        }
    }

    float globalPos = (fragTexCoord.y + offset) * frequency;
    float wavePos = cos((fract(globalPos) - 0.5)*3.14);

    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord);

    finalColor = ((sum/(samples*samples)) + source)*colDiffuse; // - mix(vec4(0.0, 0.3, 0.0, 0.0), texelColor, wavePos);
}
