#ifndef DECKCOMPONENT_H
#define DECKCOMPONENT_H

#include "BaseComponent.h"


class DeckComponent : public BaseComponent
{
    public:
        DeckComponent();
        virtual ~DeckComponent();

        void NextCard();
        void PreviousCard();

        void PeekPreviousCard();
        void PeekNextCard();
        void PeekActiveCard();

        void UseActiveCard();
        void ResetDeck();


    private:
        int _index;
        int _deckSize;
};

#endif // DECKCOMPONENT_H
