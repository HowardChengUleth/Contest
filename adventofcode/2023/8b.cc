#include <bits/stdc++.h>

using namespace std;

typedef pair<string, string> pss;
map<string, pss> G;

bool read_node()
{
  string line;
  getline(cin, line);
  if (cin.eof()) return false;

  for (auto &c : line) {
    if (!isalnum(c)) c = ' ';
  }
  
  istringstream iss(line);
  string from, left, right;
  iss >> from >> left >> right;
  G[from] = make_pair(left, right);
  //  cout << "from, left, right " << from << ' ' << left << ' ' << right << endl;

  return true;
}

string dir;

bool done(const vector<string> &loc)
{
  for (auto s : loc) {
    if (s[2] != 'Z') return false;
  }
  return true;
}

int count_steps(const vector<string> &from, int index = 0)
{
  if (index >= (int)dir.length()) {
    index = 0;
  }

  if (done(from)) return 0;

  vector<string> next;

  for (auto s : from) {
    string nexts = (dir[index] == 'L') ? G[s].first : G[s].second;
    next.push_back(nexts);
  }
  return 1 + count_steps(next, index+1);
}

void find_cycle(string s, vector<int> &pos, int &cycle_start, int &len)
{
  typedef pair<string,int> psi;
  map<psi, int> seen;

  int step = 0;
  int index = 0;
  seen[psi(s, index)] = step++;

  while (true) {
    string next = (dir[index] == 'L') ? G[s].first : G[s].second;
    index = (index+1) % dir.length();
    //    cout << "(" << next << ", " << index << ")" << endl;
    if (seen.find(psi(next, index)) == seen.end()) {
      if (next[2] == 'Z') {
	pos.push_back(step);
      }
      seen[psi(next, index)] = step++;
    } else {
      len = step - seen[psi(next, index)];
      cycle_start = seen[psi(next, index)];
      return;
    }
    s = next;
  }
}

typedef long long ll;
ll gcd(ll a, ll b)
{
  if (!b) return a;
  return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
  return a / gcd(a, b) * b;
}

ll lcm(vector<int> x)
{
  ll ans = 1;
  for (auto a : x) {
    ans = lcm(ans, a);
  }
  return ans;
}

int main()
{
  cin >> dir;

  string str;
  getline(cin, str);
  getline(cin, str);
  while (read_node())
    ;

  vector<string> startstr;
  for (auto [a, b]: G) {
    if (a[2] == 'A') {
      startstr.push_back(a);
    }
  }

  vector<int> cycle_start(startstr.size(), 0),
    cycle_len(startstr.size(), 0);
  vector<vector<int>> pos(startstr.size());
  
  for (unsigned int i = 0; i < startstr.size(); i++) {
    find_cycle(startstr[i], pos[i], cycle_start[i], cycle_len[i]);
  }

  // big cheat...turns out for input, pos[i] == cycle_len[i], so we are
  // just looking for lcm
  vector<int> vals;
  for (auto v : pos) {
    vals.push_back(v[0]);
  }
  
  cout << lcm(vals) << endl;
  
  return 0;
}
