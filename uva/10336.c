#include <stdio.h>
#include <stdlib.h>

void mark(char **map, int H, int W, int r, int c, int ch)
{

  map[r][c] = ' ';
  if (r > 0 && map[r-1][c] == ch) {
    mark(map, H, W, r-1, c, ch);
  }
  if (r < H-1 && map[r+1][c] == ch) {
    mark(map, H, W, r+1, c, ch);
  }
  if (c > 0 && map[r][c-1] == ch) {
    mark(map, H, W, r, c-1, ch);
  }
  if (c < W-1 && map[r][c+1] == ch) {
    mark(map, H, W, r, c+1, ch);
  }
}

typedef struct {
  char state;
  int freq;
} Data;

int cmp(const void *a, const void *b)
{
  Data *x = (Data *)a, *y = (Data *)b;

  if (x->freq != y->freq) {
    return y->freq - x->freq;
  } else {
    return x->state - y->state;
  }
}

int main(void)
{
  int N;
  int H, W;
  int world, i, r, c;
  char **map;
  int count[26];
  Data data[26];
  int num_data;


  scanf("%d", &N);
  for (world = 1; world <= N; world++) {
    scanf("%d %d\n", &H, &W);
    map = malloc(H*sizeof(*map));
    for (r = 0; r < H; r++) {
      map[r] = malloc(W+1);
      scanf("%s", map[r]);
    }
    
    for (i = 0; i < 26; i++) {
      count[i] = 0;
    }

    for (r = 0; r < H; r++) {
      for (c = 0; c < W; c++) {
	if (map[r][c] == ' ') continue;
	count[map[r][c]-'a']++;
	mark(map, H, W, r, c, map[r][c]);
      }
    }

    num_data = 0;
    for (i = 0; i < 26; i++) {
      if (count[i]) {
	data[num_data].state = i;
	data[num_data++].freq = count[i];
      }
    }

    qsort(data, num_data, sizeof(*data), cmp);
    
    printf("World #%d\n", world);
    for (i = 0; i < num_data; i++) {
      printf("%c: %d\n", (char)(data[i].state+'a'), data[i].freq);
    }

    for (r = 0; r < H; r++) {
      free(map[r]);
    }
    free(map);
  }
  return 0;
}
  
