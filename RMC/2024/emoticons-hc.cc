#include <bits/stdc++.h>

using namespace std;

// intentionally not being efficient in anything

vector<string> emoticons{
  ":---:",
  ":)",
  ":-)",
  ":-(",
  ";-)",
  "xD",
  "^_^",
  "-_-",
  "^o^",
  "^^;",
  "(..)"};

int convert(string s)
{
  if (s.length() == 0) {
    return 0;
  }
  
  for (const auto &e : emoticons) {
    if (s.find(e) == 0) {
      return 1 + convert(s.substr(e.length()));
    }
  }

  return 1 + convert(s.substr(1));
}

int main()
{
  string s;
  getline(cin, s);

  int min_ans = s.length();
  int max_ans = 0;
  
  for (int f = 0; f < 256; f++) {
    for (int t = 0; t < 256; t++) {
      if (!(isprint(f) && isprint(t)))
	continue;

      string s2 = s;
      replace(begin(s2), end(s2), f, t);
      int temp = convert(s2);
      min_ans = min(min_ans, temp);
      max_ans = max(max_ans, temp);
    }
  }

  cout << min_ans << ' ' << max_ans << endl;
  
  return 0;
}
