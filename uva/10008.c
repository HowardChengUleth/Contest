/* @JUDGE_ID: 1102NT 10008 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
  int letter;
  int count;
} Info;

Info info[26];

int cmp(const void *a, const void *b)
{
  Info *x = (Info *)a, *y = (Info *)b;

  if (x->count != y->count) {
    return y->count - x->count;
  } else {
    return x->letter - y->letter;
  }
}

int main(void)
{
  int i, c;

  for (i = 0; i < 26; i++) {
    info[i].letter = 'A' + i;
    info[i].count = 0;
  }
  scanf("%d", &i);     /* just ignore it */
  while ((c = getchar()) != EOF) {
    if (isalpha(c)) {
      c = toupper(c) - 'A';
      info[c].count++;
    }
  }
  qsort(info, 26, sizeof(*info), cmp);
  for (i = 0; i < 26; i++) {
    if (info[i].count) {
      printf("%c %d\n", (char)info[i].letter, info[i].count);
    }
  }
  
  return 0;
}
