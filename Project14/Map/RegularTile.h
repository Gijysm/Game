#ifndef  REGULARTILE_H
#define REGULARTILE_H
#include "Tile.h"
class RegularTile : public Tile
{
private:
protected:

public:
    RegularTile();
    RegularTile(short type , int x, int y, float gridSizeF, const Texture& tex,
        const IntRect& tex_rect,
        bool collision = false);
    ~RegularTile();

    const int& GetType() const;
    const string getAsString() const;
   

    void update();
    void render(RenderTarget& target, Shader* shader = NULL, Vector2f PlayerPos = Vector2f());

};
#endif