// CYK parsing.  Assumes that each rule has at most 2 nonterminals on RHS.
// If not, rewrite the rule.  No need to change anything for part b...just
// rewrite the rules and run the same program

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

struct Rule
{
  int n;
  vi rhs[2];
  char ch;

  void read(string line)
  {
    string L[2];
    n = ch = 0;
    auto it = line.find('|');
    if (it == string::npos) {
      L[n++] = line;
    } else {
      L[n++] = line.substr(0, it);
      L[n++] = line.substr(it+1);
      assert(line.find('|', it+1) == string::npos);
    }

    for (int i = 0; i < n; i++) {
      istringstream iss(L[i]);
      int x;
      while (iss >> x) {
	rhs[i].push_back(x);
      }
      assert(rhs[i].size() <= 2);
      if (rhs[i].size() == 0) {
	if (L[i].find('a') != string::npos) {
	  ch = 'a';
	} else {
	  ch = 'b';
	}
      }
    }
  }
};

Rule rule[1000];

int memo[1000][100][100];

bool parse(int r, const string &line, int s, int e)
{
  if (memo[r][s][e] >= 0) {
    return memo[r][s][e];
  }

  if (rule[r].ch) {
    return memo[r][s][e] = (s+1 == e && line[s] == rule[r].ch);
  }

  bool ans = false;
  for (int i = 0; i < rule[r].n && !ans; i++) {
    auto R = rule[r].rhs[i];
    if (R.size() == 1) {
      ans |= parse(R[0], line, s, e);
    } else {
      for (int k = s+1; k < e && !ans; k++) {
	ans |= (parse(R[0], line, s, k) && parse(R[1], line, k, e));
      }
    }
  }
  return memo[r][s][e] = ans;
}

int main()
{
  string line;

  while (getline(cin, line) && line != "") {
    auto it = line.find(':');
    int i = stoi(line.substr(0, it));
    rule[i].read(line.substr(it+1));
  }

  int ansA = 0;
  while (getline(cin, line)) {
    for (int i = 0; i < 1000; i++) {
      for (int j = 0; j < 100; j++) {
	for (int k = 0; k < 100; k++) {
	  memo[i][j][k]  = -1;
	}
      }
    }
    if (parse(0, line, 0, line.length())) {
      ansA++;
    }
  }
  cout << "A = " << ansA << endl;

  return 0;
}
