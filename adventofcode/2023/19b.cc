#include <bits/stdc++.h>

using namespace std;

const string xmas = "xmas";
typedef long long ll;

struct Part
{
  ll lb[256], ub[256];

  Part()
  {
    fill(lb, lb+256, 0);
    fill(ub, ub+256, 0);
    lb['x'] = lb['m'] = lb['a'] = lb['s'] = 1;
    ub['x'] = ub['m'] = ub['a'] = ub['s'] = 4000;
  }
  
  void print() const
  {
    for (auto c : xmas) {
      cout << c << ": " << lb[(int)c] << '-' << ub[(int)c] << endl;
    }
  }

  void update(char ch, char cmp, int val, bool pos)
  {
    if (cmp == '<') {
      if (pos) {
	ub[(int)ch] = val-1;
      } else {
	lb[(int)ch] = val;
      }
    } else if (cmp == '>') {
      if (pos) {
	lb[(int)ch] = val+1;
      } else {
	ub[(int)ch] = val;
      }
    }
  }
    
  ll comb() const
  {
    ll ans = 1;
    for (auto c : xmas) {
      if (ub[(int)c] >= lb[(int)c]) {
	ans *= ub[(int)c] - lb[(int)c] + 1;
      } else {
	ans = 0;
      }
    }
    return ans;
  }
};

struct Rule
{
  string label;
  vector<string> test, dest;

  void read(string line)
  {
    for (auto &c : line) {
      if (c == '{' || c == ',' || c == '}') {
	c = ' ';
      }
    }
    istringstream iss(line);
    iss >> label;
    string part;
    while (iss >> part) {
      auto pos = part.find(':');
      if (pos == string::npos) {
	dest.push_back(part);
      } else {
	replace(begin(part), end(part), ':', ' ');
	istringstream iss2(part);
	string s1, s2;
	iss2 >> s1 >> s2;
	test.push_back(s1);
	dest.push_back(s2);
      }
    }
  }

  void print() const
  {
    cout << label << ":";
    for (auto s : test) {
      cout << ' ' << s;
    }
    cout << ":";
    for (auto s : dest) {
      cout << ' ' << s;
    }
    cout << endl;
  }

  vector<pair<string,Part>> process(Part p) const
  {
    vector<pair<string,Part>> result;
    
    int N = test.size();
    for (int i = 0; i < N; i++) {
      char var = test[i][0];
      char cmp = test[i][1];
      int val = stoi(test[i].substr(2));

      Part p1 = p;
      p1.update(var, cmp, val, true);
      result.emplace_back(dest[i], p1);
      p.update(var, cmp, val, false);
    }
    result.emplace_back(dest.back(), p);
    return result;
  }
};

  
map<string, Rule> rules;
vector<Part> parts;

ll process(string label, Part part)
{
  if (label == "A") {
    return part.comb();
  }
  if (label == "R") {
    return 0;
  }
  
  auto res = rules[label].process(part);
  ll ans = 0;
  for (auto [label2, part2] : res) {
    ans += process(label2, part2);
  }
  return ans;
}

ll count()
{
  Part og_part;
  string label = "in";
  return process(label, og_part);
}

int main()
{
  string line;
  while (getline(cin, line) && line != "") {
    Rule r;
    r.read(line);
    rules[r.label] = r;
  }

  ll ans = count();
  cout << ans << endl;
  
  return 0;
}
