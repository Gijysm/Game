#include "AnimationComponent.h"

void AnimationComponent::addAnimation(const string key, float animationTimer, int start_frame_x, int start_frame_y,
    int frame_x, int frame_y, int width, int height)
{

    animation[key] = new Animation(sprite, textureSheet[key],
        animationTimer, start_frame_x, start_frame_y,
        frame_x, frame_y, width, height);

}

void AnimationComponent::play(const string key, const float& dt)
{
    if (this->Lastanimation != animation[key])
    {
        if(this->Lastanimation == NULL)
            this->Lastanimation = this->animation[key];
        else {
        this->Lastanimation->reset();
        this->Lastanimation = this->animation[key];
        }

    }
    animation[key]->sprite.setTexture(textureSheet[key]);
    animation[key]->play(dt);
}


AnimationComponent::AnimationComponent(Sprite& sprite, map<string, Texture>& textureSheet)
    : sprite(sprite), textureSheet(textureSheet), Lastanimation(NULL)
{
    this->sprite.scale(3, 3);
}

AnimationComponent::~AnimationComponent()
{
    for (auto& i : animation)
    {
        delete i.second;
    }
}