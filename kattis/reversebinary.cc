#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  bitset<32> bs(N);
  string s = bs.to_string();
  reverse(begin(s), end(s));
  while (s.back() == '0') {
    s.erase(s.length()-1);
  }
  bitset<32> bs2(s);

  cout << bs2.to_ulong() << endl;

  
  return 0;
}
