/* @JUDGE_ID: 1102NT 107 C "Straight calculation" */

#include <stdio.h>
#include <assert.h>

void process(int init_h, int work);

int main(void)
{
  int init_h, work;

  scanf("%d %d", &init_h, &work);
  while (init_h != 0 || work != 0) {
    process(init_h, work);
    scanf("%d %d", &init_h, &work);
  }
  return 0;
}

void process(int init_h, int work)
{
  int total_h;
  int total_num = 0;
  int num_cat;
  int curr_h;
  int n, N = 0;

  /* find N */
  for (n = 1; n < init_h && N == 0; n++) {
    num_cat = 1;
    curr_h = init_h;
    while (curr_h > 1) {
      curr_h /= (n + 1);
      num_cat *= n;
    }
    if (curr_h == 1 && num_cat == work) {
      N = n;
    }
  }
  assert ((N == 0 && init_h == 1) || N > 0);
  curr_h = init_h;
  num_cat = 1;
  total_h = (init_h > 1) ? work : 1;
  while (curr_h != 1) {
    total_num += num_cat;
    total_h += num_cat * curr_h;
    num_cat *= N;
    curr_h /= (N+1);
  }

  printf("%d %d\n", total_num, total_h);
}
