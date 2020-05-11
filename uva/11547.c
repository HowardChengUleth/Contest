#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
  int nc, n;
  
  scanf("%d", &nc);
  for(; nc>0; --nc) {
    scanf("%d", &n);
    n = (((n*567)/9+7492)*235)/47-498; 
    if (n<0) n = -n;
    printf("%d\n", (n/10)%10); 
  }
  
  return 0;
}
