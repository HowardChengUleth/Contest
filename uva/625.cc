/* @JUDGE_ID: 1102NT 625 C++ "" */

#include <iostream>
#include <map>
#include <cctype>
#include <string>
#include <cassert>

using namespace std;

string keywords[16] = {
  "var", "end", "for", "then", "else", "case", "goto", "const", "label",
  "while", "begin", "until", "repeat", "downto", "function", "procedure"
};

bool seen_end = false;

string get_token(void)
{
  string token = "";
  char c;
  bool done = false;

  while (cin.get(c) && !isalnum(c)) {
    if (seen_end && c == '.') {
      done = true;
    } else {
      seen_end = false;
    }
    cout << c;
  }

  if (done) {
    cin.unget();
    return token;
  }
  if (cin.eof()) {
    return token;
  }

  token += string(1,c);
  while (cin.get(c) && isalnum(c)) {
    token += string(1,c);
  }
  if (!cin.eof()) {
    cin.unget();
  }
  seen_end = (token == "end");
  return token;
}

void solve(void)
{
  string token;
  map< string, int > dict;

  for (int i = 0; i < 16; i++) {
    dict[keywords[i]] = i;
  }

  seen_end = false;
  while ((token = get_token()) != "") {
    if (token.length() < 3) {
      cout << token;
    } else {
      if (dict.find(token) != dict.end()) {
	cout << '&' << dict[token];
      } else {
	cout << token;
	int t = dict.size();
	dict[token] = t;
	assert(dict.size() <= 2000);
      }
    }
  }
}

int main(void)
{
  int cases;

  cin >> cases;
  cin.ignore();
  cin.ignore();

  while (cases-- > 0) {
    solve();
  }
  return 0;
}
