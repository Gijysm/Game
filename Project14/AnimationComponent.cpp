#include "AnimationComponent.h"

void AnimationComponent::addAnimation(const string key, float animationTimer, int start_frame_x, int start_frame_y,
    int frame_x, int frame_y, int width, int height)
{

    animation[key] = new Animation(sprite, textureSheet[key],
        animationTimer, start_frame_x, start_frame_y,
        frame_x, frame_y, width, height);

}

void AnimationComponent::play(const string key, const float& dt, const bool ver)
{
    if (animation.find(key) != animation.end()) // ?????????, ?? ? ???????? ? ????? ??????
    {
        if (ver)
        {
            animation[key]->sprite.setTexture(textureSheet[key]);
            animation[key]->play(dt);
        }
        else
        {
            // ??????? ???????, ???? ??????????? (ver) ?? ????????
            animation[key]->play(dt);
        }
    }
    else
    {
        // ??????? ???????, ???? ???????? ? ????? ?????? ?? ????????
        throw "Animation not found";
    }
}


AnimationComponent::AnimationComponent(Sprite& sprite, map<string, Texture>& textureSheet)
    : sprite(sprite), textureSheet(textureSheet)
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