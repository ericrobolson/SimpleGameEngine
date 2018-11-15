#include "catch.hpp"
#include "EntityComponentManager.h"
#include <vector>
#include <memory>
#include "DeckComponent.h"


SCENARIO("DeckComponent::Constructor"){
    DeckComponent deckComponent;

    REQUIRE(deckComponent.GetDeck().empty() == true);
    REQUIRE(deckComponent.GetExhaustedCards().empty() == true);
    REQUIRE(deckComponent.GetDiscardedCards().empty() == true);
    REQUIRE(deckComponent.GetHand().empty() == true);
}

SCENARIO("DeckComponent::AddCardToDeck"){
    DeckComponent deckComponent;
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
    DeckComponent deckComponent;
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
    DeckComponent deckComponent;
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
    DeckComponent deckComponent;
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
    DeckComponent deckComponent;

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
