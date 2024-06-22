#ifndef PLAYERGUI
#define PLAYERGUI
#include "Player.h"
class Player;
class PlayerGUI
{
private:
	Player* player;
	RectangleShape playerHpBar;
	RectangleShape playerHpBarBack;
	RectangleShape playerManaBar;
	RectangleShape playerStaminBar;
	Font font;

	void InitFont();
	void InitPlayerHpBar();

	public:
		PlayerGUI(Player* player);
		virtual ~PlayerGUI();
		void UpdateHpBar();
		void update(const float& dt);
		void Render(RenderTarget& target);
		void RenderHpBar(RenderTarget& target);
};
#endif // !PLAYERGUI



  