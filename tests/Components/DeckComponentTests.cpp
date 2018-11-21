#include "catch.hpp"
#include "EntityComponentManager.h"
#include <vector>
#include <memory>
#include "DeckComponent.h"
#include "EventQueue.h"

using namespace SGE;

SCENARIO("DeckComponent::Constructor"){
    EventQueue eq;
    DeckComponent deckComponent(eq);

    REQUIRE(deckComponent.GetDeck().empty() == true);
    REQUIRE(deckComponent.GetExhaustedCards().empty() == true);
    REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
    REQUIRE(deckComponent.GetHand().empty() == true);
}

SCENARIO("DeckComponent::AddCardToDeck"){
    EventQueue eq;

    DeckComponent deckComponent(eq);
    REQUIRE(deckComponent.GetDeck().empty() == true);
    REQUIRE(deckComponent.GetExhaustedCards().empty() == true);
    REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
    REQUIRE(deckComponent.GetHand().empty() == true);

    SECTION("AddCardToDeck Increases DeckSize"){
        Card cardToAdd;
        deckComponent.AddCardToDeck(cardToAdd);

        REQUIRE(deckComponent.GetDeck().size() == 1);
        REQUIRE(deckComponent.GetExhaustedCards().empty() == true);
        REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
        REQUIRE(deckComponent.GetHand().empty() == true);
    }
}

SCENARIO("DeckComponent::AddCardToHand"){
    EventQueue eq;

    DeckComponent deckComponent(eq);
    REQUIRE(deckComponent.GetDeck().empty() == true);
    REQUIRE(deckComponent.GetExhaustedCards().empty() == true);
    REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
    REQUIRE(deckComponent.GetHand().empty() == true);

    SECTION("AddCardToHand Increases HandSize"){
        Card cardToAdd;
        deckComponent.AddCardToHand(cardToAdd);

        REQUIRE(deckComponent.GetHand().size() == 1);
        REQUIRE(deckComponent.GetDeck().empty() == true);
        REQUIRE(deckComponent.GetExhaustedCards().empty() == true);
        REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
    }
}

SCENARIO("DeckComponent::AddCardToDiscard"){
    EventQueue eq;
    DeckComponent deckComponent(eq);

    REQUIRE(deckComponent.GetDeck().empty() == true);
    REQUIRE(deckComponent.GetExhaustedCards().empty() == true);
    REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
    REQUIRE(deckComponent.GetHand().empty() == true);

    SECTION("AddCardToDiscard Increases Discard"){
        Card cardToAdd;
        deckComponent.AddCardToDiscard(cardToAdd);

        REQUIRE(deckComponent.GetDiscardedCards().size() == 1);
        REQUIRE(deckComponent.GetDeck().empty() == true);
        REQUIRE(deckComponent.GetExhaustedCards().empty() == true);
        REQUIRE(deckComponent.GetHand().empty() == true);
    }
}

SCENARIO("DeckComponent::AddCardToExhaustedCards"){
    EventQueue eq;
    DeckComponent deckComponent(eq);

    REQUIRE(deckComponent.GetDeck().empty() == true);
    REQUIRE(deckComponent.GetExhaustedCards().empty() == true);
    REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
    REQUIRE(deckComponent.GetHand().empty() == true);

    SECTION("AddCardToExhaustedCards Increases ExhaustedCards"){
        Card cardToAdd;
        deckComponent.AddCardToExhaustedCards(cardToAdd);

        REQUIRE(deckComponent.GetExhaustedCards().size() == 1);
        REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
        REQUIRE(deckComponent.GetDeck().empty() == true);
        REQUIRE(deckComponent.GetHand().empty() == true);
    }
}

SCENARIO("DeckComponent::Energy"){
    EventQueue eq;
    DeckComponent deckComponent(eq);

    REQUIRE(deckComponent.GetEnergy() == 0);
    SECTION("AddEnergy increases GetEnergy"){
        int energyToAdd = 1;
        REQUIRE(deckComponent.AddEnergy(energyToAdd) == energyToAdd);
        REQUIRE(deckComponent.GetEnergy() == energyToAdd);
    }

    SECTION("SetEnergy sets Energy"){
        int energyToSet = 20;
        REQUIRE(deckComponent.SetEnergy(energyToSet) == energyToSet);
        REQUIRE(deckComponent.GetEnergy() == energyToSet);
    }

}


SCENARIO("DeckComponent::DrawCards"){
    EventQueue eq;
    DeckComponent deckComponent(eq);
    Card card;
    REQUIRE(deckComponent.GetHand().empty() == true);

    SECTION("One Card in deck, draw 1 makes deck empty"){
        deckComponent.AddCardToDeck(card);
        REQUIRE(deckComponent.GetHand().empty() == true);
        REQUIRE(deckComponent.GetDeck().size() == 1);

        deckComponent.DrawCard(1);

        REQUIRE(deckComponent.GetHand().size() == 1);
        REQUIRE(deckComponent.GetDeck().empty() == true);
    }

    SECTION("One Card in discard, draw 1 moves discard to deck, then deck empty"){
        deckComponent.AddCardToDiscard(card);
        REQUIRE(deckComponent.GetHand().empty() == true);
        REQUIRE(deckComponent.GetDeck().empty() == true);
        REQUIRE(deckComponent.GetDiscardedCards().size() == 1);

        deckComponent.DrawCard(1);

        REQUIRE(deckComponent.GetHand().size() == 1);
        REQUIRE(deckComponent.GetDeck().empty() == true);
        REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
    }

    SECTION("One Card in discard, one card in deck, draw 2 moves discard to deck, then deck empty"){
        deckComponent.AddCardToDiscard(card);
        deckComponent.AddCardToDeck(card);
        REQUIRE(deckComponent.GetHand().empty() == true);
        REQUIRE(deckComponent.GetDeck().size() == 1);
        REQUIRE(deckComponent.GetDiscardedCards().size() == 1);

        deckComponent.DrawCard(2);

        REQUIRE(deckComponent.GetHand().size() == 2);
        REQUIRE(deckComponent.GetDeck().empty() == true);
        REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
    }

    SECTION("5 cards in deck, 10 cards in discard, draw Max + 1 only draws max cards"){
        deckComponent.AddCardToDeck(card);
        deckComponent.AddCardToDeck(card);
        deckComponent.AddCardToDeck(card);
        deckComponent.AddCardToDeck(card);
        deckComponent.AddCardToDeck(card);

        deckComponent.AddCardToDiscard(card);
        deckComponent.AddCardToDiscard(card);
        deckComponent.AddCardToDiscard(card);
        deckComponent.AddCardToDiscard(card);
        deckComponent.AddCardToDiscard(card);
        deckComponent.AddCardToDiscard(card);
        deckComponent.AddCardToDiscard(card);
        deckComponent.AddCardToDiscard(card);
        deckComponent.AddCardToDiscard(card);
        deckComponent.AddCardToDiscard(card);

        REQUIRE(deckComponent.GetHand().empty() == true);
        REQUIRE(deckComponent.GetDeck().size() == 5);
        REQUIRE(deckComponent.GetDiscardedCards().size() == 10);

        deckComponent.DrawCard(deckComponent.MaxHandSize + 1);

        REQUIRE(deckComponent.GetHand().size() == deckComponent.MaxHandSize);
        REQUIRE(deckComponent.GetDeck().size() == 5);
        REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
    }

    SECTION("No Card in discard, no card in deck, draw 2 does nothing"){
        REQUIRE(deckComponent.GetHand().empty() == true);
        REQUIRE(deckComponent.GetDeck().empty() == true);
        REQUIRE(deckComponent.GetDiscardedCards().empty() == true);

        deckComponent.DrawCard(2);

        REQUIRE(deckComponent.GetHand().empty() == true);
        REQUIRE(deckComponent.GetDeck().empty() == true);
        REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
    }
}
