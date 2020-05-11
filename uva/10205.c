#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *suit[4] = { "Clubs", "Diamonds", "Hearts", "Spades" };
const char *rank[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10",
			 "Jack", "Queen", "King", "Ace" };

const char *getsuit(int card)
{
  return suit[card/13];
}

const char *getrank(int card)
{
  return rank[card%13];
}

void apply(int *cards, int *shuffle)
{
  int temp[52];
  int i;

  for (i = 0; i < 52; i++) {
    temp[i] = cards[i];
  }

  for (i = 0; i < 52; i++) {
    cards[i] = temp[shuffle[i]-1];
  }
}

void solve_case(void)
{
  int cards[52];
  int shuffles[100][52];
  char line[1024];
  int n, i, j, k;
  

  for (i = 0; i < 52; i++) {
    cards[i] = i;
  }

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    for (j = 0; j < 52; j++) {
      scanf("%d\n", &shuffles[i][j]);
    }
  }

  while (fgets(line, 1024, stdin) && strlen(line) > 1) {
    k = atoi(line) - 1;
    apply(cards, shuffles[k]);
  }

  for (i = 0; i < 52; i++) {
    printf("%s of %s\n", getrank(cards[i]), getsuit(cards[i]));
  }
}

int main(void)
{
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    solve_case();
    if (cases) {
      printf("\n");
    }
  }
  return 0;
}
