#include "DeckComponent.h"
#include <vector>
#include "BaseComponent.h"
DeckComponent::DeckComponent() : BaseComponent()
{
    _energy = 0;
}

DeckComponent::~DeckComponent()
{
    //dtor
}

int DeckComponent::GetEnergy(){
    return _energy;
}

int DeckComponent::AddEnergy(int energyToAdd){
    _energy += energyToAdd;
    return GetEnergy();
}

int DeckComponent::SetEnergy(int energyToSet){
    _energy = energyToSet;
    return GetEnergy();
}

void DeckComponent::AddCardToDeck(Card card){
    _deck.push_back(card);
}

void DeckComponent::AddCardToDiscard(Card card){
    _discardedCards.push_back(card);
}

void DeckComponent::AddCardToExhaustedCards(Card card){
    _exhaustedCards.push_back(card);
}

void DeckComponent::AddCardToHand(Card card){
    _hand.push_back(card);
}

std::vector<Card> DeckComponent::GetHand(){
    return _hand;
}

std::vector<Card> DeckComponent::GetDeck(){
    return _deck;
}

std::vector<Card> DeckComponent::GetExhaustedCards(){
    return _exhaustedCards;
}

std::vector<Card> DeckComponent::GetDiscardedCards(){
    return _discardedCards;
}
