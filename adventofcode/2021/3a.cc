#include <bits/stdc++.h>

using namespace std;

int main()
{
  vector<string> bits;
  string s;
  while (cin >> s) {
    bits.push_back(s);
  }

  string gamma = bits[0], epsilon = bits[0];
  int n = gamma.length();

  for (int i = 0; i < n; i++) {
    int count0 = 0;
    for (const auto &s : bits) {
      if (s[i] == '0') {
	count0++;
      }
    }
    int count1 = bits.size() - count0;
    if (count0 > count1) {
      gamma[i] = '0';
      epsilon[i] = '1';
    } else if (count0 < count1) {
      gamma[i] = '1';
      epsilon[i] = '0';
    } else {
      assert(false);
    }
  }

  bitset<12> G(gamma), E(epsilon);

  cout << G.to_ullong() * E.to_ullong() << endl;

  
  return 0;
}
