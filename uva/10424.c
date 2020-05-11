#include <stdio.h>
#include <ctype.h>

int convert(char *str)
{
  int sum = 0;

  while (*str) {
    if (isalpha(*str)) {
      sum += tolower(*str) - 'a' + 1;
    }
    str++;
  }
  return sum;
}

int sum(int n)
{
  int s;

  while (n >= 10) {
    s = 0;
    while (n) {
      s += n % 10;
      n /= 10;
    }
    n = s;
  }
  return n;
}

int main(void)
{
  char str1[27], str2[27];
  int val1, val2;
  
  while (fgets(str1, 27, stdin)) {
    fgets(str2, 27, stdin);
    val1 = sum(convert(str1));
    val2 = sum(convert(str2));
    if (val1 < val2) {
      printf("%.2f %%\n", val1*100.0/val2);
    } else {
      printf("%.2f %%\n", val2*100.0/val1);
    }
  }
  return 0;
}
