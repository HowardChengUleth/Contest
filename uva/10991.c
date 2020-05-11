#include <stdio.h>
#include <math.h>

double heron(double s1, double s2, double s3)
{
  double s = (s1+s2+s3)/2;
  return sqrt(s*(s-s1)*(s-s2)*(s-s3));
}

double angle(double a, double b, double c)
{
  return acos((a*a+b*b-c*c)/(2*a*b));
}

int main(void)
{
  int K;
  double r1, r2, r3;
  double s1, s2, s3;
  double tri_area;

  scanf("%d", &K);
  while (K-- > 0) {
    scanf("%lf %lf %lf", &r1, &r2, &r3);
    s1 = r1+r2;
    s2 = r2+r3;
    s3 = r1+r3;
    tri_area = heron(s1, s2, s3);
    
    tri_area -= angle(s1, s3, s2)/2 * r1*r1;
    tri_area -= angle(s1, s2, s3)/2 * r2*r2;
    tri_area -= angle(s2, s3, s1)/2 * r3*r3;

    printf("%.6f\n", tri_area);
    
  }
  return 0;
}
