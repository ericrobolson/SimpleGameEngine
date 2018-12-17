#ifndef PACKET_H
#define PACKET_H
#include <vector>

class Packet
{
    public:
        class PlayerInput{
            public:
                PlayerInput(){
                    Button1 = ButtonAction::NoChange;
                    Button2 = ButtonAction::NoChange;
                    Button3 = ButtonAction::NoChange;
                    Button4 = ButtonAction::NoChange;
                    Button5 = ButtonAction::NoChange;
                    Button6 = ButtonAction::NoChange;
                    Button7 = ButtonAction::NoChange;
                    Button8 = ButtonAction::NoChange;
                    Button9 = ButtonAction::NoChange;
                    Button10 = ButtonAction::NoChange;
                    Button11 = ButtonAction::NoChange;
                    Button12 = ButtonAction::NoChange;
                    Button13 = ButtonAction::NoChange;
                    Button14 = ButtonAction::NoChange;

                    CursorDeltaX = 0;
                    CursorDeltaY = 0;
                }

            enum class ButtonAction{NoChange, Pressed, Released};

            int playerId;

            int CursorDeltaX;
            int CursorDeltaY;

            ButtonAction Button1; // Up
            ButtonAction Button2; // Down
            ButtonAction Button3; // Left
            ButtonAction Button4; // Right
            ButtonAction Button5; // Lmb
            ButtonAction Button6; // Rmb
            ButtonAction Button7; // Space
            ButtonAction Button8; // Shift
            ButtonAction Button9; // Ctl
            ButtonAction Button10; // R
            ButtonAction Button11; // Q
            ButtonAction Button12; // E
            ButtonAction Button13; // G
            ButtonAction Button14; // F
        };

        Packet();
        virtual ~Packet();

        int GameStep;

        std::vector<PlayerInput> PlayerInputs;

    protected:

    private:
};

#endif // PACKET_H
