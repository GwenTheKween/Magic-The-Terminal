#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "deck.h"

enum player_AI {
    HUMAN,
    RANDOM,
};

class Player{
private:
    //life points the player has.  Starts at 20, can go up or down.
    //Player loses when this reaches 0.
    unsigned life;

    //Cards that the player can draw to make a move.
    //Player loses when the deck is empty.
    deck d;

    //Poison counters on the player.  These are only given by specific
    //card effects, and are almost never removed.
    //Player loses when this reaches 10.
    unsigned poison;

    //Cards that are in the hand of the player.  Player will be able to
    //play one of these by paying the cost of the card.
    //This only stores the index of the cards, using the same deck index.
    std::vector<int> hand;

    //What kind of intelligence will govern this player, a Human one, or
    //an artificial one - and which is it.
    player_AI ai;
public:
    Player(deck dd, player_AI AI=RANDOM);
};

#endif /*__PLAYER_H__*/
