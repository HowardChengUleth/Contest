#include <stdio.h>
#include <math.h>

int main(void)
{
  int N;
  double R, r, I, E;
  double pi = acos(-1.0);
  double alpha;

  while (scanf("%lf %d", &R, &N) == 2) {
    if (N == 1) {
      r = R;  
      I = E = 0.0;
    } else if (N == 2) {
      r = R/2.0;  
      I = 0.0;  
      E = pi*(R*R - 2*r*r);
    } else {
      /*
	draw the regular n-gon whose vertices are the centres of
	the smaller circles. 
      */
      alpha = pi*(N-2)/N;          /* interior angle in n-gon */
      
      /*
	Each triangular slice connecting two consecutive centres of
	the small circle and the centre of the large circle is an
	isoscoles triangle with sides R-2r, R-2r, and 2r.

	The triangular slice connecting the center of the large circle
	and the points at which two consecutive smaller circles touch
	the larger circle is similar to the slice above, and has sides
	R, R, and 2*R*sin(pi/n).
      */
      r = sin(pi/N)*R/(1 + sin(pi/N));
      
      I = (sqrt((R-r)*(R-r) - r*r) * r     /* area of the triangle */
	   - r*r*alpha/2)                  /* area of the smaller circles
					      inside the slice */
	* N;
      E = pi*R*R - N*pi*r*r - I;
    }
    
    printf("%.10f %.10f %.10f\n", r, I, E);
  }

  return 0;
}
