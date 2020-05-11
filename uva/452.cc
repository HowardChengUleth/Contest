#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

int len[26];
int complete[26];
bool depend[26][26];

int compute(int i)
{
  if (complete[i] >= 0) {
    return complete[i];
  }

  int before = 0;
  for (int j = 0; j < 26; j++) {
    if (depend[i][j]) {
      before = max(before, compute(j));
    }
  }
  return complete[i] = before + len[i];
}

void solve()
{
  fill(len, len+26, -1);
  fill(complete, complete+26, -1);
  for (int i = 0; i < 26; i++) {
    fill(depend[i], depend[i]+26, false);
  }
  
  string line;
  while (getline(cin, line) && line != "") {
    istringstream iss(line);
    char task;
    iss >> task;
    iss >> len[task-'A'];
    char task2;
    while (iss >> task2) {
      depend[task-'A'][task2-'A'] = true;
    }
  }

  for (int i = 0; i < 26; i++) {
    if (len[i] >= 0) {
      compute(i);
    }
  }
  cout << *max_element(complete, complete+26) << endl;
}

int main(void)
{
  int T;
  cin >> T;
  cin.ignore(1);
  cin.ignore(1);
  while (T--) {
    solve();
    if (T) cout << endl;
  }
  return 0;
}
