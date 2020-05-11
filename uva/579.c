#include <stdio.h>

int main(void)
{
  int H, M;
  double angh, angm;
  double diff;

  while (scanf("%d:%d", &H, &M) == 2 && (H || M)) {
    angm = (double)M / 60 * 360.0;
    angh = (double)(H*60+M) / (12*60) * 360.0;
    diff = angh - angm;
    if (diff < 0) {
      diff = -diff;
    }
    if (diff > 180.0) {
      diff = 360.0 - diff;
    }
    printf("%.3f\n", diff);
  }
  return 0;
}
