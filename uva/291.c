/* @JUDGE_ID: 1102NT 291 C "" */

#include <stdio.h>

void perm(int tour[9], int index, int used[6][6])
{
  int i, t;
  
  if (index == 9) {
    for (i = 0; i < 9; i++) {
      printf("%d", tour[i]);
    }
    printf("\n");
    return;
  }

  t = tour[index-1];
  for (i = 1; i <= 5; i++) {
    if (!used[t][i]) {
      used[t][i] = used[i][t] = 1;
      tour[index] = i;
      perm(tour, index+1, used);
      used[t][i] = used[i][t] = 0;
    }
  }
}

int main(void)
{
  int used[6][6];
  int i, j;
  int tour[9];

  for (i = 1; i <= 5; i++) {
    for (j = 1; j <= 5; j++) {
      used[i][j] = 1;
    }
  }

  used[1][2] = used[2][1] = 0;
  used[1][3] = used[3][1] = 0;
  used[1][5] = used[5][1] = 0;
  used[2][3] = used[3][2] = 0;
  used[2][5] = used[5][2] = 0;
  used[3][4] = used[4][3] = 0;
  used[3][5] = used[5][3] = 0;
  used[4][5] = used[5][4] = 0;

  tour[0] = 1;
  perm(tour, 1, used);
  return 0;
}
