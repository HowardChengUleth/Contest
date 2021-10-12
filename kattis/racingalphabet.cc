#include <bits/stdc++.h>

using namespace std;

int index(char c)
{
  if (isalpha(c)) return c - 'A';
  if (c == ' ') return 26;
  return 27;
}

void solve()
{
  string s;
  getline(cin, s);

  int total = 0;
  for (int i = 1; i < s.length(); i++) {
    int p1 = index(s[i-1]);
    int p2 = index(s[i]);

    int steps = min((p1 - p2 + 28) % 28, (p2 - p1 + 28) % 28);
    total += steps;
  }

  const double PI = acos(-1.0);
  double circ = 60 * PI;
  double dist = circ / 28.0 * total;
  double time = dist / 15.0 + s.length();

  cout << fixed << setprecision(10) << time << endl;
  
  
}

int main()
{
  int N;
  cin >> N;
  cin.ignore();
  while (N--)
    solve();

  return 0;
}
