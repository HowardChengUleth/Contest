/* @JUDGE_ID: 1102NT 301 C++ "" */

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NUM   8
#define MAX_ORDER 22

typedef struct {
  int start;
  int dest;
  int passengers;
  int profit;
  int profit_to_come;
} Order;

FILE *in, *out;
Order order[MAX_ORDER];
int capacity, B_index, num_order;

int order_cmp(const void *a, const void *b)
{
  Order o1 = *((Order *)a);
  Order o2 = *((Order *)b);

  if (o1.passengers == o2.passengers) {
    return o2.profit - o1.profit;
  } else {
    return o2.passengers - o1.passengers;
  }
}

void calc_profit(int index, char *selected, int *leaving, int profit_so_far, 
		 int &best)
{
  int new_leaving[MAX_NUM];
  int i, max_profit;
  int flag;

  if (index >= num_order) {
    if (profit_so_far > best) {
      best = profit_so_far;
    }
    return;
  }

  /* try not adding this order */
  max_profit = order[index].profit_to_come + profit_so_far;
  if (max_profit > best) {
    for (i = 0; i <= B_index; i++) {
      new_leaving[i] = leaving[i];
    }
    calc_profit(index+1, selected, new_leaving, profit_so_far, best);
  }

  /* try adding this order */
  max_profit += order[index].profit;
  flag = 1;
  for (i = 0; i <= B_index; i++) {
    if (order[index].start <= i && i < order[index].dest) {
      new_leaving[i] = leaving[i] + order[index].passengers;
      if (new_leaving[i] > capacity) {
	flag = 0;
      }
    } else {
      new_leaving[i] = leaving[i];
    }
  }
  if (max_profit > best && flag) {
    selected[index] = 1;
    calc_profit(index+1, selected, new_leaving, 
		profit_so_far + order[index].profit, best);
    selected[index] = 0;
  }
}

int main(void)
{
  int i;
  int best;
  char selected[MAX_ORDER];
  int leaving[MAX_NUM];  /* number of people leaving station i on the train */

  in = stdin;
  out = stdout;
  fscanf(in, "%d %d %d", &capacity, &B_index, &num_order);
  while (capacity || B_index || num_order) {
    assert(0 < B_index && B_index <= MAX_NUM-1);
    assert(0 <= num_order && num_order <= MAX_ORDER);
    for (i = 0; i < num_order; i++) {
      fscanf(in, "%d %d %d", &order[i].start, &order[i].dest, 
	     &order[i].passengers);
      order[i].profit = order[i].passengers * (order[i].dest - order[i].start);
    }
    if (num_order == 0) {
      best = 0;
    } else {
      qsort(order, num_order, sizeof(Order), order_cmp);
      order[num_order-1].profit_to_come = 0;
      for (i = num_order-2; i >= 0; i--) {
	order[i].profit_to_come = order[i+1].profit_to_come + order[i+1].profit;
      }
      
      /* initialize best with last order, fewest passengers */
      best = order[num_order-1].profit;
      if (order[num_order-1].passengers > capacity) {
	/* no other order can be satisfied. */
	best = 0;
      } else {
	for (i = 0; i < num_order; i++) {
	  selected[i] = 0;
	}
	for (i = 0; i <= B_index; i++) {
	  leaving[i] = 0;
	}
	calc_profit(0, selected, leaving, 0, best);
      }
    }
    fprintf(out, "%d\n", best);
    fscanf(in, "%d %d %d", &capacity, &B_index, &num_order);
  }

  return 0;
}
