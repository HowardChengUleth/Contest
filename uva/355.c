#include <stdio.h>
#include <ctype.h>

long long todec(char *num, int b)
{
  long long val = 0;
  int d;

  while (*num) {
    if (isdigit(*num)) {
      d = *num - '0';
    } else if (isupper(*num)) {
      d = *num - 'A' + 10;
    } else {
      return -1;
    }
    if (d >= b) {
      return -1;
    }
    val = val * b + d;
    num++;
  }
  return val;
}

void print_val(long long val, int b)
{
  if (!val) return;

  print_val(val/b, b);
  
  putchar((val%b < 10) ? val%b+'0' : val%b - 10 + 'A');
}

int main(void)
{
  char num[1000];
  int from, to;
  long long val;

  while (scanf("%d %d %s", &from, &to, num) == 3) {
    val = todec(num, from);
    if (val < 0) {
      printf("%s is an illegal base %d number\n", num, from);
    } else if (val == 0) {
      printf("%s base %d = 0 base %d\n", num, from, to);
    } else {
      printf("%s base %d = ", num, from);
      print_val(val, to);
      printf(" base %d\n", to);
    }
  }
  

  return 0;
}
