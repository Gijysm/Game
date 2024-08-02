#version 120

// Змінні, що передаються з вершинного шейдера
varying vec4 vert_pos;

// Уніформи, що задаються програмою
uniform sampler2D texture;
uniform bool hasTexture;
uniform vec2 lightPos;

void main()
{
    // Ambient освітлення
    vec4 ambient = vec4(0.02, 0.02, 0.02, 1.0);

    // Перетворення позиції світла у координати виду
    vec2 light = (gl_ModelViewProjectionMatrix * vec4(lightPos, 0.0, 1.0)).xy;

    // Вектор від світла до фрагмента
    vec2 lightToFrag = light - vert_pos.xy;
    lightToFrag.y = lightToFrag.y / 1.7;

    // Довжина вектора (відстань)
    float vecLength = clamp(length(lightToFrag) * 5.0, 0.5, 4.0);

    // Зчитуємо піксель з текстури
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // Обчислюємо кінцевий колір з урахуванням освітлення
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
