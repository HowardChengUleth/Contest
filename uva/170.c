/* @JUDGE_ID: 1102NT 170 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char deck[52][3];
char pile[13][20][3];
int pile_num[13];

int read_case(void)
{
  int i;

  scanf("%s", deck[0]);
  if (!strcmp(deck[0], "#")) {
    return 0;
  }
  for (i = 1; i < 52; i++) {
    scanf("%s", deck[i]);
  }
  return 1;
}

void deal_cards(void)
{
  int i, p;

  for (i = 0; i < 13; i++) {
    pile_num[i] = 0;
  }

  p = 0;
  for (i = 51; i >= 0; i--) {
    strcpy(pile[p][pile_num[p]++], deck[i]);
    if (++p == 13) {
      p = 0;
    }
  }
}

int get_index(char *card)
{
  if (*card == 'A') {
    return 0;
  } else if (isdigit(*card)) {
    return *card - '0' - 1;
  } else if (*card == 'T') {
    return 9;
  } else if (*card == 'J') {
    return 10;
  } else if (*card == 'Q') {
    return 11;
  } else if (*card == 'K') {
    return 12;
  } else {
    assert(0);
  }
}

void do_case(void)
{
  int done = 0;
  int i, p;
  char card[3];
  int total = 0;

  deal_cards();
  p = 12;

  while (pile_num[p] > 0) {
    strcpy(card, pile[p][--pile_num[p]]);
    p = get_index(card);
  }
  for (i = 0; i < 13; i++) {
    total += pile_num[i];
  }
  printf("%02d,%s\n", 52-total, card);
}

int main(void)
{
  while (read_case()) {
    do_case();
  }
  return 0;
}
