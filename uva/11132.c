#include <stdio.h>
#include <string.h>

int main(void)
{
  int rolls, sides;
  int total;
  char coins[1024];
  int len;
  int chunk, i, j, k, val;

  while (scanf("%dD%d", &rolls, &sides) == 2 && (rolls || sides)) {
    total = 0;
    scanf("%s", coins);
    len = strlen(coins);
    
    chunk = 1;
    k = 2;
    while (k < sides) {
      chunk++;
      k *= 2;
    }
    

    for (i = 0; i + chunk - 1 < len && rolls; i += chunk) {
      val = 0;
      for (j = 0; j < chunk; j++) {
	val = val*2 + (coins[i+j] == 'T');
      }
      val++;
      if (val <= sides) {
	total += val;
	rolls--;
      }
    }
    
    if (rolls) {
      printf("-1\n");
    } else {
      printf("%d\n", total);
    }
  }

  return 0;
}
