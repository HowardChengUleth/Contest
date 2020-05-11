#include <stdio.h>

int fl[25], fr[25], bl[25], br[25];

void print_sheet(int num, char *label, int left, int right)
{
  if (left <= 0 && right <= 0) {
    return;
  }

  printf("Sheet %d, %s: ", num, label);
  if (left <= 0) {
    printf("Blank, ");
  } else {
    printf("%d, ", left);
  }
  if (right <= 0) {
    printf("Blank\n");
  } else {
    printf("%d\n", right);
  }

}

int main(void)
{
  int n;
  int sheets;
  int i;
  int page;

  while (scanf("%d", &n) == 1 && n) {
    sheets = (n+3)/4;
    for (i = 0; i < sheets; i++) {
      fl[i] = fr[i] = bl[i] = br[i] = -1;
    }
    
    page = 1;
    i = 0;
    for (i = 0; i < sheets; i++) {
      if (page <= n) fr[i] = page++;
      if (page <= n) bl[i] = page++;
    }
    for (i = sheets-1; i >= 0; i--) {
      if (page <= n) br[i] = page++;
      if (page <= n) fl[i] = page++;
    }
     
    printf("Printing order for %d pages:\n", n);
    for (i = 0; i < sheets; i++) {
      print_sheet(i+1, "front", fl[i], fr[i]);
      print_sheet(i+1, "back ", bl[i], br[i]);
    }
  }
  return 0;
}
