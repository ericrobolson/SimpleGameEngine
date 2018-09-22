#ifndef INPUTSTATE_H
#define INPUTSTATE_H

class InputState
{
    public:
        static InputState& Instance(){
            static InputState *instance = new InputState();
            return *instance;
        };

        int CursorX;
        int CursorY;

        bool ButtonUpIsPressed;
        bool ButtonDownIsPressed;
        bool ButtonRightIsPressed;
        bool ButtonLeftIsPressed;

        bool Button1IsPressed;
        bool Button2IsPressed;
        bool Button3IsPressed;
        bool Button4IsPressed;

        bool Button5IsPressed;
        bool Button6IsPressed;
        bool Button7IsPressed;
        bool Button8IsPressed;

        bool Button9IsPressed;

        bool Exit;
    private:
        InputState();
        virtual ~InputState();
};

#endif // INPUTSTATE_H
