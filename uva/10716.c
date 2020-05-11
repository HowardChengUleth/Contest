/* @JUDGE_ID: 1102NT 10716 C "" */

#include <stdio.h>
#include <string.h>

void swap(char *str, int i, int j)
{
  char t = str[i];
  str[i] = str[j];
  str[j] = t;
}

int swaps(char *str, int start, int end)
{
  int i, t;

  if (start >= end) {
    return 0;
  }

  if (str[start] == str[end]) {
    return swaps(str, start+1, end-1);
  }

  /* find first match of str[end] */
  for (i = start+1; i < end && str[i] != str[end]; i++) ;

  if (i == end) {
    /* no match, it better be an odd length string */
    if ((end+1-start) % 2) {
      t = swaps(str, start, end-1);
      if (t >= 0) {
	return t + (end+1-start)/2;   /* need to swap to middle */
      } else {
	return -1;
      }
    } else {
      return -1;
    }
  }

  /* swap to the front */
  for (t = i; t > start; t--) {
    swap(str, t, t-1);
  }
  t = swaps(str, start+1, end-1);
  if (t >= 0) {
    return (i-start) + t;
  } else {
    return -1;
  }
}

int main(void)
{
  int n;
  char str[101];
  int res;
  
  scanf("%d", &n);
  while (n-- > 0) {
    scanf("%s", str);
    if ((res = swaps(str, 0, strlen(str)-1)) >= 0) {
      printf("%d\n", res);
    } else {
      printf("Impossible\n");
    }
  }

  return 0;
}
