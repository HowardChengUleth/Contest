#include <iostream>
#include <algorithm>

using namespace std;

int min3(int a, int b, int c)
{
  if (a <= b && a <= c) {
    return a;
  } else if (b <= a && b <= c) {
    return b;
  } else {
    return c;
  }
}

int main(void)
{
  int ugly[1500];
  int index2, index3, index5;
  
  ugly[0] = 1;

  // the next ugly number must be a previous ugly number * 2, 3, or 5.
  // index2 indicates that ugly[index2] is the smallest previous ugly
  // number such that ugly[index2] * 2 > last ugly number
  index2 = index3 = index5 = 0;

  // note that index2, index3, index5 can only be incremented 1500 times
  // so the inner loops are linear time (amortized over the outer loop.
  for (int count = 1; count < 1500; count++) {
    int n2, n3, n5;
    while ((n2 = ugly[index2]*2) <= ugly[count-1]) {
      index2++;
    }

    while ((n3 = ugly[index3]*3) <= ugly[count-1]) {
      index3++;
    }

    while ((n5 = ugly[index5]*5) <= ugly[count-1]) {
      index5++;
    }

    ugly[count] = min3(n2, n3, n5);
  }

  cout << "The 1500'th ugly number is " << ugly[1499] << "." << endl;
  return 0;
}
