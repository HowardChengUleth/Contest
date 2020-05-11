#include <stdio.h>

/* there are 10^6 different configuration */
int best[1000000];

/* individual item can be considered a combo of 1 */
typedef struct {
  int items[6];      /* how many of each kind */
  int price;
} Item;

Item combo[14];
int num_combos;
int I;

int read_menu(void)
{
  int i, j;

  if (scanf("%d", &I) != 1) {
    return 0;
  }
  for (i = 0; i < I; i++) {
    for (j = 0; j < I; j++) {
      combo[i].items[j] = (i == j);
    }
    scanf("%d", &combo[i].price);
  }
  scanf("%d", &num_combos);
  for (i = 0; i < num_combos; i++) {
    for (j = 0; j < I; j++) {
      scanf("%d", &combo[i+I].items[j]);
    }
    scanf("%d", &combo[i+I].price);
  }

  return 1;
}

int toindex(int *orders)
{
  int i, a = 0;

  /* convert to a 1-D index, use base 10 arithmetic */
  for (i = 0; i < I; i++) {
    a = a*10 + orders[i];
  }
  return a;
}

int compute(int *order)
{
  int index = toindex(order);
  int good;
  int i, j;
  int temp;

  if (best[index] >= 0) {
    return best[index];
  }

  for (i = 0; i < I+num_combos; i++) {
    good = 1;
    for (j = 0; j < I && good; j++) {
      if (combo[i].items[j] > order[j]) {
	good = 0;
      }
    }
    if (!good) continue;

    for (j = 0; j < I; j++) {
      order[j] -= combo[i].items[j];
    }
    temp = compute(order) + combo[i].price;
    if (best[index] < 0 || temp < best[index]) {
      best[index] = temp;
    }

    /* restore order */
    for (j = 0; j < I; j++) {
      order[j] += combo[i].items[j];
    }
  }
  return best[index];
}

int main(void)
{
  int orders;
  int i;
  int order[6];

  while (read_menu()) {
    best[0] = 0;
    for (i = 1; i < 1000000; i++) {
      best[i] = -1;
    }
    scanf("%d", &orders);
    while (orders-- > 0) {
      for (i = 0; i < I; i++) {
	scanf("%d", order+i);
      }
      printf("%d\n", compute(order));
    }
  }
  return 0;
}
