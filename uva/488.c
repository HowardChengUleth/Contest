#include <stdio.h>

int main(int argc, char *argv[]) {
  int cases = 0;
  int freq = 0;
  int height = 0;
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  
  scanf("%d", &cases);
  for (i = 1; i <= cases; i++) {
    scanf("%d\n%d", &height, &freq);
    
    for (j = 1; j <= freq; j++) {
      for (k = 1; k <= height; k++) {
	for (l = 1; l <= k; l++) {
	  printf("%d", k);
	}
	printf("\n");
      }
      for (k = height - 1; k > 0; k--) {
	for (l = k; l > 0; l--) {
	  printf("%d", k);
	}
	printf("\n");
      }
      if (j+1 <= freq) {
	printf("\n");
      }
    }

    if (1 || i+1 <= cases) {
      printf("\n");
    }
    
    
    freq = 0;
    height = 0;
  }

  
  return 0;
}
