/* @JUDGE_ID: 1102NT 673 C "" */

#include <stdio.h>
#include <ctype.h>
#include <assert.h>

char valid(char *s)
{
  char stack[200];
  int stack_size = 0;
  int i;

  for (i = 0; s[i] != '\n'; i++) {
    switch (s[i]) {
    case '[': case '(':
      stack[stack_size++] = s[i];
      break;
    case ']':
      if (!stack_size || stack[--stack_size] != '[') return 0;
      break;
    case ')':
      if (!stack_size || stack[--stack_size] != '(') return 0;
      break;
    default:
      return 0;
    }
  }
  return stack_size == 0;
}

int main(void)
{
  int cases;
  char s[1024];

  fgets(s, 1024, stdin);
  sscanf(s, "%d", &cases);
  while (cases-- > 0) {
    fgets(s, 1024, stdin);
    printf("%s\n", valid(s) ? "Yes" : "No");
  }

  return 0;
}
