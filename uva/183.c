#include <stdio.h>
#include <ctype.h>

void eatwhite(void)
{
  int c;

  while ((c = getchar()) != EOF && isspace(c))
    ;
  if (c != EOF) {
    ungetc(c, stdin);
  }
}

void output(char c, int *curr_col)
{
  putchar(c);
  if (++(*curr_col) >= 50) {
    putchar('\n');
    *curr_col = 0;
  }
}

void compress(char bitmap[200][200], int top, int left, int rows, int cols,
	      int *curr_col)
{
  int same = 1;
  int i, j;
  int rows2, cols2;

  if (!rows || !cols) return;
  for (i = 0; i < rows && same; i++) {
    for (j = 0; j < cols && same; j++) {
      if (bitmap[top+i][left+j] != bitmap[top][left]) {
	same = 0;
      }
    }
  }
  if (same) {
    output(bitmap[top][left], curr_col);
    return;
  }

  rows2 = (rows+1)/2;
  cols2 = (cols+1)/2;
  output('D', curr_col);
  compress(bitmap, top, left, rows2, cols2, curr_col);
  compress(bitmap, top, left+cols2, rows2, cols-cols2, curr_col);
  compress(bitmap, top+rows2, left, rows-rows2, cols2, curr_col);
  compress(bitmap, top+rows2, left+cols2, rows-rows2, cols-cols2, curr_col);
}

void decompress(char bitmap[200][200], int top, int left, int rows, int cols)
{
  char c;
  int i, j;
  int rows2, cols2;

  if (!rows || !cols) return;
  eatwhite();
  scanf("%c\n", &c);
  if (c == '0' || c == '1') {
    for (i = 0; i < rows; i++) {
      for (j = 0; j < cols; j++) {
	bitmap[top+i][left+j] = c;
      }
    }
    return;
  }
  rows2 = (rows+1)/2;
  cols2 = (cols+1)/2;
  decompress(bitmap, top, left, rows2, cols2);
  decompress(bitmap, top, left+cols2, rows2, cols-cols2);
  decompress(bitmap, top+rows2, left, rows-rows2, cols2);
  decompress(bitmap, top+rows2, left+cols2, rows-rows2, cols-cols2);
}

void do_compress(int rows, int cols)
{
  char bitmap[200][200];
  int i, j;
  int curr_col = 0;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      eatwhite();
      scanf("%c\n", bitmap[i]+j);
    }
  }
  
  printf("D%4d%4d\n", rows, cols);
  compress(bitmap, 0, 0, rows, cols, &curr_col);
  if (curr_col) {
    printf("\n");
  }
}

void do_decompress(int rows, int cols)
{
  char bitmap[200][200];
  int i, j;
  int curr_col = 0;

  printf("B%4d%4d\n", rows, cols);
  decompress(bitmap, 0, 0, rows, cols);

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      output(bitmap[i][j], &curr_col);
    }
  }
  
  if (curr_col) {
    printf("\n");
  }
}

int main(void)
{
  char type;
  int rows, cols;

  while (scanf("%c", &type) == 1 && type != '#') {
    scanf("%d %d", &rows, &cols);
    if (type == 'B') {
      do_compress(rows, cols);
    } else {
      do_decompress(rows, cols);
    }
  }

  return 0;
}
