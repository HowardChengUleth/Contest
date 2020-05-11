/* @JUDGE_ID: 1102NT 10625 C++ "" */

#include <iostream>
#include <string>

using namespace std;

typedef unsigned long long Matrix[127][127];
typedef unsigned long long Vector[127];
Matrix expansion, expansion4;   // expansion4 = expansion^4 to speed things up
                     // not needed to get it fast enough for the judge, though
bool rule_present[127];

void read_case(void)
{
  for (int i = 33; i < 127; i++) {
    for (int j = 33; j < 127; j++) {
      expansion[i][j] = 0;
    }
    rule_present[i] = false;
  }

  int R;
  cin >> R;
  while (R-- > 0) {
    char from;
    string s;
    cin >> from;
    rule_present[from] = true;
    cin.ignore(2);
    cin >> s;
    for (unsigned int i = 0; i < s.length(); i++) {
      expansion[from][s[i]]++;
    }
  }

  for (int i = 33; i < 127; i++) {
    int j;
    for (j = 33; j < 127; j++) {
      if (expansion[i][j]) {
	break;
      }
    }
    if (j == 127) {
      expansion[i][i] = 1;
    }
  }
}

void expand(Matrix expansion, Vector v)
{
  Vector w;
  for (int i = 33; i < 127; i++) {
    w[i] = v[i];
    v[i] = 0;
  }
  for (int i = 33; i < 127; i++) {
    if (!rule_present[i]) {
      v[i] += w[i] * expansion[i][i];
    } else {
      for (int j = 33; j < 127; j++) {
	v[j] += w[i] * expansion[i][j];
      }
    }
  }
}

void solve_case(void)
{
  int Q;
  Vector v;
  int steps;
  string s;
  char ch;

  for (int i = 33; i < 127; i++) {
    for (int j = 33; j < 127; j++) {
      expansion4[i][j] = expansion[i][j];
    }
  }
  for (int k = 0; k < 3; k++) {
    for (int i = 33; i < 127; i++) {
      if (rule_present[i]) {
	expand(expansion, expansion4[i]);
      }
    }
  }

  cin >> Q;
  while (Q-- > 0) {
    for (int i = 33; i < 127; i++) {
      v[i] = 0;
    }
    cin >> s >> ch >> steps;

    for (unsigned int i = 0; i < s.length(); i++) {
      v[s[i]]++;
    }

    for (int i = 0; i < steps/4; i++) {
      expand(expansion4, v);
    }
    for (int i = 0; i < steps % 4; i++) {
      expand(expansion, v);
    }

    cout << v[ch] << endl;
  }
}

int main(void)
{
  int T;

  cin >> T;
  while (T-- > 0) {
    read_case();
    solve_case();
  }
  return 0;
}
