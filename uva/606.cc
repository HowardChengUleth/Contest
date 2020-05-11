#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>

using namespace std;

struct Rule
{
  vector<int> base;
  int cycle_len;
  bool is_zip;
  char name1, name2,  next;      // 1st and 2nd for zip, next for other case
};

istream &operator>>(istream &is, Rule &r)
{
  r.is_zip = true;
  int val;
  while (is >> val) {
    r.base.push_back(val);
    r.is_zip = false;
  }
  is.clear();

  if (r.is_zip) {
    string zip;
    is >> zip;
    assert(zip == "zip");
    is >> r.name1 >> r.name2;
  } else {
    is >> r.next;
  }
    
  r.cycle_len = 0;

  return is;
}

void read_defs(map<char, Rule> &rule, int n)
{
  for (int i = 0; i < n; i++) {
    string line;
    getline(cin, line);
    istringstream iss(line);

    char lhs, eq;
    iss >> lhs >> eq;
    assert(eq == '=');
    
    iss >> rule[lhs];
  }
}

void compute_cycles(map<char, Rule> &rule)
{
  for (map<char, Rule>::iterator it = rule.begin(); it != rule.end(); ++it) {
    char name = it->first;
    Rule &r = it->second;
    
    // now try to trace through it, but only if it's not zip
    if (r.is_zip) continue;

    bool seen[128];
    fill(seen, seen+128, false);
    seen[name] = true;

    char curr = name;
    int len = rule[curr].base.size();
    while (!seen[rule[curr].next]) {
      curr = rule[curr].next;

      // do not trace any more if there is a zip
      if (rule[curr].is_zip) break;

      seen[curr] = true;
      len += rule[curr].base.size();
    }

    if (rule[curr].next == name) {
      r.cycle_len = len;
    }
  }
}

void compute(vector<int> &vals, map<char, Rule> &rule, 
	     char name, int start,  int numvals, 
	     int out_start = 0, int out_inc = 1)
{
  if (numvals == 0) {
    return;
  }

  if (rule[name].is_zip) {
    int start1 = (start + 1)/2;
    int start2 = start/2;
    int numvals1 = (numvals + (start % 2 == 0)) / 2;
    int numvals2 = numvals - numvals1;
    int out_start1 = (start % 2 == 0) ? out_start : out_start + out_inc;
    int out_start2 = (start % 2 == 1) ? out_start : out_start + out_inc;
      
    compute(vals, rule, rule[name].name1, start1, numvals1, out_start1, 
	    out_inc*2);
    compute(vals, rule, rule[name].name2, start2, numvals2, out_start2, 
	    out_inc*2);
  } else {
    if (rule[name].cycle_len) {
      start %= rule[name].cycle_len;
    }
    for (vector<int>::size_type i = start; 
	 i < rule[name].base.size() && numvals > 0; i++) {
      vals[out_start] = rule[name].base[i];
      numvals--;
      out_start += out_inc;
    }
    start -= rule[name].base.size();
    start = max(0, start);
    compute(vals, rule, rule[name].next, start, numvals, out_start, out_inc);
  }
}

void solve_case(map<char, Rule> &rule)
{
  char name;
  int s, e;
  cin >> name >> s >> e;

  int numvals = e-s+1;
  vector<int> vals(numvals);
  
  compute(vals, rule, name, s, numvals);

  for (int i = 0; i < e-s+1; i++) {
    if (i) cout << ' ';
    cout << vals[i];
  }
  cout << endl;
}

void solve_set()
{
  int n, m;
  cin >> n >> m;
  cin.ignore(1);

  map<char,Rule> rule;
  read_defs(rule, n);

  compute_cycles(rule);

  for (int i = 0; i < m; i++) {
    solve_case(rule);
  }
}

int main(void)
{
  int num_sets;
  cin >> num_sets;

  while (num_sets-- > 0) {
    solve_set();
    if (num_sets) {
      cout << endl;
    }
  }
  return 0;
}
