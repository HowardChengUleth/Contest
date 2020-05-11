#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

/* Whee, tropical determinants, everybody loves 'em. 
   No reason not to use the 2^n solution here, though. */

int main() {
  int minor[256];
  int a[8][8];
  uint16_t m, sm;
  int nc, n, i, j, me, min;
  
  scanf("%d", &nc);
  for(; nc>0; --nc) {
    scanf("%d", &n);
    for(i=0; i<n; i++)
      for(j=0; j<n; j++)
        scanf("%d", &a[i][j]);
    
    minor[0u] = 0;
    for(m=1u; m<1u<<n; m++) {
      i=-1;
      for(sm=1u<<(n-1); sm; sm>>=1)
        if(m&sm) i++; 
      min = (-1u>>1); 
      for(sm=1u<<(n-1), j=n-1; sm; sm>>=1, j--) 
        if (m&sm) {
          me = a[i][j] + minor[m&~sm];
          if (me < min) min = me;
        }
      minor[m] = min;
    }
    
    printf("%d\n", minor[(1u<<n)-1]);
  }

  return 0;
}
