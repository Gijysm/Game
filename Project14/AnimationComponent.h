#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include<map>
#include<string>
#include<iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace sf;
using namespace std;
class AnimationComponent
{
private:
	Sprite& sprite;
	Texture& textureSheet;
	class Animation {
	public:
		Texture& Texturesheet;
		Sprite& SpriTe;
		float AnimationTimer;
		float Timer;
		int width;
		int height;
		IntRect Startrect;
		IntRect Currentrect;
		IntRect Endrect;

		Animation(Sprite& SpriTe, Texture& Texturesheet, float AnimationTimer, int start_frame_x, int start_frame_y,
			int frame_x, int frame_y, int width, int height)
			:SpriTe(SpriTe), Texturesheet(Texturesheet), width(width), height(height),
			AnimationTimer(AnimationTimer)
		{
			this->Timer = 0.f;
			this->Startrect = IntRect(start_frame_x * width, start_frame_y * height, width, height);
			this->Currentrect = this->Startrect;
			this->Endrect = IntRect(frame_x * width, frame_y * height, width, height);
			this->SpriTe.setTexture(this->Texturesheet, true);
			this->SpriTe.setTextureRect(this->Startrect);
		}
		void play(const float& dt)
		{
			this->Timer += 10.f * dt;
			if (this->Timer >= this->AnimationTimer)
			{
				this->Timer = 0.f;

				// ???????????, ?? ????????? ????? ????????
				if (this->Currentrect.top != this->Endrect.top || this->Currentrect.left != this->Endrect.left)
				{
					// ???????????? ????????
					this->Currentrect.left += this->width;
					if (this->Currentrect.left + this->width >= this->Endrect.left + this->Endrect.width)
					{
						this->Currentrect.left = this->Startrect.left;
						this->Currentrect.top += this->height;
						if (this->Currentrect.top + this->height >= this->Endrect.top + this->Endrect.height)
						{
							this->Currentrect.top = this->Startrect.top;
						}
					}
				}
				else
				{
					// ?????? ? ???????
					this->Currentrect = this->Startrect;
				}

				this->SpriTe.setTextureRect(this->Currentrect);
			}
		}

	};
	map<string, Animation*> animation;
public:
	void addAnimation(const string key, float AnimationTimer, int start_frame_x, int start_frame_y,
		int frame_x, int frame_y, int width, int height);

	void play(const string key, const float& dt);
	AnimationComponent(Sprite& sprite, Texture& textureSheet);
	virtual ~AnimationComponent();
};
#endif

