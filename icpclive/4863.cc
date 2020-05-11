// idea: if we assume that every ballon goes to B, then the ones that
//       we want to move back to A are the ones whose DA - DB is minimum
//       and negative.
//
//       Use a greedy strategy to select.

#include <iostream>
#include <algorithm>

using namespace std;

struct Info
{
  int K, DA, DB;

  bool operator<(const Info &x) const
  {
    int mine = DA - DB;
    int other = x.DA - x.DB;

    return mine < other;
  }
};

istream &operator>>(istream &is, Info &x)
{
  return is >> x.K >> x.DA >> x.DB;
}

bool do_case()
{
  int N, A, B;
  cin >> N >> A >> B;
  if (!N && !A && !B) {
    return false;
  }

  Info info[1000];
  int totalB = 0;
  for (int i = 0; i < N; i++) {
    cin >> info[i];
    totalB += info[i].K;
  }

  sort(info, info+N);

  int total = 0;

  for (int i = 0; i < N; i++) {
    int numA, numB;
    if (info[i].DA < info[i].DB) {
      // move if possible
      numA = min(info[i].K, A);
    } else if (A > 0 && totalB > B) {
      // don't move unless there are too many B's
      numA = min(info[i].K, totalB - B);
    } else {
      numA = 0;
    }
    numB = info[i].K - numA;
    total += numA * info[i].DA + numB * info[i].DB;
    A -= numA;
    B -= numB;
    totalB -= info[i].K;
  }

  cout << total << endl;
  return true;
}

int main(void)
{
  while (do_case())
    ;

  return 0;
}
