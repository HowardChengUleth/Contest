/* @JUDGE_ID: 1102NT 305 C "" */

#include <stdio.h>

int good(int *people, int m)
{
  int i, j, count;

  i = -1;
  while (people[1] > 0) {
    /* look for next victim */
    count = people[0] + people[1];
    i = (i+m) % count;

    if (i < people[0]) {
      return 0;
    }
    people[1]--;
    i--;
  }
  return 1;
}

int best(int k)
{
  int people[2];
  int m;

  for (m = k+1; 1; m++) {
    people[0] = people[1] = k;
    if (good(people, m)) {
      return m;
    }
  }
}

int main(void)
{
  int k;
  printf("int table[14] = {\n");
  printf("  0,\n");
  for (k = 1; k <= 13; k++) {
    printf("  %d%s\n", best(k), (k == 13) ? "" : ",");
  }
  printf("};\n");
  return 0;
}
