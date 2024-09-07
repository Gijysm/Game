#ifndef EDITORMODE_H
#define EDITORMODE_H

#include "../../States/State.h"

class State;
class StateData;

class EditorMode
{
private:
    StateData* state_data;
public:
    EditorMode(StateData* state_data);
    virtual ~EditorMode();
    // void updatePmenuButton();
    // void UpdateEditorInput(const float& dt);
    // void renderPmenuButton(RenderTarget& target);
    virtual void updateInput(const float& dt) = 0;
    virtual void updateGui(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void renderButton(RenderTarget& target) = 0;
    virtual void renderGui(RenderTarget* target) = 0;
    virtual void render(RenderTarget* target = NULL) = 0;
};
#endif