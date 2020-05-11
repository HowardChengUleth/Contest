#include <stack>
#include <string>
#include <iostream>

using namespace std;

void solve(const string &s)
{
  int n = s.length();
  int pos = 1;
  
  stack<char> S;
  int i = 0;
  while (i < n) {
    if (s[i] == '[') {
      S.push(']');
    } else if (s[i] == '{') {
      S.push('}');
    } else if (s[i] == '<') {
      S.push('>');
    } else if (s[i] == '(') {
      if (i+1 < n && s[i+1] == '*') {
	S.push('*');
	i++;
      } else {
	S.push(')');
      }
    } else if (s[i] == ']' || s[i] == '}' || s[i] == '>' || s[i] == ')') {
      if (S.empty() || S.top() != s[i]) {
	cout << "NO " << pos << endl;
	return;
      }
      S.pop();
    } else if (s[i] == '*' && i+1 < n && s[i+1] == ')') {
      if (S.empty() || S.top() != '*') {
	cout << "NO " << pos << endl;
	return;
      }
      S.pop();
      i++;
    }

    pos++;
    i++;
  }
  
  if (S.empty()) {
    cout << "YES" << endl;
  } else {
    cout << "NO " << pos << endl;
  }

}

int main(void)
{
  string s;
  while (getline(cin, s)) {
    solve(s);
  }
  return 0;
}
