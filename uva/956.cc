#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 128;
int n;

struct State {
  int next1, next2;
  bool win;
};

istream &operator>>(istream &is, State &s)
{
  char n1, n2, w;
  is >> n1 >> n2 >> w;

  s.next1 = n1;
  s.next2 = n2;
  s.win = (w == 'w');
  return is;
}

State state[MAX_N];
  
bool read_case(void)
{
  if (!(cin >> n)) {
    return false;
  }

  for (int i = 0; i < n; i++) {
    char s;
    cin >> s;
    cin >> state[(int)s];
  }

  return true;
}

#include <cassert>

void solve_case()
{
  int first = 'A', last = 'A' + n;
  bool equiv[MAX_N][MAX_N];
  for (int i = first; i < last; i++) {
    fill(equiv[i]+first, equiv[i]+last, true);
  }

  bool changed;
  do {
    changed = false;

    for (int c1 = first; c1 < last; c1++) {
      for (int c2 = c1+1; c2 < last; c2++) {
	if (!equiv[c1][c2]) continue;

	/* two states are equivalent if they have equivalent n1 and n2,
	   and same win/lose */
	State s1 = state[c1], s2 = state[c2];
	if (!(s1.win == s2.win && equiv[s1.next1][s2.next1] &&
	      equiv[s1.next2][s2.next2])) {
	  equiv[c1][c2] = equiv[c2][c1] = false;
	  changed = true;
	}
      }
    }
  } while (changed);

  
  bool left[MAX_N];
  fill(left+first, left+last, true);

  bool printed = false;
  for (char c = first; c < last; c++) {
    if (left[c]) {
      if (printed) cout << ' ';
      cout << c;
      printed = true;

      for (char c2 = c+1; c2 < last; c2++) {
	if (equiv[c][c2]) {
	  left[c2] = false;
	}
      }
    }
  }
  cout << endl;
}

int main(void)
{
  while (read_case()) {
    solve_case();
  }
  return 0;
}
