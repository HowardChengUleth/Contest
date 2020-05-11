/* @JUDGE_ID: 1102NT 10701 C "" */

#include <stdio.h>
#include <string.h>
#include <assert.h>

char pre[53], in[53], post[53];

void do_case(int pre_0, int in_0, int post_0, int n)
{
  int i, n1, n2;
  int index;

  if (n > 1) {
    index = strchr(in, pre[pre_0]) - in;
    n1 = index - in_0;
    n2 = in_0 + n - 1 - index;
    assert(n1 + n2 + 1 == n);
    if (n1 > 0) {
      do_case(pre_0+1, in_0, post_0, n1);
    }
    if (n2 > 0) {
      do_case(pre_0+1+n1, index+1, post_0+n1, n2);
    }
  }
  post[post_0+n-1] = pre[pre_0];
}

int main(void)
{
  int C;
  scanf("%d", &C);
  while (C-- > 0) {
    scanf("%*d %s %s", pre, in);
    do_case(0, 0, 0, strlen(pre));
    post[strlen(pre)] = 0;
    printf("%s\n", post);
  }
  return 0;
}
