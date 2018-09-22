#include "InputState.h"

InputState::InputState()
{
    CursorX = 0;
    CursorY = 0;

    ButtonUpIsPressed = false;
    ButtonDownIsPressed = false;
    ButtonRightIsPressed = false;
    ButtonLeftIsPressed = false;

    Button1IsPressed = false;
    Button2IsPressed = false;
    Button3IsPressed = false;
    Button4IsPressed = false;

    Button5IsPressed = false;
    Button6IsPressed = false;
    Button7IsPressed = false;
    Button8IsPressed = false;

    Button9IsPressed = false;

    Exit = false;
}

InputState::~InputState()
{
    //dtor
}
