#include <bits/stdc++.h>

using namespace std;

struct Part
{
  int val[256];

  void read(string line)
  {
    fill(val, val+256, 0);
    for (auto &c : line) {
      if (!isdigit(c)) c = ' ';
    }
    istringstream iss(line);
    iss >> val['x'] >> val['m'] >> val['a'] >> val['s'];
  }
  
  void print() const
  {
    cout << val['x'] << ' ' << val['m'] << ' ' << val['a'] << ' ' << val['s']
	 << endl;
  }

  int rating() const
  {
    return accumulate(val, val+256, 0);
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

  string process(Part p) const
  {
    int N = test.size();
    for (int i = 0; i < N; i++) {
      char var = test[i][0];
      char cmp = test[i][1];
      int val = stoi(test[i].substr(2));
      int pval = p.val[var];

      bool pass = (cmp == '<' && pval < val) ||
	(cmp == '>' && pval > val);
      if (pass) {
	return dest[i];
      }
    }
    return dest.back();
  }
};

  
map<string, Rule> rules;
vector<Part> parts;

bool accept(Part p)
{
  string label = "in";
  while (label != "A" && label != "R") {
    label = rules[label].process(p);
  }
  return label == "A";
}

int main()
{
  string line;
  while (getline(cin, line) && line != "") {
    Rule r;
    r.read(line);
    rules[r.label] = r;
  }

  while (getline(cin, line) && line != "") {
    Part p;
    p.read(line);
    parts.push_back(p);
  }

  int ans = 0;
  for (auto p : parts) {
    if (accept(p)) {
      ans += p.rating();
    }
  }
  cout << ans << endl;
  
  return 0;
}
