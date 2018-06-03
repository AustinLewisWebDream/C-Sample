/* File: deck.cpp
 * Course: CS216-00x
 * Project: Lab12 (as part of Project 3)
 * Purpose: the implementation of member functions for the Deck class.
 *** DO NOT CHANGE THIS FILE ***
 *
 */

#include <cstdlib>
#include <ctime>
#include "deck.h"
        
// create a standard 52-card deck
void Deck::createDeck()
{
    deck.clear();
    for (int s= Card::Spade; s <= SUITS; s++)
        for (Card::cPoints val = CARD_START; val < POINT_RANKS+CARD_START; val++)
        {
            Card::cSuits suit = static_cast<Card::cSuits>(s);
            Card newcard(suit, val);
            deck.push_back(newcard);
        }
}

// shuffle the cards in 52-card deck
void Deck::shuffleDeck()
{
    srand(time(0));
    Card temp;  // for swapping
    for (int i = deck.size()-1; i>= 1; i--)
    {
        int j = rand() % (i+1);
        temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
}

// return a card from the tail of the deck
Card Deck::deal_a_card()
{
    if (deck.size() == 0)
        return Card(Card::Invalid,0);
    else
    {
        Card result = deck.back();
        deck.pop_back();
        return result;
    }
}

