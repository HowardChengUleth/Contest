#include <stdio.h>
#include <string.h>

int main(void)
{
  int n, k, i;
  int first = 1;
  int win[100], loss[100];
  int p1, p2;
  char ch1[100], ch2[100];

  while (scanf("%d", &n) == 1 && n > 0) {
    if (!first) {
      printf("\n");
    }
    first = 0;

    scanf("%d", &k);
    
    for (i = 0; i < n; i++) {
      win[i] = loss[i] = 0;
    }
    
    for (i = 0; i < k*n*(n-1)/2; i++) {
      scanf("%d %s %d %s", &p1, ch1, &p2, ch2);
      p1--; p2--;
      if (!strcmp(ch1, "rock") && !strcmp(ch2, "paper")) {
	win[p2]++;  loss[p1]++;
      }
      if (!strcmp(ch2, "rock") && !strcmp(ch1, "paper")) {
	win[p1]++;  loss[p2]++;
      }
      if (!strcmp(ch1, "scissors") && !strcmp(ch2, "rock")) {
	win[p2]++;  loss[p1]++;
      }
      if (!strcmp(ch2, "scissors") && !strcmp(ch1, "rock")) {
	win[p1]++;  loss[p2]++;
      }
      if (!strcmp(ch1, "paper") && !strcmp(ch2, "scissors")) {
	win[p2]++;  loss[p1]++;
      }
      if (!strcmp(ch2, "paper") && !strcmp(ch1, "scissors")) {
	win[p1]++;  loss[p2]++;
      }
    }

    for (i = 0; i < n; i++) {
      if (win[i] + loss[i]) {
	printf("%.3f\n", win[i] / (double)(win[i] + loss[i]));
      } else {
	printf("-\n");
      }
    }

  }

  return 0;
}
