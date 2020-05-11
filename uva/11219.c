#include <stdio.h>

typedef struct {
  int y, m, d;
} Date;

void read_date(Date *d)
{
  scanf("%d/%d/%d", &(d->d), &(d->m), &(d->y));
}

int years(Date *curr, Date *birth)
{
  if (curr->m < birth->m ||
      (curr->m == birth->m && curr->d < birth->d)) {
    curr->y--;
  }
  return curr->y - birth->y;
}

int main(void)
{
  int T;
  int N;
  Date curr, birth;
  int age;
  

  scanf("%d", &T);
  for (N = 1; N <= T; N++) {
    printf("Case #%d: ", N);
    read_date(&curr);
    read_date(&birth);
    age = years(&curr, &birth);
    if (age < 0) {
      printf("Invalid birth date\n");
    } else if (age > 130) {
      printf("Check birth date\n");
    } else {
      printf("%d\n", age);
    }
    
  }
  return 0;
}
