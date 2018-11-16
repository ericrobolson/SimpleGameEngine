#ifndef DECKCOMPONENT_H
#define DECKCOMPONENT_H

#include "BaseComponent.h"
#include <vector>
#include <memory>

#include "EntityComponentManager.h"

/*
Example Cards:
    Name: Melee
    Cost: 1
    CardType: Attack
    PowerType: OneShot
    Effect: Create an Attack with 5 damage, discard after use

    Name: Shield
    CardType: Shield
    Cost: 1
    PowerType: OneShot
    Effect: Create a shield with 10hp, discard after use

    Name: Next Turn
    Cost: 0
    CardType: Spell
    PowerType: OneShot
    Effect: Discard hand, start next turn, exile this card, add a copy of this card to your hand

    Name: Energy Reserves
    Cost: 2
    CardType: Spell
    PowerType: Modifier
    Effect: At the start of your turn, gain 1 energy

    Name: Fire
    Cost: 1
    CardType: Spell
    PowerType: Trigger
    Effect: Your next attack gains fire, discard this card

    Name: Ice
    Cost: 1
    CardType: Spell
    PowerType: Trigger
    Effect: Your next attack gains Ice, discard this card

    Name: Golden Coin
    Cost: 2
    CardType: Spell
    PowerType: OneShot
    Effect: Gain 3 energy, discard this card

    Name: Critical Strike
    Cost: 1
    CardType: Spell
    PowerType: Trigger
    Effect: Your next attack deals 2x damage, exile that card, discard this card

    Name: Critical Shield
    Cost: 1
    CardType: Spell
    PowerType: Trigger
    Effect: Your next Shield gains 2x shield, exile that card, discard this card

    Name: Health Pot
    Cost: 1
    CardType: Spell
    PowerType: OneShot
    Effect: You gain 10hp, exile this card

    Name: Consuming Hunger
    Cost: 0
    CardType: Spell
    PowerType: OneShot
    Effect: Exile top card of deck, gain energy equal to it's cost, discard this card

    Name: Shiv
    Cost: 0
    CardType: Attack
    PowerType: OneShot
    Effect: Create an attack with 4 damage, exile this card

    Name: Blade Master
    Cost: 1
    CardType: Spell
    PowerType: Trigger
    Effect: At the start of your turn, add 1 shiv to your hand

    Name: Strongman
    Cost: 3
    CardType: Spell
    PowerType: Trigger
    Effect: At the start of your turn, gain +1 Strength

    Name: ???
    Cost: 1
    CardType: Attack
    PowerType: OneShot
    Effect: discard this card, Draw 1 card, create an attack with 9 dmg,
*/



class Card{
    public:
        int EnergyCost;

        enum CardTypes {Attack, Shield, Spell};
        CardTypes CardType;

        enum PowerTypes {OneShot, Modifier, Trigger};
        PowerTypes PowerType;
};

class DeckComponent : public BaseComponent
{
    public:
        DeckComponent();
        virtual ~DeckComponent();

        //int SelectNextCard();
        //int SelectPreviousCard();

        //void UseActiveCard();

        void ShuffleDeck();

        //void BeginTurn();


        //void ProcessTriggers(ECS::EntityComponentManager entityComponentManager, int entityIdForCard);


        //void UpdateState();

        void DrawCard(int numCardsToDraw);

        int GetEnergy();
        int AddEnergy(int energyToAdd);
        int SetEnergy(int energyToSet);

        void AddCardToDeck(Card card);
        void AddCardToDiscard(Card card);
        void AddCardToHand(Card card);
        void AddCardToExhaustedCards(Card card);

        std::vector<Card> GetDeck();
        std::vector<Card> GetHand();
        std::vector<Card> GetExhaustedCards();
        std::vector<Card> GetDiscardedCards();
    private:
        const int DefaultEnergy = 3;

        int _energy;
        int _activeCardIndex;

        std::vector<Card> _hand;
        std::vector<Card> _deck;
        std::vector<Card> _exhaustedCards;
        std::vector<Card> _discardedCards;
};

#endif // DECKCOMPONENT_H
