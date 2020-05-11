#include <stdio.h>
#include <string.h>

char *ones[] = { "", "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix"};
char *tens[] = { "", "x", "xx", "xxx", "xl", "l", "lx", "lxx", "lxxx", "xc", 
		 "c"};

char *label = "ivxlc";

int count[101][256];

void do_count(int n)
{
  int one, ten;
  int i;

  one = n % 10;
  ten = n / 10;
  
  for (i = 0; ones[one][i]; i++) {
    count[n][ones[one][i]]++;
  }
  for (i = 0; tens[ten][i]; i++) {
    count[n][tens[ten][i]]++;
  }

  for (i = 0; label[i]; i++) {
    count[n][label[i]] += count[n-1][label[i]];
  }
}

int main(void)
{
  int i, j, n;

  for (i = 1; i <= 100; i++) {
    do_count(i);
  }

  while (scanf("%d", &n) == 1 && n) {
    printf("%d: %d %c", n, count[n][label[0]], label[0]);
    for (j = 1; label[j]; j++) {
      printf(", %d %c", count[n][label[j]], label[j]);
    }
    printf("\n");
  }
  return 0;
}

