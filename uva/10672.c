/* @JUDGE_ID: 1102NT 10672 C "" */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
  int deg;
  int offset;       /* offset into children array */
  int marbles;
} Node;

#define MAX_N 10000

Node tree[MAX_N];
int children[MAX_N];
int N;

int read_case(void)
{
  int i, j, k, v;
  int child_count = 0;
  
  scanf("%d", &N);
  if (!N) {
    return 0;
  }

  for (i = 0; i < N; i++) {
    scanf("%d", &j);
    j--;
    scanf("%d %d", &tree[j].marbles, &tree[j].deg);
    tree[j].offset = child_count;
    for (k = 0; k < tree[j].deg; k++) {
      scanf("%d", &v);
      children[child_count++] = v-1;
    }
  }
      
  return 1;
}

void visit(int i, char *visited)
{
  int j, v;

  visited[i] = 1;
  for (j = 0; j < tree[i].deg; j++) {
    v = children[tree[i].offset + j];
    if (!visited[v]) {
      visit(v, visited);
    }
  }
}

int find_root(void)
{
  char visited[MAX_N];
  int i, j;

  for (i = 0; i < N; i++) {
    memset(visited, 0, N);
    visit(i, visited);
    for (j = 0; j < N; j++) {
      if (!visited[j]) {
	break;
      }
    }
    if (j >= N) {
      return i;
    }
  }
  assert(0);
  return -1;
}

int compute(int root, int *needed)
{
  int j, v, moved, count;

  count = 0;
  for (j = 0; j < tree[root].deg; j++) {
    v = children[tree[root].offset + j];
    count += compute(v, &moved);
    tree[root].marbles -= moved;
  }

  *needed = 1 - tree[root].marbles;
  return count+abs(*needed);
}

void solve_case(void)
{
  int count, root, dummy;

  root = find_root();
  count = compute(root, &dummy);

  printf("%d\n", count);
}

int main(void)
{
  while (read_case()) {
    solve_case();
  }

  return 0;
}
