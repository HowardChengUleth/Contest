#include <bits/stdc++.h>

using namespace std;

map<string,char> status;

int main()
{
  int N, L;
  cin >> N >> L;

  for (int i = 0; i < N; i++) {
    string name;
    char s;
    cin >> name >> s;
    status[name] = s;
  }

  bool maybe = false;
  for (int i = 0; i < L; i++) {
    string name1, name2, arrow;
    cin >> name1 >> arrow >> name2;

    char s1 = status[name1], s2 = status[name2];
    if (s1 == 'm' && s2 == 'u') {
      cout << 1 << endl;
      return 0;
    }

    maybe |= (s1 == 'm' && s2 == '?') || (s1 == '?' && s2 == 'u');
  }

  if (maybe) {
    cout << '?' << endl;
  } else {
    cout << 0 << endl;
  }
  
  return 0;
}
