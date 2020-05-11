#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

bool solve()
{
  int S, B;
  scanf("%d%d", &S, &B);
  if (!S && !B) return false;

  int left[100001], right[100001];
  for (int i = 1; i <= S; i++) {
    left[i] = i-1;
    right[i] = i+1;
  }
  left[1] = -1;
  right[S] = -1;
  
  while (B-- > 0) {
    int L, R;
    scanf("%d%d", &L, &R);
    if (left[L] >= 1) {
      right[left[L]] = right[R];
      printf("%d", left[L]);
    } else {
      putchar('*');
    }

    putchar(' ');
    if (right[R] >= 1) {
      left[right[R]] = left[L];
      printf("%d", right[R]);
    } else {
      putchar('*');
    }
    printf("\n");
  }

  printf("-\n");

  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
