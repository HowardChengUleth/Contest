#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

map<string,int> output;

map<string, string> rename_map;
vector<pair<string,string>> swap_out;

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

  int index() const
  {
    if (!(isdigit(out[1]) && isdigit(out[2]))) {
      return 1000;
    }
    return (out[1] - '0') * 10 + (out[2] - '0');
  }

  bool operator<(const Rule &r) const
  {
    if (index() == r.index()) {
      return out < r.out;
    }
    return index() < r.index();
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

  void rename()
  {
    if (rename_map.find(in1) != rename_map.end()) {
      in1 = rename_map[in1];
    }
    if (rename_map.find(in2) != rename_map.end()) {
      in2 = rename_map[in2];
    }
    if (rename_map.find(out) != rename_map.end()) {
      out = rename_map[out];
    }
    if (in1 > in2) {
      swap(in1, in2);
    }
  }

};

ostream &operator<<(ostream &os, const Rule &r)
{
  os << r.in1 << ' ' << r.op << ' ' << r.in2 << " -> " << r.out;
  return os;
}

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

ll getval(char prefix)
{
  ll ans = 0;
  ll pow2 = 1;
  for (auto [var, val] : output) {
    if (var[0] != prefix) continue;
    ans += val * pow2;
    pow2 <<= 1;
  }
  return ans;
}

ll solve_z()
{
  for (auto &r : rule) {
    r.applied = false;
    output.erase(r.out);
  }
  
  int rules_left = rule.size();
  while (rules_left > 0) {
    int delta = 0;
    for (int i = 0; i < (int)rule.size(); i++) {
      if (rule[i].can_apply()) {
	rule[i].apply();
	delta++;
      }
    }
    rules_left -= delta;
    if (delta == 0) {
      return -1;
    }
  }

  return getval('z');
}

void putval(ll val, char prefix)
{
  for (int i = 0; i <= 44; i++) {
    
    ostringstream out;
    out << prefix << setw(2) << setfill('0') << i;
    output[out.str()] = val % 2;
    val /= 2;
  }
}

set<int> wrong;

void compare_bit(ll correct, ll compute)
{
  bitset<46> bs1(correct), bs2(compute);
  for (int i = 0; i <= 45; i++) {
    if (bs1[i] != bs2[i]) {
      wrong.insert(i);
    }
  }
}

void read_rename()
{
  ifstream in("rename_map.txt");

  string orig, rep;
  while (in >> orig >> rep) {
    rename_map[orig] = rep;
  }
}

void read_swap()
{
  ifstream in("swap.txt");
  string s1, s2;
  while (in >> s1 >> s2) {
    swap_out.emplace_back(s1, s2);
  }
}

void do_swap(string &s, string s1, string s2)
{
  if (s == s1) {
    s = s2;
  } else if (s == s2) {
    s = s1;
  }
}


void swap_and_rename()
{
  for (auto [s1, s2] : swap_out) {
    for (auto &r : rule) {
      do_swap(r.out, s1, s2);
    }
  }

  for (auto &r : rule) {
    r.rename();
  }
}

int main()
{
  read_rename();
  read_swap();

  read_input();
  swap_and_rename();

  sort(begin(rule), end(rule));
  for (auto r : rule) {
    cout << r << endl;
  }

  return 0;
  

  
  
  for (int i = 0; i < 1000; i++) {
    ll xval = ll(rand()) * ll(rand());
    ll yval = ll(rand()) * ll(rand());
    xval &= (1LL << 45) - 1;
    yval &= (1LL << 45) - 1;
    putval(xval, 'x');
    putval(yval, 'y');
    /*
    cout << "x = " << xval << endl;
    cout << "y = " << yval << endl;
    cout << "x+y = " << xval + yval << endl;
    cout << "z   = " << solve_z() << endl;
    */
    compare_bit(xval + yval, solve_z());
  }

  for (auto b : wrong) {
    cout << "bit " << b << " is wrong" << endl;
  }
  
  /*    
    int N = rule.size();
    if (solve_z() == xval + yval) {
      cout << "nothing needs to be swapped" << endl;
      continue;
    }
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
	swap(rule[i].out, rule[j].out);
	if (solve_z() == xval + yval) {
	  cout << rule[i].out << ' ' << rule[j].out << endl;
	}
	swap(rule[i].out, rule[j].out);
      }
    }
    }
  */

  return 0;
}

