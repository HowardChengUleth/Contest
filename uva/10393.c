/* @JUDGE_ID: 1102NT 10393 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char *finger[11] = {
  "",
  "qaz",
  "wsx",
  "edc",
  "rfvtgb",
  " ",
  " ",
  "yhnujm",
  "ik,",
  "ol.",
  "p;/"
};

char words[1000][51];
int N, F;
char map[256];

char *output[1000];
int outsize;

int cmp(const void *a, const void *b)
{
  char *x = (char *)a, *y = (char *)b;
  int t = strlen(y) - strlen(x);
  if (t) {
    return t;
  } else {
    return strcmp(x, y);
  }
}

int can_type(int i)
{
  int j;

  for (j = 0; words[i][j]; j++) {
    if (!map[(int)words[i][j]]) {
      return 0;
    }
  }
  return 1;
}

int main(void)
{
  int i, t;

  
  while (scanf("%d %d", &F, &N) == 2) {
    memset(map, 1, 256);
    while (F-- > 0) {
      scanf("%d", &t);
      for (i = 0; finger[t][i]; i++) {
	map[(int)finger[t][i]] = 0;
      }
    }
    for (i = 0; i < N; i++) {
      scanf("%s", words[i]);
    }
    qsort(words, N, 51, cmp);

    outsize = 0;
    for (i = 0; i < N; i++) {
      if (i > 0 && !strcmp(words[i], words[i-1])) {
	continue;
      }
      if (can_type(i)) {
	if (outsize == 0 || strlen(words[i]) == strlen(output[0])) {
	  output[outsize++] = words[i];
	} else {
	  assert(strlen(words[i]) < strlen(output[0]));
	}
      }
    }

    printf("%d\n", outsize);
    for (i = 0; i < outsize; i++) {
      printf("%s\n", output[i]);
    }
  }
  return 0;
}
