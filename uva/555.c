/* @JUDGE_ID: 1102NT 555 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char card[4][13][3];

int get_dealer(char c)
{
  switch (c) {
  case 'N':
    return 0;
  case 'E':
    return 1;
  case 'S':
    return 2;
  case 'W':
    return 3;
  default:
    assert(0);
  }
}

int suit_val(char c)
{
  switch (c) {
  case 'C':
    return 0;
  case 'D':
    return 1;
  case 'S':
    return 2;
  case 'H':
    return 3;
  default:
    printf("c = %c\n", c);
    assert(0);
  }
}

int card_val(char c)
{
  if ('2' <= c && c <= '9') {
    return c - '0';
  }
  switch (c) {
  case 'T':
    return 10;
  case 'J':
    return 11;
  case 'Q':
    return 12;
  case 'K':
    return 13;
  case 'A':
    return 14;
  default:
    printf("c = %c\n", c);
    assert(0);
  }
}

int cmp(const void *a, const void *b)
{
  char *x = (char *)a;
  char *y = (char *)b;
  
  int t = suit_val(x[0]) - suit_val(y[0]);
  
  if (t) {
    return t;
  }
  return card_val(x[1]) - card_val(y[1]);
}
  

int main (void) {
  char buffer[100];
  int dealer, ptr, hand;
  char pos[5] = "NESW";
  int i, j;

  while (scanf("%1s", buffer) == 1 && strcmp(buffer, "#")) {
    dealer = get_dealer(buffer[0]);
    ptr = 0;
    hand = (dealer+1)%4;
    while (ptr < 52) {
      scanf("%2s", buffer);
      strcpy(card[hand][ptr/4], buffer);
      hand = (hand+1)%4;
      ptr++;
    }
    for (i = 2; i < 6; i++) {
      qsort(card[i%4], 13, 3*sizeof(char), cmp);
      printf("%c:", pos[i%4]);
      for (j = 0; j < 13; j++) {
	printf("%3s", card[i%4][j]);
      }
      printf("\n");
    }
  }
  return 0;
}
