/* @JUDGE_ID: 1102NT 694 C++ "" */

#include <iostream>

using namespace std;

long long terms(int A, int L)
{
  long long num = 1;

  while (A != 1) {
    if (A & 1) {
      if (A > (L - 1)/3) {     // compare "backwards" to prevent overflow
	break;
      }
      A = 3*A + 1;
    } else {
      A /= 2;
    }
    num++;
  }
  return num;
}

int main(void)
{
  int case_num = 1;
  int A, L;
  while (cin >> A >> L && A >= 0 && L >= 0) {
    cout << "Case " << case_num++ << ": A = " << A << ", limit = " << L
	 << ", number of terms = " << terms(A, L) << endl;
  }
  return 0;
}
