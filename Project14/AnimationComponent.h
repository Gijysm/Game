#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H
#include "stdafx.h"

class AnimationComponent
{
private:
    friend class Animation;
    Sprite& sprite;
    map<string, Texture> textureSheet;
    Animation* AnimationPriority;
    map<string, Animation*> animation;
    Animation* Lastanimation;

public:
    void addAnimation(const string key, float animationTimer, int start_frame_x, int start_frame_y,
        int frame_x, int frame_y, int width, int height);

    const bool& IsDone(const string key);

    const bool& play(const string key, const float& dt,
        const float& modifiere, const float& modifiere_max, const bool priority = false);
    const bool& play(const string key, const float& dt, const bool priority= false);
    AnimationComponent(Sprite& sprite, map<string, Texture>& textureSheet);
    virtual ~AnimationComponent();
};

class Animation
{
public:
    Texture& texture;
    Sprite& sprite;
    float animationTimer;
    float timer;
    int width;
    int height;
    bool done;
    IntRect startRect;
    IntRect currentRect;
    IntRect endRect;

    Animation(Sprite& sprite, Texture& texture, float animationTimer, int start_frame_x, int start_frame_y,
        int frame_x, int frame_y, int width, int height)
        : sprite(sprite), texture(texture), width(width), height(height),
        animationTimer(animationTimer),timer(0.f), done(false)
    {
        startRect = IntRect(start_frame_x * width, start_frame_y * height, width, height);
        currentRect = startRect;
        endRect = IntRect(frame_x * width, frame_y * height, width, height);
        
        this->sprite.setTexture(this->texture, true);
        this->sprite.setTextureRect(this->startRect);
    }
    
    const bool& IsDone() const
    {
        return this->done;
    }

    const bool& play(const float& dt)
    {
        this->done = false;
        timer += 100.f * dt;
        if (timer >= animationTimer)
        {
            timer = 0.f;

            if (currentRect.left != endRect.left)
            {
                currentRect.left += width;
            }
            else
			{
				currentRect = startRect;
				this->done = true;
			}
            /*
            OLD ALGORITHM
            if (currentRect.top != endRect.top || currentRect.left != endRect.left)
            {
                currentRect.left += width;
                if (currentRect.left + width >= endRect.left + endRect.width)
                {
                    currentRect.left = startRect.left;
                    if (currentRect.top != endRect.top)
                    {
                        currentRect.top += height;
                        if (currentRect.top + height >= endRect.top + endRect.height)
                        {
                            currentRect.top = startRect.top;
                            this->done = true;
                        }
                    }
                }
            }*/

            sprite.setTextureRect(currentRect);
            
        }
        return this->done;
    }
    const bool& play(const float& dt,
        float modifiere_precent)
    {
        if (modifiere_precent < 0.5)
            modifiere_precent = 0.5;
        this->done = false;
        timer += modifiere_precent * 100.f * dt;
        if (timer >= animationTimer)
        {
            timer = 0.f;
            if (currentRect.left != endRect.left)
            {
                currentRect.left += width;
            }
            else
            {
                currentRect = startRect;
                this->done = true;
            }
            /*
            OLD ALGORITHM
            if (currentRect.top != endRect.top || currentRect.left != endRect.left)
            {
                currentRect.left += width;
                if (currentRect.left + width >= endRect.left + endRect.width)
                {
                    currentRect.left = startRect.left;
                    if (currentRect.top != endRect.top)
                    {
                        currentRect.top += height;
                        if (currentRect.top + height >= endRect.top + endRect.height)
                        {
                            currentRect.top = startRect.top;
                            this->done = true;
                        }
                    }
                }
            }*/
            sprite.setTextureRect(currentRect);
            
        }
        return this->done;
    }
    void reset()
    {
        this->timer = 0;
        this->currentRect = startRect;
    }
};

#endif
