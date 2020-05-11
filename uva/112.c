/* @JUDGE_ID: 1102NT 112 C "" */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

static int next_token(void);
static int exist_sum(int sum, int top_level, int *empty);

int main(void)
{
  int sum;

  while (scanf("%d", &sum) == 1) {
    if (exist_sum(sum, 1, NULL)) {
      printf("yes\n");
    } else {
      printf("no\n");
    }
  }

  return 0;
}

/* returns the next non-space character, EOF if not found */
static int next_token(void)
{
  int c;
  
  /* isspace() probably filters too much, but should be okay here */
  while ((c = getchar()) != EOF && isspace(c))
    ;
  return c;
}

/* determines if there is a root-to-leaf path with the specified sum */
/* if top_level, we don't accept empty trees.                        */
static int exist_sum(int sum, int top_level, int *empty)
{
  int val;        /* value of node */
  int t;
  int c;
  int result, result1, result2;
  int empty1, empty2;

  c = next_token();
  assert(c == '(');

  /* check for empty tree */
  c = getchar();
  assert(c != EOF);
  if (c == ')') {
    /* empty tree */
    if (empty) {
      *empty = 1;
    }
    if (top_level) {
      return 0;
    } else {
      return (sum == 0);
    }
  }

  /* non-empty node, check children */
  t = ungetc(c, stdin);
  assert(t != EOF);
  t = scanf("%d", &val);
  assert(t == 1);

  /* only need to test subtrees for sum - val */
  result1 = exist_sum(sum - val, 0, &empty1);
  result2 = exist_sum(sum - val, 0, &empty2);

  /* consume ending ) */
  c = next_token();
  assert(c == ')');

  if (empty1 && empty2) {
    /* both child are empty */
    assert(result1 == result2);
    result = result1;
  } else if (empty1 && !empty2) {
    /* not a leaf node, only take result1 */
    result = result2;
  } else if (!empty1 && empty2) {
    result = result1;
  } else {
    result = (result1 || result2);
  }

  if (empty) {
    *empty = 0;
  }
  return result;
}

