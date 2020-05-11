#include <stdio.h>

typedef struct {
  unsigned long long value;
  char *name;
} Bangla;

Bangla bangla[4] = {
  { 10000000, "kuti"  },
  { 100000,   "lakh"  },
  { 1000,     "hajar" },
  { 100,      "shata" }
};

void translate(unsigned long long n, char last)
{
  int i;

  if (n == 0 && last == '\n') {
    printf(" %lld%c", n, last);
    return;
  }

  if (n >= bangla[0].value) {
    translate(n / bangla[0].value, ' ');
    printf("%s", bangla[0].name);
    n %= bangla[0].value;
  }

  for (i = 1; i < 4; i++) {
    if (n >= bangla[i].value) {
      printf("% lld %s", n / bangla[i].value, bangla[i].name);
      n %= bangla[i].value;
    }
  }
  
  if (n) {
    printf(" %lld%c", n, last);
  } else {
    printf("%c", last);
  }
}

int main(void)
{
  int case_num = 0;
  unsigned long long n;

  while (scanf("%llu", &n) == 1) {
    printf("%4d.", ++case_num);
    
    translate(n, '\n');
  }

  return 0;
}
