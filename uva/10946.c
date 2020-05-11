#include <stdio.h>
#include <stdlib.h>

char map[50][51];
int x, y;

typedef struct {
  char name;
  int size;
} Entry;
Entry entry[2500];
int n;

int read_case(void)
{
  int i;

  scanf("%d %d", &x, &y);
  if (!x && !y) {
    return 0;
  }
  
  for (i = 0; i < x; i++) {
    scanf("%s", map[i]);
  }
  n = 0;

  return 1;
}

int hole_size(int i, int j)
{
  char c = map[i][j];
  int ans = 1;

  map[i][j] = '.';
  if (i-1 >= 0 && map[i-1][j] == c) {
    ans += hole_size(i-1, j);
  }
  if (i+1 < x && map[i+1][j] == c) {
    ans += hole_size(i+1, j);
  }
  if (j-1 >= 0 && map[i][j-1] == c) {
    ans += hole_size(i, j-1);
  }
  if (j+1 < y && map[i][j+1] == c) {
    ans += hole_size(i, j+1);
  }
  return ans;
}

void find_holes(void)
{
  int i, j;

  for (i = 0; i < x; i++) {
    for (j = 0; j < y; j++) {
      if (map[i][j] != '.') {
	entry[n].name = map[i][j];
	entry[n++].size = hole_size(i, j);
      }
    }
  }
}

int cmp(const void *a, const void *b)
{
  Entry *aa = (Entry *)a, *bb = (Entry *)b;
  
  if (aa->size != bb->size) {
    return bb->size - aa->size;
  } else {
    return (int)aa->name - (int)bb->name;
  }
}

int main(void)
{
  int cases = 1;
  int i;

  while (read_case()) {
    printf("Problem %d:\n", cases++);
    find_holes();
    qsort(entry, n, sizeof(Entry), cmp);
    for (i = 0; i < n; i++) {
      printf("%c %d\n", entry[i].name, entry[i].size);
    }
  }
  return 0;
}
