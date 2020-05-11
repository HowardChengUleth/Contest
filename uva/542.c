#include <stdio.h>

int can_play(int i, int j, int round)
{
  return ((i >> round) == (j >> round)) &&
    (i >> (round-1)) != (j >> (round-1));
}

int main(void)
{
  char country[16][100];
  int prob[16][16];
  int i, j;
  int round;

  double reach_p[16][5];    /* probability of team i to advance to round j+1 */

  for (i = 0; i < 16; i++) {
    scanf("%s", country[i]);
  }
  for (i = 0; i < 16; i++) {
    for (j = 0; j < 16; j++) {
      scanf("%d", &prob[i][j]);
    }
    reach_p[i][0] = 1;      /* always reach the 1st round */
  }

  for (round = 1; round <= 4; round++) {
    for (i = 0; i < 16; i++) {
      reach_p[i][round] = 0;
      for (j = 0; j < 16; j++) {
	if (i != j && can_play(i, j, round)) {
	  reach_p[i][round] += reach_p[i][round-1] * reach_p[j][round-1] *
	    (prob[i][j]/100.0);
	}
      }
    }
  }

  for (i = 0; i < 16; i++) {
    printf("%-10s p=%4.2f%%\n", country[i], reach_p[i][4]*100);
  }

  return 0;
}
