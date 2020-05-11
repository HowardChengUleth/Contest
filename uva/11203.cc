#include <iostream>
#include <string>

using namespace std;

int main(void)
{
  int N;
  cin >> N;
  while (N--) {
    string s;
    cin >> s;

    bool bad = false;
    int n = s.length();
    int Mi = -1, Ei = -1;
    for (int i = 0; i < n && !bad; i++) {
      bad |= !(s[i] == '?' || s[i] == 'M' || s[i] == 'E');
      if (s[i] == 'M') {
	bad |= (Mi >= 0);
	Mi = i;
      } else if (s[i] == 'E') {
	bad |= (Ei >= 0);
	Ei = i;
      }
    }

    bad |= (Mi > Ei);
    int a = Mi, b = Ei - Mi - 1, c = n - Ei - 1;
    bad |= (!a || !b || !c || a+b != c);

    if (bad) cout << "no-";
    cout << "theorem" << endl;
  }
  return 0;
}
