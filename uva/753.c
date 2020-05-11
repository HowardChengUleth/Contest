/* @JUDGE_ID: 1102NT 753 C "" */

/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_TYPES 400
#define MAX_TYPE_LEN 24
#define MAX_DEVS  100
#define MAX_DEV_LEN 24
#define MAX_ADAPTER 100
#define MAX_NODES MAX_TYPES+MAX_DEVS+2
#define SOURCE 0
#define SINK 1
#define NODES (n+num_dev+2)
#define PLUG(x) ((x)+2)
#define DEV(x) ((x)+n+2)

#define NDEBUG

char type[MAX_TYPES][MAX_TYPE_LEN+1];
char dev[MAX_DEVS][MAX_DEV_LEN+1];
int dev_plug[MAX_DEVS];
char adapter[MAX_TYPES][MAX_TYPES];
char graph[MAX_NODES][MAX_NODES];

int num_type, n, num_dev;

int search_type(char *s)
{
  int i;
  for (i = 0; i < num_type; i++) {
    if (!strcmp(s, type[i])) {
      return i;
    }
  }

  /* not found, insert it */
  strcpy(type[num_type++], s);
  return num_type-1;
}

void read_case(void)
{
  char buf1[MAX_TYPE_LEN+1], buf2[MAX_TYPE_LEN+1];
  int num_adapter, i, j, k, t;

  for (i = 0; i < MAX_TYPES; i++) {
    type[i][0] = 0;
  }
  for (i = 0; i < MAX_TYPES; i++) {
    for (j = 0; j < MAX_TYPES; j++) {
      adapter[i][j] = (i == j) ? 1 : 0;
    }
  }

  t = scanf("%d", &n);
  assert(t == 1 && 1 <= n && n <= MAX_TYPES);
  num_type = n;
  for (i = 0; i < num_type; i++) {
    t == scanf("%s", type[i]);
    assert(t == 1 && strlen(type[i]) <= MAX_TYPE_LEN);
  }
  t = scanf("%d", &num_dev);
  assert(t == 1 && 1 <= num_dev && num_dev <= MAX_DEVS);
  for (i = 0; i < num_dev; i++) {
    t = scanf("%s %s", dev[i], buf1);
    assert(t == 2 && strlen(dev[i]) <= MAX_DEV_LEN && 
	   strlen(buf1) <= MAX_TYPE_LEN);
    for (j = 0; j < i; j++) {
      assert(strcmp(dev[i], dev[j]));
    }
    dev_plug[i] = search_type(buf1);
    assert(0 <= dev_plug[i] && dev_plug[i] < num_type);
  }
  
  t = scanf("%d", &num_adapter);
  assert(t == 1 && 1 <= num_adapter && num_adapter <= MAX_ADAPTER);
  for (i = 0; i < num_adapter; i++) {
    t = scanf("%s %s", buf1, buf2);
    assert(t == 2 && strlen(buf1) <= MAX_TYPE_LEN && 
	   strlen(buf2) <= MAX_TYPE_LEN);
    j = search_type(buf2);
    k = search_type(buf1);
    assert(0 <= j && j <= num_type && 0 <= k && k <= num_type);
    adapter[j][k] = 1;
  }
}

void trans_closure(void)
{
  int i, j, k;

  for (k = 0; k < num_type; k++) {
    for (i = 0; i < num_type; i++) {
      for (j = 0; j < num_type; j++) {
	adapter[i][j] |= (adapter[i][k] && adapter[k][j]);
      }
    }
  }

#ifndef NDEBUG
  printf("Adapters:\n\n");
  for (i = 0; i < num_type; i++) {
    printf("%s =>", type[i]);
    for (j = 0; j < num_type; j++) {
      if (adapter[i][j] && i != j) {
	printf(" %s", type[j]);
      }
    }
    printf("\n");
  }
  printf("\n");
#endif

}

void build_graph(void)
{
  int i, j;

  /* clear */
  for (i = 0; i < NODES; i++) {
    for (j = 0; j < NODES; j++) {
      graph[i][j] = 0;
    }
  }

  for (i = 0; i < n; i++) {
    graph[SOURCE][PLUG(i)] = 1;
  }
  for (i = 0; i < num_dev; i++) {
    graph[DEV(i)][SINK] = 1;
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < num_dev; j++) {
      graph[PLUG(i)][DEV(j)] = adapter[i][dev_plug[j]];
    }
  }

#ifndef NDEBUG
  printf("Graph:\n\n");
  for (i = 0; i < n; i++) {
    printf("%s <=", type[i]);
    for (j = 0; j < num_dev; j++) {
      if (graph[PLUG(i)][DEV(j)]) {
	printf(" %s", dev[j]);
      }
    }
    printf("\n");
  }
  printf("\n");
#endif
}

int find_path(int v, int pos, int *path, int *used)
{
  int w;

  path[pos] = v;
  used[v] = 1;
  if (v == SINK) {
    return 1;
  }

  for (w = 0; w < NODES; w++) {
    if (graph[v][w] && !used[w] && find_path(w, pos+1, path, used)) {
      return 1;
    }
  }

  return 0;
}

void push_path(int *path)
{
  int i;
  for (i = 0; path[i] != SINK; i++) {
    graph[path[i]][path[i+1]] = 0;
    graph[path[i+1]][path[i]] = 1;
  }
}

void solve_case(void)
{
  int flow = 0;
  int path[MAX_NODES], used[MAX_NODES];
  int i, j, c;

  for (i = 0; i < NODES; i++) {
    used[i] = 0;
  }
  while (find_path(SOURCE, 0, path, used)) {
    push_path(path);
    flow++;
    for (i = 0; i < NODES; i++) {
      used[i] = 0;
    }
  }
  assert(flow <= n && flow <= num_dev);
  printf("%d\n", num_dev - flow);
  for (i = 0; i < num_dev; i++) {
    c = 0;
    for (j = 0; j < n; j++) {
      if (graph[DEV(i)][PLUG(j)]) {
#ifndef NDEBUG
	printf("%s => %s\n", dev[i], type[j]);
#endif
	c++;
	assert(c == 1);
      }
    }
  }
}

void solve(void)
{
  read_case();
  trans_closure();
  build_graph();
  solve_case();
}

int main(void)
{
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    solve();
    if (cases > 0) {
      printf("\n");
    }
  }
  return 0;
}
