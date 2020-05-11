#include <stdio.h>
#include <string.h>
#include <assert.h>


typedef struct {
  int rows, cols;
} Dim;

typedef struct {
  int ops;
  Dim d;
} Data;

int n;
Dim dim[256];

void parse(char *expr, int len, Data *result)
{
  Data left, right;
  if (len == 1) {
    result->d.rows = dim[*expr].rows;
    result->d.cols = dim[*expr].cols;
    result->ops = 0;
    return;
  }

  assert(expr[0] == '(' && expr[len-1] == ')');
  if (expr[1] != '(') {
    parse(expr+1, 1, &left);
    parse(expr+2, len-3, &right);
  } else {
    int level = 1;
    int k;
    for (k = 2; level && k < len; k++) {
      if (expr[k] == '(') level++;
      if (expr[k] == ')') level--;
    }
    parse(expr+1, k-1, &left);
    parse(expr+k, len-1-k, &right);
  }

  if (left.ops >= 0 && right.ops >= 0 && left.d.cols == right.d.rows) {
    result->d.rows = left.d.rows;
    result->d.cols = right.d.cols;
    result->ops = left.ops + right.ops +
      left.d.rows * left.d.cols * right.d.cols;
  } else {
    result->ops = -1;
  }
}

int main(void)
{
  int i;
  char c;
  int rows, cols;
  char expr[1024];
  Data result;

  scanf("%d\n", &n);
  
  for (i = 0; i < n; i++) {
    scanf("%c %d %d\n", &c, &rows, &cols);
    dim[c].rows = rows;
    dim[c].cols = cols;
  }
  
  while (scanf("%s", expr) == 1) {
    parse(expr, strlen(expr), &result);
    if (result.ops < 0) {
      printf("error\n");
    } else {
      printf("%d\n", result.ops);
    }
  }
  return 0;
}
