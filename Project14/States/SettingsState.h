#ifndef SETTINGS_H
#define SETTINGS_H

#include "..//States/State.h"
#include "..//GUI/Gui.h"

class SettingsState : public State
{
private:
	RectangleShape BackGround;
	Texture BackGroundTexture;
	Font font;
	Text optionsText;
	map<string, gui::Button*> Buttons;
	map<string, gui::DropDownList*> dropdownList;
	vector<VideoMode> modes;

	void InitVariables();
	void InitBackGround();
	void InitFont();
	void InitGui();
	void InitKeyBinds();
	void initText();
public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void renderGui(RenderTarget& target);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

#endif 