/* @JUDGE_ID: 1102NT 10295 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m, n;

typedef struct {
  char word[17];
  int value;
} Dictionary;

Dictionary dict[1000];

int cmp(const void *a, const void *b)
{
  Dictionary *x = (Dictionary *)a;
  Dictionary *y = (Dictionary *)b;

  return strcmp(x->word, y->word);
}

int binsearch(char *key)
{
  int lo = 0, hi = m-1;
  int mid, t;

  while (lo <= hi) {
    mid = (lo + hi) / 2;
    if ((t = strcmp(key, dict[mid].word)) == 0) {
      return dict[mid].value;
    } else if (t > 0) {
      lo = mid+1;
    } else if (t < 0) {
      hi = mid-1;
    }
  }
  return 0;
}

int main(void)
{
  int i;
  int sum = 0;
  char buffer[1024];

  scanf("%d %d", &m, &n);
  for (i = 0; i < m; i++) {
    scanf("%s %d", dict[i].word, &(dict[i].value));
  }

  qsort(dict, m, sizeof(Dictionary), cmp);

  sum = 0;
  while (scanf("%s", buffer) == 1) {
    if (!strcmp(buffer, ".")) {
      printf("%d\n", sum);
      sum = 0;
    } else {
      sum += binsearch(buffer);
    }
  }

  return 0;
}
