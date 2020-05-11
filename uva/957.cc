#include <iostream>

using namespace std;

int A[100000];

void do_case(int Y)
{
  int P;
  cin >> P;
  for (int i = 0; i < P; i++) {
    cin >> A[i];
  }

  int start, end;

  start = 0;
  for (end = start; end < P && A[end] - A[start] + 1 <= Y; end++)
    ;
  
  int best_sum = end - start;
  int best_start = start;
  int best_end = end - 1;

  while (end < P) {
    while (A[end] - A[start] + 1 > Y) {
      start++;
    }
    while (end < P && A[end] - A[start] + 1 <= Y) {
      end++;
    }
    if (end - start > best_sum) {
      best_sum = end - start;
      best_start = start;
      best_end = end - 1;
    }
  }

  cout << best_sum << ' ' << A[best_start] << ' ' << A[best_end-1] << endl;
}

int main(void)
{
  int case_num = 1;
  int Y;
  while (cin >> Y) {
    if (case_num++ > 1) {
      //      cout << endl;
    }
    do_case(Y);
  }

  return 0;
}
