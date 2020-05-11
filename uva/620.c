/* @JUDGE_ID: 1102NT 620 C "" */

#include <stdio.h>
#include <string.h>

char *result[4] = {"SIMPLE", "FULLY-GROWN", "MUTAGENIC", "MUTANT"};

enum { SIMPLE, FULLYGROWN, MUTAGENIC, MUTANT };

int stage(char *s, int len)
{
  if (len < 1) {
    return MUTANT;
  }

  if (len == 1) {
    if (s[0] == 'A') {
      return SIMPLE;
    } else {
      return MUTANT;
    }
  }

  if (s[len-2] == 'A' && s[len-1] == 'B' && stage(s, len-2) != MUTANT) {
    return FULLYGROWN;
  }
  
  if (s[0] == 'B' && s[len-1] == 'A' && stage(s+1, len-2) != MUTANT) {
    return MUTAGENIC;
  }

  return MUTANT;
}

int main(void)
{
  int n;
  char s[10000];

  scanf("%d\n", &n);
  while (n-- > 0) {
    scanf("%s", s);
    printf("%s\n", result[stage(s, strlen(s))]);
  }
  return 0;
}
