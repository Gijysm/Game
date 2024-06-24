#ifndef PLAYERGUI
#define PLAYERGUI
#include "Player.h"
class Player;
class PlayerGUI
{
private:
	int colorChangeCounter;

	string hpBarString;
	string ManaBarString;
	string ExpBarString;
	Text HpText;
	Text ManaText;
	Text ExpText;
	Player* player;
	RectangleShape playerHpBar;
	RectangleShape playerExpBar;
	RectangleShape playerBarBack;
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
		void update(const float& dt);
		void UpdateColor(int Exp, int zmina, RectangleShape& shape);
		void Render(RenderTarget& target);
		void RenderHpBar(RenderTarget& target);
		void RenderManaBar(RenderTarget& target);
		void RenderExpBar(RenderTarget& target);
};
#endif // !PLAYERGUI



  