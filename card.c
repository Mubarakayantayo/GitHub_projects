#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "card.h"

#define LONGNAMES

static const int BUFFER_LENGTH=1024;

#ifdef LONGNAMES
static char *long_suits[] = {"oops","Clubs", "Diamonds", "Hearts", "Spades"};
static char *long_ranks[] = {"oops", "oops", "2", "3", "4", "5", "6", "7", "8",
                             "9", "Ten", "Jack", "Queen", "King", "Ace"};
#endif

static char *short_suits = "?CDHS";
static char *short_ranks = "?.23456789TJQKA";


/* purpose: print a message and terminate the program
 * input:   the message
 * returns: never!! terminates progam
 */
static void die(char *msg)
{
  perror(msg);
  exit(-1);
}

/* purpose: get the index in a string of a character
 * input:   the character, c, and the string, s
 * returns: the index of c or the index of '?' is c is not in s
            (kills the program if '?' is not found)
 */
static int get_index(char c, char *s)
{
  c = toupper(c);
  char *at = strchr(s, c);
  if (at == NULL)
    at = strchr(s, '?');
  if (at == NULL)
    die("get index in trouble :(");
  return (long)at - (long)s;
}

/* purpose: read in a card
 * input:   nothing
 * returns: the card as read from stdin
 */
card_t card_read(){

  char c_rank, c_suit;
  char input[BUFFER_LENGTH];
  if (fgets(input, BUFFER_LENGTH, stdin) == NULL)
    die("fgets fail");
  sscanf(input, " %c%c", &c_rank, &c_suit);
  int rank = get_index(c_rank, short_ranks);
  int suit = get_index(c_suit, short_suits);
  if (rank == 0 || suit == 0){
    return INVALID_CARD;
  }
  return card_create(rank, suit);

}

/* purpose: create a card with a given rank and suit
 * input:   the rank and suit
 * returns: the newly allocated card
 */
card_t card_create(int rank,int suit){
  card_t new_card;
  new_card.suit = suit;
  new_card.rank = rank;
  return new_card;
}

/* purpose: print a card
 * input:   the card
 * returns: nothing (printing is a side effect)
 */
void card_print(card_t c)
{
#ifdef LONGNAMES
  printf("%s of %s", long_ranks[c.rank], long_suits[c.suit]);
#else
  printf("%c%c", short_ranks[c.rank], short_suits[c.suit]);
#endif
}


/* purpose: compare two cards
 * input:   the cards, c1 and c2
 * returns: 0 is the two cards are equal, <0 ir c1<c2, and >0 otherwise
 */
int card_compare(card_t c1, card_t c2)
{
  if (c1.suit != c2.suit)
    return c2.suit - c1.suit;
  else
    return c2.rank - c1.rank;
}
