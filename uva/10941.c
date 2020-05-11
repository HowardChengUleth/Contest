#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_K 1000
#define MAX_LEN 2000

typedef struct {
  char *s;
  int d;
} BFSnode;

char x[MAX_LEN+1], y[MAX_LEN+1];
int k;
char word[MAX_K][MAX_LEN+1];
int w_len[MAX_K];
char *set[MAX_LEN+1][MAX_K+2];
int set_n[MAX_LEN+1];
  
/* use whatever element type as necessary                       */
/* assume that ELEMTYPE has proper assignment operation defined */
#define ELEMTYPE BFSnode

typedef struct {
  int n;
  ELEMTYPE *elem;
  int head, tail;
} Queue;

void init_queue(Queue *q, int n)
{
  int i;
  n++;                                /* one bigger than necessary */
  q->elem = malloc(n * sizeof(*(q->elem)));
  assert(q->elem);
  for (i = 0; i < n; i++) {
    q->elem->s = 0;
  }
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

int add_tail(Queue *q, ELEMTYPE item)
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

int add_head(Queue *q, ELEMTYPE item)
{
  int new_head = q->head - 1;
  if (new_head < 0) {
    new_head += q->n;
  }
  if (new_head == q->tail) {
    fprintf(stderr, "Queue full: cannot add\n");
    return 0;
  } else {
    assert(!q->elem[new_head].s);
    q->elem[new_head] = item;
    q->head = new_head;
    return 1;
  }
}

ELEMTYPE remove_head(Queue *q)
{
  ELEMTYPE item;
  if (empty_queue(q)) {
    fprintf(stderr, "Queue empty: cannot delete\n");
    assert(0);
  }
  item = q->elem[q->head];
  q->head = (q->head + 1) % (q->n);
  return item;
}

ELEMTYPE remove_tail(Queue *q)
{
  int new_tail = q->tail - 1;
  if (empty_queue(q)) {
    fprintf(stderr, "Queue empty: cannot delete\n");
    assert(0);
  }
  if (new_tail < 0) {
    new_tail += q->n;
  }
  q->tail = new_tail;
  return q->elem[q->tail];
}

int num_in_queue(Queue *q)
{
  int res = q->tail - q->head;
  return (res >= 0) ? res : res + q->n;
}


void add_node(Queue *q, char *s, int len, int dist)
{
  BFSnode node;
  int i;

  for (i = 0; i < set_n[len]; i++) {
    if (!strcmp(s, set[len][i])) {
      return;
    }
  }

  node.s = strdup(s);
  /*
  printf("strdup = %p, \"%s\"\n", node.s, node.s);
  */
  node.d = dist;
  add_tail(q, node);

0 &&  printf("Adding \"%s\", d = %d\n", node.s, node.d);
  /* note: this is shallow copy, but we should be fine because we don't
     free it until we are all done */
  set[len][set_n[len]++] = node.s;
}

int solve(void)
{
  int nx = strlen(x), ny = strlen(y);
  int maxlen;
  int i, j, ans = -1;
  Queue queue;

0 &&  printf("x = %s\n", x);
0 &&  printf("y = %s\n", y);
0 &&  printf("nx = %d, ny = %d\n", nx, ny);
  
  /* first see if they have the same length */
  if (nx == ny) {
    return (!strcmp(x, y)) ? 0 : -1;
  }

  /* see if one is a substring of the other */
  if (ny < nx) {
    int t;
    char ct[MAX_LEN+1];
    
    t = nx; nx = ny; ny = t;
    strcpy(ct, x); strcpy(x, y); strcpy(y, ct);
  }
  if (strstr(y, x) != y) {
    return -1;
  }

  maxlen = ny;
  for (i = 0; i < k; i++) {
    if (w_len[i] > maxlen) {
      maxlen = w_len[i];
    }
  }

  /* now we start a BFS search on the part that "sticks out" */
  init_queue(&queue, (k+2)*(maxlen+1));
  for (i = 0; i <= maxlen; i++) {
    set_n[i] = 0;
  }
    
  add_node(&queue, y+nx, ny-nx, 0);


  while (!empty_queue(&queue)) {
    BFSnode u = remove_head(&queue);
    char *suffix = u.s;
    int suffix_len = strlen(suffix);

0 &&    printf("Examining \"%s\", d = %d\n", u.s, u.d);

    /* now look for a word that can be used for adjustment */
    for (i = 0; i < k; i++) {
      if (suffix_len == w_len[i] && !strcmp(suffix, word[i])) {
	/* we are done */
	ans = u.d+1;
	goto cleanup;
      }
      if (suffix_len < w_len[i] && strstr(word[i], suffix) == word[i]) {
	add_node(&queue, word[i]+suffix_len, w_len[i]-suffix_len, u.d+1);
      } else if (suffix_len > w_len[i] && strstr(suffix, word[i]) == suffix) {
	add_node(&queue, suffix+w_len[i], suffix_len-w_len[i], u.d+1);
      }
    }
  }

 cleanup:
  for (i = 0; i <= maxlen; i++) {
    for (j = 0; j < set_n[i]; j++) {
      /*
      printf("freeing %p\n", set[i][j]);
      */
      free(set[i][j]);
    }
  }
  free_queue(&queue);
  return ans;
}

int main(void)
{
  int cases;
  int i;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%s %s", x, y);
    scanf("%d", &k);
    for (i = 0; i < k; i++) {
      scanf("%s", word[i]);
      w_len[i] = strlen(word[i]);
    }
    printf("%d\n", solve());
  }
  return 0;
}
