/* @JUDGE_ID: 1102NT 376 C "" */

#include <stdio.h>
#include <math.h>

#define EPS 1e-8

double round(double x)
{
  return  floor(x * 100 + 0.5)/100;
}

int main(void)
{
  double A, B, C[2], theta, theta2, theta3, tmp;
  double pi = atan(1)*4;
  int case_num = 1, num;
  int i;

  printf("Case    A      B    THETA  # of    Side   Side\n");
  printf(" #     side   side  (deg)  Triags    1      2\n");
  while (scanf("%lf %lf %lf", &A, &B, &theta) == 3 &&
	 (fabs(A) > EPS || fabs(B) > EPS || fabs(theta) > EPS)) {
    printf("%4d%7.2f%7.2f%7.2f", case_num++, A, B, theta);
    theta *= pi/180.0;
    theta2 = asin(A*sin(theta)/B);
    if (theta2 < 0) {         
      /* tricky: there can be input with theta = 0 */
      /* we are supposed to consider these as "triangles"... */
      printf("%6d\n", 0);     /* no solution */
      continue;
    }

    num = 0;
    theta3 = pi - theta - theta2;
    if (theta3 >= 0) {
      tmp = A*A + B*B - 2*A*B*cos(theta3);
      if (tmp > 0) {
	C[num++] = sqrt(tmp);
      }
    }
    theta2 = pi - theta2;
    theta3 = pi - theta - theta2;
    if (theta3 >= 0) {
      tmp = A*A + B*B - 2*A*B*cos(theta3);
      if (tmp > 0) {
	if (num == 0 || fabs(round(sqrt(tmp)) - round(C[0])) > EPS) {
	  C[num++] = sqrt(tmp);
	}
      }
    }
    if (num == 2 && C[0] < C[1]) {
      tmp = C[0];
      C[0] = C[1];
      C[1] = tmp;
    }

    printf("%6d", num);
    if (num) {
      printf("  ");
    }
    for (i = 0; i < num; i++) {
      printf("%7.2f", C[i]);
    }
    printf("\n");
  }

  printf("\nEND OF REPORT for %d cases\n", case_num-1);
  return 0;
}
