/* @JUDGE_ID: 1102NT 127 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef char Card[3];

int height[52];
Card stack[52][52];
int piles;

int read_cards(void)
{
  int i;

  scanf("%s", stack[0][0]);
  if (stack[0][0][0] == '#') {
    return 0;
  }
  height[0] = 1;

  for (i = 1; i < 52; i++) {
    scanf("%s", stack[i][0]);
    height[i] = 1;
  }
  piles = 52;

  return 1;
}

int match(Card c1, Card c2)
{
  return (c1[0] == c2[0] || c1[1] == c2[1]);
} 

int next_move(int *dest)
{
  int i;

  for (i = 1; i < piles; i++) {
    if (i >= 3 && match(stack[i][height[i]-1], stack[i-3][height[i-3]-1])) {
      *dest = i-3;
      return i;
    }
    if (match(stack[i][height[i]-1], stack[i-1][height[i-1]-1])) {
      *dest = i-1;
      return i;
    }
  }
  return 0;
}

void shift_stack(int src)
{
  int i, j;

  for (i = src+1; i < piles; i++) {
    for (j = 0; j < height[i]; j++) {
      strcpy(stack[i-1][j], stack[i][j]);
    }
    height[i-1] = height[i];
  }
  piles--;
}

int make_move(void)
{
  int src, dest;

  if ((src = next_move(&dest))) {
    strcpy(stack[dest][height[dest]], stack[src][height[src]-1]);
    height[dest]++;
    height[src]--;
    if (!height[src]) {
      shift_stack(src);
    }
    return 1;
  } else {
    return 0;
  }
}

int main(void)
{
  int i;
  while (read_cards()) {
    while (make_move())
      ;
    printf("%d pile%s remaining:", piles, (piles > 1) ? "s" : "");
    for (i = 0; i < piles; i++) {
      printf(" %d", height[i]);
    }
    printf("\n");
  }
  return 0;
}
