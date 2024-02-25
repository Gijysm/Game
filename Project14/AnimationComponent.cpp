#include "AnimationComponent.h"

void AnimationComponent::addAnimation(const string key, float animationTimer, int start_frame_x, int start_frame_y,
    int frame_x, int frame_y, int width, int height)
{

    animation[key] = new Animation(sprite, textureSheet[key],
        animationTimer, start_frame_x, start_frame_y,
        frame_x, frame_y, width, height);

}
void AnimationComponent::play(const string key, const float& dt
    , const bool priority)
{
    if (this->AnimationPriority)
    {
        if (this->AnimationPriority == this->animation[key])
        {
            if (this->Lastanimation != animation[key])
            {
                if (this->Lastanimation == NULL)
                    this->Lastanimation = this->animation[key];
                else {
                    this->Lastanimation->reset();
                    this->Lastanimation = this->animation[key];
                }

            }
            animation[key]->sprite.setTexture(textureSheet[key]);

            if (animation[key]->play(dt))
            {
                AnimationPriority = NULL;
            }
        }
    }
    else
    {
        if (priority)
        {
            this->AnimationPriority = this->animation[key];
        }
        if (this->Lastanimation != animation[key])
        {
            if (this->Lastanimation == NULL)
                this->Lastanimation = this->animation[key];
            else {
                this->Lastanimation->reset();
                this->Lastanimation = this->animation[key];
            }

        }
        animation[key]->sprite.setTexture(textureSheet[key]);
        animation[key]->play(dt);
    }

}
void AnimationComponent::play(const string key, const float& dt,
    const float& modifiere, const float& modifiere_max, const bool priority)
{
    if (this->AnimationPriority)
    {
        if (this->AnimationPriority == this->animation[key])
        {
            if (this->Lastanimation != animation[key])
            {
                if (this->Lastanimation == NULL)
                    this->Lastanimation = this->animation[key];
                else {
                    this->Lastanimation->reset();
                    this->Lastanimation = this->animation[key];
                }

            }
            animation[key]->sprite.setTexture(textureSheet[key]);

            if (animation[key]->play(dt, abs(modifiere / modifiere_max)))
            {
                AnimationPriority = NULL;
            }
        }
    }
    else
    {
        if (priority)
        {
            this->AnimationPriority = this->animation[key];
        }
        if (this->Lastanimation != animation[key])
        {
            if (this->Lastanimation == NULL)
                this->Lastanimation = this->animation[key];
            else {
                this->Lastanimation->reset();
                this->Lastanimation = this->animation[key];
            }

        }
    animation[key]->sprite.setTexture(textureSheet[key]);
    animation[key]->play(dt, abs(modifiere/modifiere_max));
    }

}


AnimationComponent::AnimationComponent(Sprite& sprite, map<string, Texture>& textureSheet)
    : sprite(sprite), textureSheet(textureSheet), 
    Lastanimation(NULL), AnimationPriority(NULL)
{
    this->sprite.setScale(3, 3);
}

AnimationComponent::~AnimationComponent()
{
    for (auto& i : animation)
    {
        delete i.second;
    }
}