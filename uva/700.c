#include <stdio.h>

int main(void)
{
  int n;
  int a[20], b[20], y[20];
  int yy[20];
  int u, i;
  int done;
  int case_num = 1;

  while (scanf("%d", &n) == 1 && n > 0) {
    u = 0;
    for (i = 0; i < n; i++) {
      scanf("%d %d %d", y+i, a+i, b+i);
      if (a[i] > u) {
	u = a[i];
      }
    }

    done = 1;
    for (i = 0; i < n; i++) {
      yy[i] = (u - a[i]) % (b[i] - a[i]) + a[i];
      done &= (yy[i] == y[i]);
    }

    while (!done) {
      u++;
      if (u >= 10000) break;
      done = 1;
      for (i = 0; i < n; i++) {
	if (++yy[i] >= b[i]) yy[i] = a[i];
	done &= (yy[i] == y[i]);
      }
    }

    printf("Case #%d:\n", case_num++);
    if (done) {
      printf("The actual year is %d.\n\n", u);
    } else {
      printf("Unknown bugs detected.\n\n");
    }
      

  }

  return 0;
}
