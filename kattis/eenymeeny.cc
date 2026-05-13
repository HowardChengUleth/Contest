#include <bits/stdc++.h>

using namespace std;

int main()
{
  string rhyme;
  getline(cin, rhyme);
  int length = count(begin(rhyme), end(rhyme), ' ') + 1;

  int num_kids;
  cin >> num_kids;
  vector<string> kids(num_kids);
  for (auto &x : kids) {
    cin >> x;
  }

  int index = 0;
  vector<string> team[2];
  int curr_team = 0;

  for (int i = 0; i < num_kids; i++) {
    while (kids[index] == "") {
      index = (index + 1) % num_kids;
    }

    int num_skip = length - 1;
    while (num_skip > 0) {
      index = (index + 1) % num_kids;
      if (kids[index] != "") {
	num_skip--;
      }
    }
    team[curr_team].push_back(kids[index]);
    kids[index] = "";
    curr_team = 1 - curr_team;
  }

  for (int t = 0; t < 2; t++) {
    cout << team[t].size() << endl;
    for (auto s : team[t]) {
      cout << s << endl;
    }
  }

  return 0;
}
