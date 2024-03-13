#ifndef SETTINGS_H
#define SETTINGS_H

#include "State.h"
#include "Gui.h"

class SettingsState : public State
{
private:
	RectangleShape BackGround;
	Texture BackGroundTexture;
	Font font;
	Text optionsText;
	GraphicsSettings& GfxSettings;
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
	SettingsState(RenderWindow* window, GraphicsSettings& GfxSettings, map<string, int>* supportedKey, stack<State*>* states);
	virtual ~SettingsState();

	void updateInput(const float& dt);
	void updateGui(const float& dt);
	void renderGui(RenderTarget& target);
	void update(const float& dt);
	void render(RenderTarget* target = NULL);
};

#endif 