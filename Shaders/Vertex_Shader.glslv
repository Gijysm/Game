#version 120

// Передача змінних у фрагментний шейдер
varying vec4 vert_pos;

void main()
{
    // Зберігаємо позицію вершин для фрагментного шейдера
    vert_pos = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // Обчислюємо кінцеву позицію вершин
    gl_FrontColor = gl_Color;
}
