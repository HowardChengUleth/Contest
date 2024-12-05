#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef set<int> si;
map<int, si> rule;

void read_rule()
{
  string line;
  while (getline(cin, line) && line != "") {
    replace(begin(line), end(line), '|', ' ');
    istringstream iss(line);
    int x, y;
    iss >> x >> y;
    rule[x].insert(y);
  }
}

vi read_job()
{
  string line;
  cin >> line;
  replace(begin(line), end(line), ',', ' ');
  istringstream iss(line);

  vi result;
  int x;
  while (iss >> x) {
    result.push_back(x);
  }
  return result;
}

bool check_job(const vi &v)
{
  for (int i = 0; i < v.size(); i++) {
    for (int j = i+1; j < v.size(); j++) {
      if (rule[v[j]].count(v[i]) > 0) return false;
    }
  }

  return true;
}
  
bool cmp(int a, int b)
{
  return (rule[a].count(b) > 0);
}

int main()
{
  read_rule();

  int ans = 0;
  while (true) {
    auto v = read_job();
    if (v.size() == 0) break;
    assert(v.size() % 2 == 1);

    if (check_job(v)) continue;

    sort(begin(v), end(v), cmp);

    ans += v[v.size()/2];
  }

  cout << ans << endl;

  return 0;
}
