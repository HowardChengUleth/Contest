#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

map<string,int> output;

struct Rule
{
  string in1, in2, out;
  string op;
  bool applied;

  Rule(string line)
    : applied{false}
  {
    istringstream iss(line);
    string arrow;
    
    iss >> in1 >> op >> in2 >> arrow >> out;
  }

  bool can_apply() const
  {
    return !applied && output.find(in1) != output.end() &&
      output.find(in2) != output.end();
  }

  void apply() 
  {
    assert(can_apply());

    int val1 = output[in1], val2 = output[in2];
    int outval;
    if (op == "AND") {
      outval = (val1 && val2) ? 1 : 0;
    } else if (op == "OR") {
      outval = (val1 || val2) ? 1 : 0;
    } else if (op == "XOR") {
      outval = (val1 ^ val2) ? 1 : 0;
    }
    output[out] = outval;
    applied = true;
  }
};

vector<Rule> rule;

void read_input()
{
  string line;
  while (getline(cin, line) && line != "") {
    replace(begin(line), end(line), ':', ' ');
    istringstream iss(line);

    string name;
    int val;
    iss >> name >> val;
    output[name] = val;
  }

  while (getline(cin, line)) {
    rule.emplace_back(line);
  }
}


int main()
{
  read_input();
  int rules_left = rule.size();
  while (rules_left > 0) {
    for (int i = 0; i < rule.size(); i++) {
      if (rule[i].can_apply()) {
	rule[i].apply();
	rules_left--;
      }
    }
  }

  ll ans = 0;
  ll pow2 = 1;
  for (auto [var, val] : output) {
    if (var[0] != 'z') continue;
    ans += val * pow2;
    pow2 <<= 1;
  }

  cout << ans << endl;

  return 0;
}

