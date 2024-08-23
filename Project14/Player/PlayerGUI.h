#ifndef PLAYERGUI
#define PLAYERGUI
#include "..//Player//Player.h"
#include "..//GUI//Gui.h"
#include "..//stdafx.h"
class Player;
class PlayerGUI
{
private:
	int colorChangeCounterProgressBar;
	bool Textchanged = false;
	bool Layerchanged = false;
	string ManaBarString;
	string ExpBarString;
	Text LevelText;
	Text ManaText;
	Text ExpText;
	Player* player;
	gui::ProgressBar* hpBar;
	gui::ProgressBar* ManaBar;
	gui::ProgressBar* ExpBar;
	gui::ProgressBar* StaminaBar;
	RectangleShape playerExpBar;
	RectangleShape playerManaBar;
	RectangleShape playerStaminBar;
	Font font;

	void InitFont();
	void InitPlayerBars();

	public:
		PlayerGUI(Player* player);
		virtual ~PlayerGUI();
		void UpdateHpBar();
		void UpdateManaBar();
		void UpdateExpBar();

		void UpdateDynamicalElliments();
		void update(const float& dt);
		void UpdateColor(int Exp, int zmina, RectangleShape& shape);
		void UpdateColor(int Exp, int zmina, Text& shape);
		void Render_Dynamical(RenderTarget& target);
		void Render(RenderTarget& target);
		void RenderHpBar(RenderTarget& target);
		void RenderManaBar(RenderTarget& target);
		void RenderExpBar(RenderTarget& target);
};
#endif // !PLAYERGUI



  