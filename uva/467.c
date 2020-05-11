#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int lights[10];
int n;

int read_case(void)
{
  char line[1024];
  char *p;

  n = 0;

  if (fgets(line, 1024, stdin)) {
    for (p = line; p = strtok(p, " \n"); p = NULL) {
      lights[n++] = atoi(p);
    }
  }
  return n;
}

void solve_case(void)
{
  char green[60*60+1];
  int i, j, k;
  int first;

  for (i = 0; i <= 60*60; i++) {
    green[i] = 1;
  }

  for (i = 0; i < n; i++) {
    j = 0;
    while (j <= 60*60) {
      j += lights[i] - 5;
      for (k = 0; k < 5+lights[i] && j <= 60*60; k++, j++) {
	green[j] = 0;
      }
    }
  }

  first = 1;
  for (i = 0; i <= 60*60; i++) {
    if (first && !green[i]) {
      first = 0;
    } else if (!first && green[i]) {
      printf("synchs again at %d minute(s) and %d second(s) after all turning green.\n",
	     i/60, i%60);
      return;
    }
  }
  printf("is unable to synch after one hour.\n");

}

int main(void)
{
  int set_no = 1;
  while (read_case()) {
    printf("Set %d ", set_no++);
    solve_case();
  }
  return 0;
}
