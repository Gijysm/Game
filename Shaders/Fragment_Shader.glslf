#version 120

// Змінні, що передаються з вершинного шейдера
varying vec4 vert_pos;

// Уніформи, що задаються програмою
uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 lightPos;

void main()
{
    vec4 ambient = vec4(0.085, 0.02, 0.3, 1.0);

    vec2 light = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0.0, 1.0)).xy;

    vec2 lightToFrag = light - vert_pos.xy;
    lightToFrag.y = lightToFrag.y / 1.7;


    float vecLength = clamp(length(lightToFrag) * 3.85, 0.4, 0.985);

    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    vec4 finalColor;
    if (hasTexture == true)
    {
        gl_FragColor = gl_Color * pixel * (clamp(ambient + vec4(1 - vecLength, 1 - vecLength, 1 - vecLength, 1), 0, 1));
    }
    else
    {
        gl_FragColor = gl_Color;
    }

}
