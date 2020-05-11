#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

map<string,string> type;
map<string,string> rh;
string combs[36];

void print(const string &s, const set<string> &ans)
{
  if (s != "?") {
    cout << ' ' << s;
    return;
  }
  if (ans.size() == 0) {
    cout << " IMPOSSIBLE";
    return;
  }
  if (ans.size() == 1) {
    cout << ' ' << *ans.begin();
  } else {
    cout << " {";
    bool first = true;
    for (set<string>::const_iterator it = ans.begin(); it != ans.end(); ++it) {
      if (!first) cout << ", ";
      cout << *it;
      first = false;
    }
    cout << "}";
  }
}

string totype(string al)
{
  return type[al.substr(0,2)] + rh[al.substr(2,2)];
}

bool valid(string bt, string al)
{
  return bt == "?" || bt == totype(al);
}

bool solve(int id)
{
  string p1, p2, c;

  cin >> p1 >> p2 >> c;
  if (p1 == "E" && p2 == "N" && c == "D") return false;

  set<string> ans;
  for (int i = 0; i < 36; i++) {
    for (int j = 0; j < 36; j++) {
      string child = combs[i];
      child[1] = combs[j][0];
      child[3] = combs[j][2];
      if (!(valid(p1, combs[i]) && valid(p2, combs[j]) && valid(c, child)))
	continue;
      if (p1 == "?") ans.insert(totype(combs[i]));
      if (p2 == "?") ans.insert(totype(combs[j]));
      if (c == "?") ans.insert(totype(child));
    }
  }

  cout << "Case " << id << ":";
  print(p1, ans);
  print(p2, ans);
  print(c, ans);
  cout << endl;
  
  return true;
}

int main()
{
  type["AA"] = "A";
  type["AB"] = type["BA"] = "AB";
  type["AO"] = type["OA"] = "A";
  type["BB"] = "B";
  type["BO"] = type["OB"] = "B";
  type["OO"] = "O";
  rh["++"] = rh["+-"] = rh["-+"] = "+";
  rh["--"] = "-";

  const string al = "ABO";
  const string pm = "+-";
  int t = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 2; k++) {
	for (int l = 0; l < 2; l++) {
	  combs[t] = al[i];
	  combs[t] += al[j];
	  combs[t] += pm[k];
	  combs[t++] += pm[l];
	}
      }
    }
  }

  int id = 1;
  while (solve(id++))
    ;

  return 0;
}
