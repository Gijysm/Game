#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <map>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class AnimationComponent
{
private:
    Sprite& sprite;
    map<string, Texture> textureSheet;

    class Animation
    {
    public:
        Texture& texture;
        Sprite& sprite;
        float animationTimer;
        float timer;
        int width;
        int height;
        IntRect startRect;
        IntRect currentRect;
        IntRect endRect;

        Animation(Sprite& sprite, Texture& texture, float animationTimer, int start_frame_x, int start_frame_y,
            int frame_x, int frame_y, int width, int height)
            : sprite(sprite), texture(texture), width(width), height(height),
            animationTimer(animationTimer)
        {
            timer = 0.f;
            startRect = IntRect(start_frame_x * width, start_frame_y * height, width, height);
            currentRect = startRect;
            endRect = IntRect(frame_x * width, frame_y * height, width, height);
            sprite.setTexture(texture, true);
            sprite.setTextureRect(startRect);
        }

        void play(const float& dt)
        {
            timer += 10.f * dt;
            if (timer >= animationTimer)
            {
                timer = 0.f;

                if (currentRect.top != endRect.top || currentRect.left != endRect.left)
                {
                    currentRect.left += width;
                    if (currentRect.left + width >= endRect.left + endRect.width)
                    {
                        currentRect.left = startRect.left;
                        currentRect.top += height;
                        if (currentRect.top + height >= endRect.top + endRect.height)
                        {
                            currentRect.top = startRect.top;
                        }
                    }
                }
                else
                {
                    currentRect = startRect;
                }

                sprite.setTextureRect(currentRect);
            }
        }
    };

    map<string, Animation*> animation;

public:
    void addAnimation(const string key, float animationTimer, int start_frame_x, int start_frame_y,
        int frame_x, int frame_y, int width, int height);

    void play(const string key, const float& dt, const bool ver);

    AnimationComponent(Sprite& sprite, map<string, Texture>& textureSheet);
    virtual ~AnimationComponent();
};

#endif // ANIMATIONCOMPONENT_H
