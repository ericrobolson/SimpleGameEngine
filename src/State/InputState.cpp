#include "InputState.h"

InputState::InputState()
{
   Reset();
}

void InputState::Reset(){
    CursorX = 0;
    CursorY = 0;

    ButtonUpIsPressed = false;
    ButtonDownIsPressed = false;
    ButtonRightIsPressed = false;
    ButtonLeftIsPressed = false;

    Button1IsPressed = false; // LMB/Right Trigger on xbox controller
    Button2IsPressed = false; // RMB/Left Trigger on xbox controller
    Button3IsPressed = false; // Space/A on xbox controller

    Button4IsPressed = false; // R/X on xbox controller
    Button5IsPressed = false; // Q/Y on xbox controller
    Button6IsPressed = false;
    Button7IsPressed = false;
    Button8IsPressed = false;

    Button9IsPressed = false;

    Exit = false;
}

bool InputState::AnyKeyPressed(){
    return (
        Button1IsPressed
        || Button2IsPressed
        || Button3IsPressed
        || Button4IsPressed
        || Button5IsPressed
        || Button6IsPressed
        || Button7IsPressed
        || Button8IsPressed
        || Button9IsPressed

        || ButtonUpIsPressed
        || ButtonDownIsPressed
        || ButtonLeftIsPressed
        || ButtonRightIsPressed
    );
}

InputState::~InputState()
{
    //dtor
}
