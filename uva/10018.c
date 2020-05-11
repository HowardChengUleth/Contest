/* @JUDGE_ID: 1102NT 10018 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pal(int n, char *num)
{
  int i;

  for (i = 0; i < n/2; i++) {
    if (num[i] != num[n-1-i]) {
      return 0;
    }
  }
  return 1;
}

int main(void)
{
  int cases;
  char num[20], rev[20], t;
  int steps, i, n, c;
  
  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%s", num);
    n = strlen(num);
    for (i = 0; i < n/2; i++) {
      t = num[i];
      num[i] = num[n-1-i];
      num[n-1-i] = t;
    }
    for (i = 0; i < n; i++) {
      num[i] -= '0';
    }
    
    steps = 0;
    do {
      for (i = 0; i < n; i++) {
	rev[i] = num[n-1-i];
      }

      c = 0;
      for (i = 0; i < n; i++) {
	num[i] += rev[i] + c;
	c = (num[i] > 9);
	if (c) {
	  num[i] -= 10;
	}
      }
      if (c) {
	num[n++] = 1;
      }
      
      steps++;
    } while (!pal(n, num));

    printf("%d ", steps);
    for (i = 0; i < n; i++) {
      printf("%d", num[i]);
    }
    printf("\n");
  }
  return 0;
}
