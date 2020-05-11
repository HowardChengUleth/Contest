#include <stdio.h>

int main(void)
{
  int ncows, ncars, nshow;
  int total;
  double p;
  while (scanf("%d %d %d", &ncows, &ncars, &nshow) == 3) {
    total = ncows + ncars;
    /* chose a cow first */
    p = (double)ncows/total * (double)ncars/(total - nshow - 1);
    
    /* chose a car first */
    p += (double)ncars/total * (double)(ncars-1)/(total - nshow - 1);
      
    printf("%.5f\n", p);
  }

  return 0;
}
