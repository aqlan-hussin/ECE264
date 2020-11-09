#include "answer06.h"
#include <strings.h>
#include <stdio.h>
// You may add more functions in this file.

// do NOT modify any #ifdef or #endif
// they are used for giving partial credits

// The following line must be above divideDeck
void divideDeck(CardDeck origdeck, 
		CardDeck * upperdeck, CardDeck * lowerdeck)
{
  // if the original deck has n cards, there are n - 1 pairs of
  // upper and low decks: 
  // 1.   upper deck has 1 card,      low deck has n - 1 cards
  // 2.   upper deck has 2 cards,     low deck has n - 2 cards
  // 3.   upper deck has 3 cards,     low deck has n - 3 cards
  // ...
  // n-1. upper deck has n - 1 cards, low deck has 1 cards
  
  // upperdeck[0] should store the first card in the original deck
  // upperdeck[1] should store the top two cards in the original deck
  // upperdeck[2] should store the top three cards in the original deck

  // be careful that in CardDeck, cards is an array (thus a pointer)
}
// The previous line must be below divideDeck

// reuse what you wrote for PE05
void interleave(CardDeck upperdeck, 
		CardDeck lowerdeck)
{
}

void shuffle(CardDeck origdeck)
{
  // origdeck contains the number of cards
  // the number of upper-low deck pairs should be 
  //     the number of cards - 1
  // this function has the following steps:
  //    calculate the number of upper-low deck pairs
  //    allocate enough memory to accommodate the pairs
  //    call divideDeck to find these pairs
  //    for each pair of upper-lower deck, interleave the cards
  //    release the allocated memory
  // 
  // The amount of memory allocated in this function must be
  // determined based on the size of the original deck. The program
  // may fail if the allocated memory has a fixed size (some students
  // like to use 1000 but nobody could explain why 1000).  If you do
  // not know how much memory to allocate, please refer to PE05's
  // README.
  // 
  // You will lose 50% points if the amount of allocated memory is not
  // determined by the size of the original deck.  To be more precise,
  // you will use 50% point if you use 100, 1000, 10000 (or any other
  // fixed number) without clear explanation.
  //

  // the following code gives you some hints. You may make any changes
  // as appropriate;
  int numpairs = -1;
  
  CardDeck * upperdeck = NULL;
  CardDeck * lowerdeck = NULL;

  // allocate memory and check whether the allocation is successful

  if (upperdeck == NULL)
    {
    }
  if (lowerdeck == NULL)
    {
    }

  // call divideDeck to fill upperdeck and lowerdeck 

  while (numpairs > 0)
    {
      // for each pairs call interleave
    }
} 
