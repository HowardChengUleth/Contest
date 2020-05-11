/* @JUDGE_ID: 1102NT 10160 C "" */

/*
 * This is dominating set and NP-hard.
 *
 * Idea: 
 *
 *   - for every vertex not yet dominated, I must choose either the
 *     vertex or one of its neighbours.
 *
 *   - try choosing each one in turn, recurse
 *
 *   - as soon as the current set so far >= best set so far, prune
 *
 *   - to avoid duplicated work, once we decided not to choose a vertex
 *     we remember this and never try to consider it again.
 *
 *     i.e. we don't want to decide to skip vertex v, recurse, and later
 *          on decide to choose v again.
 *
 *   - to minimize branching factor at the top, always choose a vertex
 *     that has minimum degree among all vertices not yet dominated.
 *
 *   - I'm using adjacency list, but I don't think it matters too much
 *     for this problem.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 35

typedef struct {
  int deg;
  int nbr[MAX_N];
} Node;

Node graph[MAX_N];
int N, M;
int best;

int read_graph(void)
{
  int i, u, v;

  scanf("%d %d", &N, &M);
  if (!N && !M) {
    return 0;
  }

  /* clear the graph */
  for (i = 0; i < N; i++) {
    graph[i].deg = 0;
  }

  /* read in each edge, store both directions */
  for (i = 0; i < M; i++) {
    scanf("%d %d", &u, &v);
    u--; v--;
    graph[u].nbr[graph[u].deg++] = v;
    graph[v].nbr[graph[v].deg++] = u;
  }

  return 1;
}

/* compute the new "cover" array, and return the number of newly covered
   vertices */
int do_select(int next_i, char *cover, char *cover2)
{
  int num = 0;
  int i, j;
  for (i = 0; i < graph[next_i].deg; i++) {
    j = graph[next_i].nbr[i];
    if (!cover[j]) {
      cover2[j] = 1;
      num++;
    }
  }
  if (!cover[next_i]) {
    cover2[next_i] = 1;
    num++;
  }
  return num;
}

void search(int covered, char *cover, char *considered, int so_far)
{
  int next_i;
  int i, j;
  char cover2[MAX_N];
  char considered2[MAX_N];
  int num = 0;

  if (covered == N) {
    /* everything is covered, done */
    if (so_far < best) {
      best = so_far;
    }
    return;
  }

  if (so_far + 1 >= best) {
    /* if it's not covered, we need at least one more vertex */
    return;
  }


  /* look for a vertex that is not covered and has the smallest degree */
  next_i = -1;
  for (i = 0; i < N; i++) {
    if (considered[i] || cover[i]) continue;
    if (next_i == -1 || graph[i].deg < graph[next_i].deg) {
      next_i = i;
    }
  }

  if (next_i == -1) {
    /* every vertex has been considered */
    return;
  }

  /* make a new copy */
  memcpy(cover2, cover, N);
  memcpy(considered2, considered, N);

  /* try covering next_i */
  num = do_select(next_i, cover, cover2);
  considered2[next_i] = 1;
  search(covered+num, cover2, considered2, so_far+1);

  /* now try covering each neighbour of next_i instead */
  for (i = 0; i < graph[next_i].deg; i++) {
    j = graph[next_i].nbr[i];
    if (considered2[j]) continue;
    memcpy(cover2, cover, N);
    num = do_select(j, cover, cover2);

    /* by setting considered2[j] = 1, we make sure that when we skip */
    /* this (next loop iteration) and recurse, we won't look at j    */
    /* again.                                                        */
    considered2[j] = 1;
    search(covered+num, cover2, considered2, so_far+1);
  }
}

int main(void)
{
  char cover[35], considered[35];

  while (read_graph()) {
    best = N;
    memset(cover, 0, N);
    memset(considered, 0, N);
    search(0, cover, considered, 0);
    printf("%d\n", best);
  }
  return 0;
}
