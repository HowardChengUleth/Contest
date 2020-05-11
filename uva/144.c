/* @JUDGE_ID: 1102NT 144 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
  int n;
  int *elem;
  int head, tail;
} Queue;

int N, k;

void init_queue(Queue *q, int n)
{
  n++;                                /* one bigger than necessary */
  q->elem = malloc(n * sizeof(*(q->elem)));
  assert(q->elem);
  q->n = n;
  q->head = q->tail = 0;
}

void free_queue(Queue *q)
{
  free(q->elem);
  q->elem = 0;
  q->n = 0;
  q->head = q->tail = 0;
}

int empty_queue(Queue *q)
{
  return (q->head == q->tail);
}

int add_tail(Queue *q, int item)
{
  int new_tail = (q->tail + 1) % (q->n);
  if (new_tail == q->head) {
    fprintf(stderr, "Queue full: cannot add\n");
    return 0;
  } else {
    q->elem[q->tail] = item;
    q->tail = new_tail;
    return 1;
  }
}

int remove_head(Queue *q)
{
  int item;
  if (empty_queue(q)) {
    fprintf(stderr, "Queue empty: cannot delete\n");
    assert(0);
  }
  item = q->elem[q->head];
  q->head = (q->head + 1) % (q->n);
  return item;
}


void do_case(void)
{
  Queue queue;
  int store = 0;
  int i, curr_k;
  int card[30], payout;


  init_queue(&queue, N);

  for (i = 0; i < N; i++) {
    card[i] = 40;
    add_tail(&queue, i);
  }
  curr_k = 1;

  while (!empty_queue(&queue)) {
    if (!store) {
      /* get money */
      store += curr_k;
      if (++curr_k > k) {
	curr_k = 1;
      }
    }
    i = remove_head(&queue);
    payout = (card[i] < store) ? card[i] : store;
    card[i] -= payout;
    store -= payout;
    if (card[i] > 0) {
      add_tail(&queue, i);
    } else {
      printf("%3d", i+1);
    }
  }
  printf("\n");
  
  free_queue(&queue);
}

int main(void)
{
  while (scanf("%d %d", &N, &k) == 2 && (N || k)) {
    do_case();
  }

  return 0;
}
