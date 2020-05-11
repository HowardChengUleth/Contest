#include <stdio.h>

int coins[5] = {1, 5, 10, 25, 50};
int ways[5][7490];

int main(void)
{
  int i, j;


  for (j = 0; j <= 7489; j++) {
    ways[0][j] = 1;
  }
  
  for (i = 1; i < 5; i++) {
    for (j = 0; j <= 7489; j++) {
      ways[i][j] = ways[i-1][j];
      if (j >= coins[i]) {
	ways[i][j] += ways[i][j-coins[i]];
      }
    }
  }
    
  while (scanf("%d", &j) == 1) {
    printf("%d\n", ways[4][j]);
  }
  return 0;
}
