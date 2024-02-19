#include "AnimationComponent.h"


void AnimationComponent::addAnimation(const string key, float AnimationTimer, int start_frame_x, int start_frame_y,
	int frame_x, int frame_y, int width, int height)
{
	this->sprite.scale(3, 3);
	this->animation[key] = new Animation(this->sprite, this->textureSheet,
		AnimationTimer, start_frame_x, start_frame_y,
		frame_x, frame_y, width, height);
}

void AnimationComponent::play(const string key, const float& dt)
{
	this->animation[key]->play(dt);
}

AnimationComponent::AnimationComponent(Sprite& sprite, Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animation)
	{
		delete i.second;
	}
}