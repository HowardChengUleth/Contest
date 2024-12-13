#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void parse_button(string s, int &dx, int &dy)
{
  istringstream iss(s);
  string word;
  char ch;
  
  iss >> word >> word >> ch >> ch >> dx >> ch >> ch >> ch >> dy;
}

void parse_prize(string s, int &x, int &y)
{
  istringstream iss(s);
  string word;
  char ch;

  iss >> word >> ch >> ch >> x >> ch >> ch >> ch >> y;
}

ll solve_case()
{
  const int Acost = 3, Bcost = 1;

  string s1, s2, s3, s4;
  getline(cin, s1);
  if (!cin.good()) {
    return -1;
  }
  
  getline(cin, s2);
  getline(cin, s3);
  getline(cin, s4);

  int Ax, Ay, Bx, By, Tx, Ty;

  parse_button(s1, Ax, Ay);
  parse_button(s2, Bx, By);
  parse_prize(s3, Tx, Ty);

  int best_cost = -1;
  for (int A = 0; A <= 100; A++) {
    for (int B = 0; B <= 100; B++) {
      if (!(A * Ax + B * Bx == Tx &&
	    A * Ay + B * By == Ty)) continue;
      int cost = A * Acost + B * Bcost;
      if (best_cost < 0 || cost < best_cost) {
	best_cost = cost;
      }
    }
  }

  return max(0, best_cost);
}

int main()
{
  ll best_cost = 0, ans = 0;
  while ((best_cost = solve_case()) >= 0) {
    ans += best_cost;
  }

  cout << ans << endl;

  return 0;
}
