#include <stdio.h>
#include <math.h>

int main(void)
{
  int cases;
  int k;
  long long n, d;

  scanf("%d", &cases);
  while (cases-- > 0) {
    scanf("%d", &k);
    if (k < 0) {
      k = -k;
    }

    if (k == 0) {
      printf("3\n");       /* special case */
    } else {

      /* 1+2+...+n = n(n+1)/2 has to be at least k */
      n = ceil((-1 + sqrt(1 + 8.0*k))/2.0) + 0.5;
      
      /* we know that d1 = n(n+1)/2 - k <= n.  Suppose that
	 d1 is even.  Then d1/2 <= n/2, so
	 
	 n(n+1)/2 - k = 2*t    for some t <= n/2
	 or   n(n+1)/2 - 2*t = k
	 
	 so 1+2+...+(t-1)+t+(t+1)+...+n - 2*t = k
	 => 1+2+...+(t-1)-t+(t+1)+...+n = k
	 
	 so answer is n. 
	 
	 if d1 is odd, it is not possible to flip the signs to make the
	 equation hold.
	 
      */
      d = n*(n+1)/2 - k;
      if (d % 2 == 0) {
	printf("%lld\n", n);
      } else {
	/* now let d2 = (n+1)(n+2)/2 - k <= 2*n+1.  If d2 is even,
	   then d2/2 <= (2*n+1)/2 < n+1.  so
	   
	   (n+1)(n+2)/2 - k = 2*t     for some t <= n
	   
	   so 1+2+...+(t-1)+t+(t+1)+...+(n+1) - 2*t = k
	   
	   so answer is n+1.
	*/
	d = (n+1)*(n+2)/2 - k;
	if (d % 2 == 0) {
	  printf("%lld\n", n+1);
	} else {
	  /* in that case, let d3 = (n+2)(n+3)/2 - k.  A similar
	     argument shows that if d3 is odd even then n+2 is the
	     answer.  Note that if d1 and d2 are both odd, then
	     since d3 = d1 + (n+1) + (n+2) means that d3 must be even */
	  printf("%lld\n", n+2);
	}
      }
    }

    
    if (cases) {
      printf("\n");
    }
  }

  return 0;
}
