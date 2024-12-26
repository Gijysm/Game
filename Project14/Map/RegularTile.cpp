#include "RegularTile.h"

RegularTile::RegularTile()
{
}

RegularTile::RegularTile(short type, int x, int y, float gridSizeF, const Texture& tex, const IntRect& tex_rect,
                         const bool collision):Tile(type, x, y, gridSizeF, tex, tex_rect, collision)
{
}

RegularTile::~RegularTile()
{
}

const int& RegularTile::GetType() const
{
    return this->type;
}
const string RegularTile::getAsString() const
{
    stringstream ss;

    ss << this->type << " " << this->shape.getTextureRect().left << " " << 
        this->shape.getTextureRect().top << " " << this->collision;
    return ss.str();
}


void RegularTile::update()
{
}
void RegularTile::render(RenderTarget& target, Shader* shader, Vector2f PlayerPos)
{
    if(shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", PlayerPos);
        target.draw(this->shape, shader);
    }
    else
        target.draw(this->shape);
}