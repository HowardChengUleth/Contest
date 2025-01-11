#include <bits/stdc++.h>

using namespace std;

int main()
{
  stack<char> S;

  char ch;
  while (cin >> ch) {
    if (ch == '.') continue;
    if (islower(ch)) {
      S.push(ch);
    } else if (isupper(ch)) {
      while (!S.empty() && S.top() != tolower(ch)) {
	S.pop();
      }
      if (S.empty()) {
	cout << "Neibb" << endl;
	return 0;
      }
      S.pop();
    }
  }

  int freq[256] = {0};
  while (!S.empty()) {
    freq[S.top()]++;
    S.pop();
  }

  cout << freq['p'] << endl;
  cout << freq['g'] << endl;
  cout << freq['o'] << endl;
  
  return 0;
}
