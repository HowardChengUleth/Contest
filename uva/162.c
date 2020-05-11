#include <stdio.h>

int num_cover[256];

void addcard(char p[3][52], int n[3], char card, int curr)
{
  int i;

  for (i = n[curr]; i >= 1; i--) {
    p[curr][i] = p[curr][i-1];
  }
  p[curr][0] = card;
  n[curr]++;
}

int simulate(char p[3][52], int n[3])
{
  int curr = 2;
  char stack[52];
  int stack_size = 0;
  int cover = 0;
  int i, to_cover;
  int last_face;

  while (n[curr] > 0) {
    if (!cover) {
      /* plays a card normally */
      cover = num_cover[stack[stack_size++] = p[curr][--n[curr]]];
    } else {
      to_cover = cover;
      for (i = 0; i < to_cover; i++) {
	if (!n[curr]) return 3-curr;      /* no more cards to play */
	cover = num_cover[stack[stack_size++] = p[curr][--n[curr]]];
	if (cover) break;          /* play switches */
      }
      if (!cover) {
	for (i = 0; i < stack_size; i++) {
	  addcard(p, n, stack[i], last_face);
	}
	stack_size = 0;
      }
    }
    if (cover) {
      last_face = curr;
    }
    curr = 3-curr;
  }
  return 3-curr;
}

int main(void)
{
  char card[3];
  char deck[52];
  char p[3][52];
  int n[3];
  int curr;
  int i;

  num_cover['J'] = 1;
  num_cover['Q'] = 2;
  num_cover['K'] = 3;
  num_cover['A'] = 4;

  while (scanf("%s", card) == 1 && card[0] != '#') {
    deck[0] = card[1];
    for (i = 1; i < 52; i++) {
      scanf("%s", card);
      deck[i] = card[1];
    }
    
    /* deal to each player, 0 = bottom of deck */
    n[1] = n[2] = 0;
    curr = 2;       /* 2 = non-dealer, 1 = dealer */
    for (i = 0; i < 52; i++) {
      p[curr][n[curr]++] = deck[i];
      curr = 3-curr;
    }
    
    curr = simulate(p, n);
    printf("%d%3d\n", curr, n[curr]);
  }

  return 0;
}
