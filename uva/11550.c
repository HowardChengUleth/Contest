#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
  char inc[8][28];
  char adj[8][8];
  char ends[8];
  int nc, n, m, i, j, k, good;
  
  scanf("%d", &nc);
  for(; nc>0; --nc) {
    scanf("%d%d", &n, &m);
    for(i=0; i<n; i++)
      for(j=0; j<m; j++)
        scanf("%d", &inc[i][j]);
    memset(adj, 0, 8*8*sizeof(char));
    
    good = 1;
    for(j=0; j<m; j++) {
      k=0;
      for(i=0; i<n; i++)
        if(inc[i][j])
          ends[k++]=i;
      if ((k != 2) || adj[ends[0]][ends[1]]++) {
        good = 0;
        break;
      }
    }
    
    printf("%s\n", good ? "Yes" : "No");
  }

  return 0;
}
