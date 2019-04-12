#ifndef ACTORCOMPONENT_H
#define ACTORCOMPONENT_H

#include "BaseComponent.h"


class ActorComponent : public BaseComponent
{
    public:
        ActorComponent();
        virtual ~ActorComponent();

        enum ButtonState{ Empty, Pressed, Released};

        class DirectionalInputs{
            public:
            ButtonState UpButton;
            ButtonState DownButton;
            ButtonState LeftButton;
            ButtonState RightButton;
        };

        DirectionalInputs LeftStick;
        DirectionalInputs RightStick;

        class PrimaryInputs{
            public:
            ButtonState AButton;
            ButtonState XButton;
            ButtonState LTrigger;
            ButtonState RTrigger;
        };

        PrimaryInputs PrimaryButtons;


        class SecondaryInputs{
            public:
            DirectionalInputs DPad;

            ButtonState BButton;
            ButtonState YButton;
            ButtonState LBumper;
            ButtonState RBumper;
        };

        SecondaryInputs SecondaryButtons;

        class SystemInputs{
            public:
            ButtonState Start;
        };

        SystemInputs SystemButtons;






    protected:

    private:
};

#endif // ACTORCOMPONENT_H
