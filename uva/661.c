#include <stdio.h>

int do_case(int num)
{
  int n, m, c;
  int cons[20];
  int state[20];

  int i;
  int max_cons;
  int curr_cons;
  int d;

  scanf("%d %d %d", &n, &m, &c);
  if (!n && !m && !c) {
    return 0;
  }
  for (i = 0; i < n; i++) {
    scanf("%d", cons+i);
    state[i] = 0;
  }

  max_cons = curr_cons = 0;
  for (i = 0; i < m; i++) {
    scanf("%d", &d);
    d--;
    if (state[d]) {
      state[d] = 0;
      curr_cons -= cons[d];
    } else {
      state[d] = 1;
      curr_cons += cons[d];
      if (curr_cons > max_cons) {
	max_cons = curr_cons;
      }
    }
  }
  printf("Sequence %d\n", num);
  if (max_cons > c) {
    printf("Fuse was blown.\n");
  } else {
    printf("Fuse was not blown.\n");
    printf("Maximal power consumption was %d amperes.\n", max_cons);
  }
  printf("\n");

  return 1;
}

int main(void)
{
  int num = 1;

  while (do_case(num++))
    ;

  return 0;
}
