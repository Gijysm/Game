#ifndef GUI_H
#define GUI_H
#include "..//stdafx.h"

enum Button_States{BTN_IDLE = 0, 
BTN_HOWER, BTN_ACTIVE};
namespace gui
{
	const float p2pX(const float perc, VideoMode vm);
	const float p2pY(const float perc, VideoMode vm);
	const unsigned CharacterSize(VideoMode vm);
	class Button
	{
	private:
		short unsigned Button_State;

		bool Hower;
		bool Active;

		RectangleShape Shape;
		Font* font;
		sf::Text text; // Instead of Text Text;

		short unsigned id;

		Color Idle_Color;
		Color Hower_Color;
		Color Active_Color;

		Color OutLine_Idle_Color;
		Color OutLine_Hower_Color;
		Color OutLine_Active_Color;

		Color Text_idle_Color;
		Color Text_hower_Color;
		Color Text_active_Color;
	public:
		Button(float x, float y, float Width, float height,
			Font* font, string text, int Character_size,
			Color Text_idle_Color, Color Text_hower_Color, Color Text_active_Color,
			Color idle_Color, Color hower_Color, Color active_Color,
			Color OutLine_idle_Color= Color::Transparent, Color OutLine_hower_Color = Color::Transparent, Color OutLine_active_Color = Color::Transparent,
			short unsigned id = 0);
		virtual ~Button();

		const bool isPressed() const;
		const string getText() const;
		const short unsigned& getId() const;


		void setText(const string text);
		void setId(const short unsigned id);

		void update(const  Vector2i& MousePos);
		void render(RenderTarget& target);
	};
	class DropDownList
	{
	private:
		Font& font;
		gui::Button* activeEllement;
		vector<gui::Button*> list;

		bool showlist;
		float Keytime;
		float KeytimeMax;
	public:
		DropDownList(float x, float y, float width, float height, Font& font,string list[],
			unsigned NOEllements, unsigned default_index = 0);
		~DropDownList();

		void UpdateKeyTime(const float& dt);
		const bool GetKeyTime();

		const unsigned short& getActiveEllementId() const;
		void update(const Vector2i& MousePos, const float& dt);
		void render(RenderTarget& target);
	};
	class TextureSelector
	{
	private:
		RectangleShape bounds;
		Sprite sheet;
		RectangleShape selector;
		Vector2u mousePosGrid;
		IntRect TextureRect;
		float offset;
		float gridSize;
		bool active;
		bool hiden;
		float Keytime;
		float KeytimeMax;
	public:
		TextureSelector(const float& x, const float& y, 
			const float& width, const float& height, 
			const float& gridSize, 
			const Texture* texture_sheet, Font& font, 
			const string& str, VideoMode vm);
		~TextureSelector();

		const bool &GetActive() const;
		const IntRect& getTextureRect() const;

		const bool GetKeyTime();
		void UpdateKeyTime(const float& dt);
		void update(const Vector2i& MousePosWindow, const float& dt, bool& Hiden);
		void render(RenderTarget& target, bool& Hiden);
	};
	enum F_ont
	{
		Width,
		Height
	};
	class ProgressBar
	{
	private:
		float x;
		float y;
		float screenWidth ;
		float screenHeight;
		
		string ProgressBarString;
		Text text;
		float maxWidth,maxHeight;
		int maxValue,
		current_value,
		size_Text;
		RectangleShape lineer;
		RectangleShape Back;
		const void SetSizeLineer(const float& x, const float& y);
		const void SetSizeText(const float& size);
		const void SetSizeBack(const float& x, const float& y);
	public:
		ProgressBar(float dx = 0, float dy = 0, float width = 0,
			float height = 0, int Character_size = 0, int XpositionText =0,
			int YpositionText = 0,  int MaxHp  = 0,
			VideoMode vm = VideoMode(), Font* font = NULL,
		Color colorText = Color(), Color colorLineer = Color());
        void LoadBack(float dx, float dy, float width,
                      	float height);
		~ProgressBar();

		const Vector2f GetPositionLineer()const ;
		const Vector2f GetSizeLineer()const ;
		const unsigned int GetSizeText() ;
		const Vector2f GetPositionBack()const ;
		const Vector2f GetPositionT()const ;
		const void SetPositionLineer(const float& x, const float& y);
		const void SetPositionText(const float& x, const float& y);
		const void SetPositionBack(const float& x, const float& y);
		
		void Update(const int& current_value, const int& Max_value = 0, const F_ont& font = F_ont::Width);
		void RenderLineer(RenderTarget& target);
		void RenderText(RenderTarget& target);
		void Render(RenderTarget& target);
		void RenderBack(RenderTarget& target);
	};
}

#endif // !BUTTON_H