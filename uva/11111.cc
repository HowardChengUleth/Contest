#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <utility>

using namespace std;

bool solve(const string &s)
{
  istringstream iss(s);

  stack<pair<int, int> > S;

  int size;
  while (iss >> size) {
    if (size < 0) {
      S.push(make_pair(-size, 0));
    } else if (size > 0) {
      if (S.empty() || S.top().first != size) {
	return false;
      }
      S.pop();
      if (!S.empty()) {
	S.top().second += size;
	if (S.top().second >= S.top().first) {
	  return false;
	}
      }
    }
  }

  return S.empty();
}

int main(void)
{
  string s;
  while (getline(cin, s)) {
    if (solve(s)) {
      cout << ":-) Matrioshka!" << endl;
    } else {
      cout << ":-( Try again." << endl;
    }
  }
  return 0;
}
