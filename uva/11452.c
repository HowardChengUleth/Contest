#include <stdio.h>
#include <string.h>
#include <assert.h>

int find_period(char *steps, int len)
{
  int p;
  int i, good;

  for (p = 1; p < len; p++) {
    if (len/p >= 3) continue;
    if ((len+p-1)/p < 2) break;

    
    good = 1;
    for (i = 0; i+p < len; i++) {
      good &= (steps[i] == steps[i+p]);
    }
    if (good) {
      return p;
    }
  }
  assert(0);
}

int main(void)
{
  int N;
  char steps[2001];
  int len, period;
  int i, j;

  scanf("%d", &N);
  while (N-- > 0) {
    scanf("%s", steps);
    len = strlen(steps);
    period = find_period(steps, len);
    len %= period;
    
    j = len;
    for (i = 0; i < 8; i++) {
      putchar(steps[j]);
      j = (j+1) % period;
    }
    printf("...\n");
      
  }
  return 0;
}
