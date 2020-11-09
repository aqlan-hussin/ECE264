#include "answer06.h"
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
// You may add more functions in this file.

// do NOT modify any #ifdef or #endif
// they are used for giving partial credits

// The following line must be above divideDeck
#ifdef TEST_DIVIDE 
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

  int i;
  int n = origdeck.size - 1;

  for(i = 0; i < n; i++) {
    upperdeck[i].size = i + 1;
    lowerdeck[i].size = n - i;
    bcopy(origdeck.cards, upperdeck[i].cards, (i+1) * sizeof(char));
    bcopy(&origdeck.cards[i+1], lowerdeck[i].cards, (n-i) * sizeof(char));
    
  }
  

}
#endif
// The previous line must be below divideDeck

#ifdef TEST_INTERLEAVE
// reuse what you wrote for PE05
static void helper(const char * uppercards, int m, const char * lowercards, int n, CardDeck newdeck, int k)
{
  if(m == -1){
    bcopy(lowercards, newdeck.cards, (n+1) * sizeof(char));
    printDeck(newdeck);
    printf("\n");
    return;
    }

  if(n == -1){
    bcopy(uppercards, newdeck.cards, (m+1) * sizeof(char));
    printDeck(newdeck);
    printf("\n");
    return;
    }

  newdeck.cards[k] = uppercards[m];
  helper(uppercards, m-1, lowercards, n, newdeck, k-1);

  newdeck.cards[k] = lowercards[n];
  helper(uppercards, m, lowercards, n-1, newdeck, k-1);

}

void interleave(CardDeck upperdeck, 
    CardDeck lowerdeck)
{
  // create a new deck storing the result
  // this new deck's size should be the sum of the
  // sizes of upperdeck and lowerdeck
  
  int m = upperdeck.size;
  int n = lowerdeck.size;
  int k = m + n;
  CardDeck newdeck;
  newdeck.size = k;
  
  // call the helper function with appropriate arguments

  helper(upperdeck.cards, upperdeck.size - 1, lowerdeck.cards, lowerdeck.size - 1, newdeck, k-1);

  return;
  
}
#endif

#ifdef TEST_SHUFFLE
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
  int numpairs = origdeck.size-1;
  
  CardDeck * upperdeck = NULL;
  CardDeck * lowerdeck = NULL;

  // allocate memory
  upperdeck = malloc(sizeof(CardDeck)*origdeck.size);
  if (upperdeck == NULL)
    {
      return;
    }
  lowerdeck = malloc(sizeof(CardDeck)*origdeck.size);    
  if (lowerdeck == NULL)
    {
      return;
    }

  // call divideDeck to fill upperdeck and lowerdeck 
  divideDeck(origdeck, upperdeck, lowerdeck);

  while (numpairs > 0)
    {
      interleave(upperdeck[numpairs - 1], lowerdeck[numpairs - 1]);
      numpairs--;
    }

  free(upperdeck);
  free(lowerdeck);
} 
#endif
