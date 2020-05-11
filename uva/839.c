/* @JUDGE_ID: 1102NT 839 C "" */


#include <stdio.h>

int balance(void)
{
  int wl, wr, dl, dr;

  scanf("%d %d %d %d", &wl, &dl, &wr, &dr);
  if (!wl) {
    wl = balance();
  }
  if (!wr) {
    wr = balance();
  }
  if (wl < 0 || wr < 0 || wl*dl != wr*dr) {
    return -1;
  } else {
    return wl + wr;
  }
}

int main(void)
{
  int cases;

  scanf("%d", &cases);
  while (cases-- > 0) {
    if (balance() >= 0) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }

    if (cases) {
      printf("\n");
    }
  }

  return 0;
}
