#include <stdio.h>

int main(void)
{
  int H, U, D, F;
  int curr, climb, dec;
  int day;

  while (scanf("%d %d %d %d", &H, &U, &D, &F) == 4 && H) {
    climb = U * 100;
    dec = U * F;
    curr = 0;
    for (day = 1; 1; day++) {
      curr += climb;
      if (curr > H * 100) {
	printf("success on day %d\n", day);
	break;
      }
      curr -= D * 100;
      if (curr < 0) {
	printf("failure on day %d\n", day);
	break;
      }
      climb -= dec;
      if (climb < 0) {
	climb = 0;
      }
    }
  }

  return 0;
}
