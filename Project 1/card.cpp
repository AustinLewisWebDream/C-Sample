/* File: card.h
 * Course: CS216-00x
 * Project: Lab12 (as part of Project 3)
 * Purpose: the implementation of member functions for the Card class.
 *** DO NOT CHANGE THIS FILE ***
 *
 */

#include "card.h"

// Default constructor marks card as invalid
Card::Card() {
    suit = Invalid ;
    point = 0 ;
}

// Alternate constructor
Card::Card(cSuits s, cPoints p) 
{
    suit = s;
    point = p;
}

// compare the two cards in descending order by points
// if the order of C1 and C2 in descending order by points, return 1;
// if C1 and C2 are of the same points, return 0;
// otherwise, return -1
int Card::compareByPoint(const Card& C1, const Card& C2)
{
    if (C1.point > C2.point)
        return 1;
    if (C1.point == C2.point)
        return 0;
    return -1;
}


// access the card point value
Card::cPoints Card::getPoint() const
{
    return point;
}
// access the card suit value
Card::cSuits Card::getSuit() const
{
    return suit;
}

// operator overloading for operators "<" and "<<"
// they are defined as friend functions

// define the operator "<" for Card class

bool operator<(Card C1, Card C2)
{
    if (C1.point < C2.point)
        return true;
    else
        return false;
}

// define the operator "<<" for Card class
// to send the Card object to the cout
// Display a description of the Card object to standard output
// The output should look like:
// suit-character point-character suit-character  
ostream& operator<<(ostream &out, const Card& C)
{
    // map the point to card face
    // 11 -->J, 12 -->Q, 13 -->K, 14 --> A
    char face;
    char space=' ';
    switch (C.point)
    {
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            face = '0'+ C.point;
            break;
        case 10:
            face = '0';
            space = '1';
            break;
        case 11:
            face = 'J';
            break;
        case 12:
            face = 'Q';
            break;
        case 13:
            face = 'K';
            break;
        case 14:
            face = 'A';
            break;
        default:
            face = '\0';
            break;
    }

    if (face =='\0')
    {
        return (out << "Invalid card value!");
    }

    switch (C.suit)
    {
        case Card::Spade:
            return (out << endl << SPADE << space << face << SPADE << endl);
            break;
        case Card::Club:
            return (out << endl << CLUB << space << face << CLUB << endl);
            break;
        case Card::Heart:
            return (cout << endl << HEART << space << face << HEART << endl);
            break;
        case Card::Diamond:
            return (out << endl << DIAMOND << space << face << DIAMOND << endl);
            break;
        default:
            return (out << "Invalid suit!" << endl);
            break;
    }
}

