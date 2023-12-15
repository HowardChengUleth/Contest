#include <bits/stdc++.h>

using namespace std;

typedef pair<string,int> lens;
vector<lens> box[256];

int myhash(const string &s)
{
  int ans = 0;
  for (auto c : s) {
    ans += (int)c;
    ans *= 17;
    ans %= 256;
  }
  return ans;
}

void process(string s)
{
  if (s.back() == '-') {
    s.erase(s.length()-1);
    int dest = myhash(s);
    bool found = false;
    for (int i = 0; i < (int)box[dest].size(); i++) {
      if (box[dest][i].first == s) {
	box[dest].erase(begin(box[dest]) + i);
	found = true;
      }
    }
  } else {
    replace(begin(s), end(s), '=', ' ');
    istringstream iss(s);
    string label;
    int id;
    iss >> label >> id;
    int dest = myhash(label);
    bool found = false;
    for (auto &[str, oldid] : box[dest]) {
      if (str == label) {
	found = true;
	oldid = id;
      }
    }
    if (!found) {
      box[dest].emplace_back(label, id);
    }
  }
}

void print_boxes()
{
  for (int i = 0; i < 256; i++) {
    if (box[i].size() == 0) continue;
    cout << "Box " << i << ": ";
    for (auto [s, id] : box[i]) {
      cout << "[" << s << ", " << id << "] ";
    }
    cout << endl;
  }
}

int fpower()
{
  int ans = 0;
  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < (int)box[i].size(); j++) {
      ans += (i+1) * (j+1) * box[i][j].second;
    }
  }
  return ans;
}

int main()
{
  string line;
  cin >> line;
  replace(begin(line), end(line), ',', ' ');

  istringstream iss(line);
  string s;
  while (iss >> s) {
    process(s);
    //print_boxes();
  }

  int ans = fpower();
  cout << ans << endl;

  return 0;
}
