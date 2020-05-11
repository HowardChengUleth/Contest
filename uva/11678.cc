#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

bool solve()
{
  int A, B;
  cin >> A >> B;
  if (!A && !B) return false;

  set<int> S1, S2;
  for (int i = 0; i < A; i++) {
    int t;
    cin >> t;
    S1.insert(t);
  }
  for (int i = 0; i < B; i++) {
    int t;
    cin >> t;
    S2.insert(t);
  }

  vector<int> S3;
  set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(), back_inserter(S3));

  cout << min(S1.size() - S3.size(), S2.size() - S3.size()) << endl;

  return true;
}

int main(void)
{
  while (solve())
    ;
  return 0;
}
