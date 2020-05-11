/* @JUDGE_ID: 1102NT 129 C "Linear search" */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int violate(char *seq, int len, int sublen)
{
  int s1, s2, i, j;

  s2 = len-sublen;
  s1 = s2-sublen;
  assert(s1 >= 0 && s2 >= 0);
  for (i = s1, j = s2; i < s2; i++, j++) {
    if (seq[i] != seq[j]) {
      return 0;
    }
  }
  assert(j >= len);
  return 1;
}

int check_okay(char *seq, int len)
{
  int i;

  for (i = 1; 2*i <= len; i++) {
    if (violate(seq, len, i)) {
      return 0;
    }
  }
  return 1;
}

int find_next(char *seq, int len, int l)
{
  int k;

  /* start by adding one more letter, and work backward */
  seq[len] = 'A' - 1;

  for (k = len; k >= 0; k--) {
    for (seq[k]++; seq[k] < 'A'+l; seq[k]++) {
      if (check_okay(seq, k+1)) {
	return k+1;
      }
    }
  }
  assert(0);
  return 0;
}

int check(char *seq, int len)
{
  int i, j, k, match;

  for (k = 1; k <= len/2; k++) {
    for (i = 0; i+k+k <= len; i++) {
      match = 1;
      for (j = 0; j < k && match; j++) {
	if (seq[i+j] != seq[i+k+j]) {
	  match = 0;
	}
      }
      if (match) {
	return 0;
      }
    } 
  }
  return 1;
}

void process(int n, int l)
{
  char seq[30000];
  int len = 0;
  int count;
  int i;

  seq[len++] = 'A';
  assert(check(seq, len));
  for (i = 1; i < n; i++) {
    len = find_next(seq, len, l);
    assert(check(seq, len));
  }
  assert(check(seq, len));
  assert(len >= 0 && len <= 80);
  count = 0;
  for (i = 0; i < len; i++) {
    if (i % 4 == 0) {
      if (++count <= 16) {
	if (count != 1) {
	  putchar(' ');
	}
      } else {
	putchar('\n');
	count = 1;
      }
    }
    putchar(seq[i]);
  }
  printf("\n%d\n", len);
}

int main(void)
{
  int n, l;

  scanf("%d %d", &n, &l);
  while (n != 0 || l != 0) {
    assert(n > 0 && 1 <= l && l <= 26);
    process(n, l);
    scanf("%d %d", &n, &l);
  }
  return 0;
}
