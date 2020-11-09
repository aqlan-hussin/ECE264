#include "answer02.h"
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

// You can add more functions to this file.
//
// If you allocate for space, you are responsible for freeing the space
// 
// You will lose 50% points if the amount of allocated memory is not
// determined by the size of the original deck.  To be more precise,
// you will lose 50% point if you use 100, 1000, 10000 (or any other
// fixed number) without clear explanation.
//

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

static void helper(const char * uppercards, int m, const char * lowercards, int n, CardDeck newdeck, int p, int k)
{
  if(m == -1){
    bcopy(lowercards, newdeck.cards, (n+1) * sizeof(char));
    repeatShuffle(newdeck, k-1);
    return;
    }

  if(n == -1){
    bcopy(uppercards, newdeck.cards, (m+1) * sizeof(char));
    repeatShuffle(newdeck, k-1);
    return;
    }

  newdeck.cards[p] = uppercards[m];
  helper(uppercards, m-1, lowercards, n, newdeck, p-1, k);

  newdeck.cards[p] = lowercards[n];
  helper(uppercards, m, lowercards, n-1, newdeck, p-1, k);


}

void interleave(CardDeck upperdeck, 
		CardDeck lowerdeck, int k)
{
  // create a new deck storing the result
  // this new deck's size should be the sum of the
  // sizes of upperdeck and lowerdeck
  
  int m = upperdeck.size;
  int n = lowerdeck.size;
  int p = m + n;
  CardDeck newdeck;
  newdeck.size = p;
  
  // call the helper function with appropriate arguments

  helper(upperdeck.cards, upperdeck.size - 1, lowerdeck.cards, lowerdeck.size - 1, newdeck, p-1, k);


  return;
  
}

void repeatShuffle(CardDeck origdeck, int k)
{
  // origdeck contains the number of cards
  // the number of upper-low deck pairs should be 
  //     the number of cards - 1
  // this function has the following steps:
  //    if (k <= 0), no shuffling, print the only possible outcome
  //    otherwise, 
  //       for each pair of upper and lower decks, interleave the cards,
  //           when the interleaving is complete, have to perform another 
  //           k-1 rounds of shuffling with the new deck
  //
  // Print only the results obtained after k rounds of shuffling
  // see interleave in PE05 and shuffle in PE06 for more details

  if (k <= 0) {
    printDeck(origdeck);
    return;
  }

  int numpairs = origdeck.size-1;
  
  CardDeck * upperdeck = NULL;
  CardDeck * lowerdeck = NULL;

  // allocate memory and check whether the allocation is successful
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
      interleave(upperdeck[numpairs - 1], lowerdeck[numpairs - 1], k);
      numpairs--;
    }

  free(upperdeck);
  free(lowerdeck);

}
