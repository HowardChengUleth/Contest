/* @JUDGE_ID: 1102NT 651 C++ "" */

// This is harmonic series.
//
// Assume that the overhang of the first n cards is (1 + 1/2 + ... + 1/n)/2 =
// H_n/2.
//
// The new card placed on the bottom of this stack has center:
//
//    H_n/2 + 1/2
//
// The new average is then ((H_n/2 + 1/2) + H_n * n)/(n+1), which simplifies
// to H_{n+1}.  The proof then follows by induction.
//

#include <iostream>
#include <iomanip>

using namespace std;

double overhang(int cards)
{
  double sum = 0.0;

  for (int i = 1; i <= cards; i++) {
    sum += 1.0/i;
  }
  return 0.5*sum;
}

int main(void)
{
  int cards;

  cout << "# Cards Overhang" << endl;
  cout.setf(ios::fixed);
  while (cin >> cards) {
    cout.width(5);
    cout << cards;
    cout.precision(3);
    cout.width(10);
    cout << overhang(cards) << endl;
  }
  return 0;
}
