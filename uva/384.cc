#include <iostream>
#include <string>

using namespace std;

bool slump(const string &s)
{
  if (s.length() < 1 || (s[0] != 'D' && s[0] != 'E')) return false;

  unsigned int i;
  for (i = 1; i < s.length() && s[i] == 'F'; i++)
    ;
  if (i == 1) return false;
  if (i >= s.length()) return false;
  if (s[i] == 'G' && i == s.length()-1) return true;
  return slump(s.substr(i, s.length()-i));
}

bool slimp(const string &s)
{
  if (s.length() < 1 || s[0] != 'A') return false;
  if (s.length() == 2) {
    return s[1] == 'H';
  }
  if (s.length() >= 3 && s[1] == 'B' && s[s.length()-1] == 'C' &&
      slimp(s.substr(2, s.length()-3))) {
    return true;
  }
  if (s.length() >= 2 && s[s.length()-1] == 'C' &&
      slump(s.substr(1, s.length()-2))) {
    return true;
  }
  return false;
}

bool slurpy(const string &s)
{
  unsigned int n = s.length();

  for (unsigned int i = 1; i <= n-1; i++) {
    if (slimp(s.substr(0, i)) && slump(s.substr(i, n-i))) {
      return true;
    }
  }
  return false;
}

int main(void)
{
  int N;

  cin >> N;
  cout << "SLURPYS OUTPUT" << endl;
  while (N-- > 0) {
    string s;
    cin >> s;
    if (slurpy(s)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }
  cout << "END OF OUTPUT" << endl;
  return 0;
}
