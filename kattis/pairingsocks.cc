#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<int> a(2*n);
  for (int i = 0; i < 2*n; i++) {
    cin >> a[i];
  }

  stack<int> S1, S2;
  for (auto it = rbegin(a); it != rend(a); ++it) {
    S1.push(*it);
  }

  // we keep checking top of S1 and S2.
  //
  // If they are the same, we pop them and match.
  // If not (or if S2 is empty), we have to pop from S1 and push to S2.
  //
  // no two consecutive socks in S2 can be matching (or we would not have
  // pushed it into S2)
  //
  // So we only need to consider moves 1 and 3
  int moves = 0;
  while (!S1.empty()) {
    if (S2.empty() || S1.top() != S2.top()) {
      S2.push(S1.top());
      S1.pop();
    } else {
      S1.pop();
      S2.pop();
    }
    moves++;
  }

  if (S2.empty()) {
    cout << moves << endl;
  } else {
    cout << "impossible" << endl;
  }

  return 0;
}
