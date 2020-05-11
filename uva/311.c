#include <stdio.h>

int main(void)
{
  int num[7];
  int i, done;
  int count, left;
  int t;

  while (1) {
    done = 1;
    for (i = 1; i <= 6; i++) {
      scanf("%d", num+i);
      if (num[i]) {
	done = 0;
      }
    }
    if (done) {
      return 0;
    }

    count = num[6];
    for (i = 0; i < num[5]; i++) {
      count++;
      if (num[1] > 0) {
	num[1] -= 11;
	if (num[1] < 0) {
	  num[1] = 0;
	}
      }
    }
    
    for (i = 0; i < num[4]; i++) {
      count++;
      left = 36 - 16;
      while (left >= 4 && num[2] > 0) {
	left -= 4;
	num[2]--;
      }
      while (left > 0 && num[1] > 0) {
	left--;
	num[1]--;
      }
    }

    while (num[3] > 0) {
      left = 36;
      count++;
      if (num[3] >= 4) {
	left = 0;
	num[3] -= 4;
      } else {
	left = 36 - num[3]*9;
	num[3] = 0;
      }
      if (left == 9 && num[2] > 0) {
	left -= 4;
	num[2]--;
      } else if (left == 18 && num[2] > 0) {
	t = (num[2] > 3) ? 3 : num[2];
	left -= 4*t;
	num[2] -= t;
      } else if (left == 27 && num[2] > 0) {
	t = (num[2] > 5) ? 5 : num[2];
	left -= 4*t;
	num[2] -= t;
      }
      while (left > 0 && num[1] > 0) {
	left--;
	num[1]--;
      }
    }
    
    while (num[2] > 0) {
      left = 36;
      count++;
      t = (num[2] > 9) ? 9 : num[2];
      left -= 4 * t;
      num[2] -= t;
      while (left > 0 && num[1] > 0) {
	left--;
	num[1]--;
      }
    }

    while (num[1] > 0) {
      t = (num[1] > 36) ? 36 : num[1];
      num[1] -= t;
      count++;
    }
    
    printf("%d\n", count);
  }
  return 0;
}
