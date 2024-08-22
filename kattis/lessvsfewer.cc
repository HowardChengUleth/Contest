#include <bits/stdc++.h>

using namespace std;

set<string> C, M;

vector<string> both_first{ "most", "more" };
vector<string> count_first{ "number", "fewest", "fewer", "many", "few" };
vector<string> mass_first{ "amount", "least", "less", "much", "little" };

bool check()
{
  string line;
  getline(cin, line);

  istringstream iss(line);
  string first, last;
  iss >> first;

  while (iss >> last)
    ;

  return (find(begin(both_first), end(both_first), first) != end(both_first)) ||
    (find(begin(count_first), end(count_first), first) != end(count_first) &&
     C.find(last) != end(C)) ||
    (find(begin(mass_first), end(mass_first), first) != end(mass_first) &&
     M.find(last) != end(M));
}

int main()
{
  int n, p;
  cin >> n >> p;

  for (int i = 0; i < n; i++) {
    string noun, type;
    cin >> noun >> type;
    if (type == "c") {
      C.insert(noun);
    } else {
      M.insert(noun);
    }
  }
  cin.ignore(1);

  for (int i = 0; i < p; i++) {
    if (check()) {
      cout << "Correct!" << endl;
    } else {
      cout << "Not on my watch!" << endl;
    }
  }

  return 0;
}
