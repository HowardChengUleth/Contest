#include <stdio.h>
#include <string.h>

int main(void)
{
  int T, i;
  char line[2000], *p;
  int count;

  scanf("%d", &T);
  fgets(line, 2000, stdin);
  fgets(line, 2000, stdin);

  for (i = 0; i < T; i++) {
    if (i) {
      printf("\n");
    }
    printf("Case #%d:\n", i+1);

    while (fgets(line, 2000, stdin) && line[0] != '\n') {
      count = 0;
      for (p = line; p = strtok(p, " \n"); p = NULL) {
	if (strlen(p) > count) {
	  putchar(p[count++]);
	}
      }
      putchar('\n');
    }

  }
  
  return 0;
}
