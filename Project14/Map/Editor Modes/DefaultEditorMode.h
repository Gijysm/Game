#ifndef DEFAULTMODE_H
#define DEFAULTMODE_H

#include "EditorMode.h"

class EditorMode;
class State;
class StateData;

class DefaultEditorMode : public EditorMode
{
public:
    DefaultEditorMode(StateData* state_data);
    virtual ~DefaultEditorMode();
};
#endif