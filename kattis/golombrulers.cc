#include <bits/stdc++.h>

using namespace std;

void solve(const string &line)
{
  istringstream iss(line);

  vector<int> A;
  int x;
  while (iss >> x) {
    A.push_back(x);
  }

  int n = *max_element(begin(A), end(A));
  int used[2001] = {0};
  for (int i = 0; i < A.size(); i++) {
    for (int j = i+1; j < A.size(); j++) {
      used[abs(A[i]-A[j])]++;
    }
  }

  for (int i = 1; i <= n; i++) {
    if (used[i] > 1) {
      cout << "not a ruler" << endl;
      return;
    }
  }
  if (count(used+1, used+n+1, 1) == n) {
    cout << "perfect" << endl;
    return;
  }
  cout << "missing";
  for (int i = 1; i <= n; i++) {
    if (!used[i]) cout << ' ' << i;
  }
  cout << endl;

}

int main()
{
  string line;
  while (getline(cin, line))
    solve(line);
  return 0;
}
