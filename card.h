#ifndef CARD_H
#define CARD_H

typedef struct card_s{
  int rank;
  int suit;
} card_t;

static const card_t INVALID_CARD= {0,0};

card_t card_create(int suit, int rank);
void card_print(card_t c);
int card_compare(card_t c1, card_t c2);
card_t card_read();

#endif
