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


SCENARIO("DeckComponent::DrawCards"){
    DeckComponent deckComponent;
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
