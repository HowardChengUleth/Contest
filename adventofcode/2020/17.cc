#include <bits/stdc++.h>

using namespace std;

typedef tuple<int,int,int> ti3;
typedef tuple<int,int,int,int> ti4;

set<ti3> stepA(const set<ti3> &active)
{
  set<ti3> ans;
  map<ti3, int> nbr;
  
  for (auto t : active) {
    int active_count = 0;
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
	for (int k = -1; k <= 1; k++) {
	  if (!i && !j && !k) continue;
	  int x, y, z;
	  tie(x,y,z) = t;
	  x += i;  y += j;  z += k;
	  if (active.count(ti3(x,y,z))) {
	    active_count++;
	  } else {
	    nbr[ti3(x,y,z)]++;
	  }
	}
      }
    }
    if (active_count == 2 || active_count == 3) {
      ans.insert(t);
    }
  }

  for (auto p : nbr) {
    if (p.second == 3) {
      ans.insert(p.first);
    }
  }

  return ans;
}

void partA(set<ti3> activeA)
{
  for (int i = 0; i < 6; i++) {
    activeA = stepA(activeA);
  }
  
  cout << "A = " << activeA.size() << endl;
}

set<ti4> stepB(const set<ti4> &active)
{
  set<ti4> ans;
  map<ti4, int> nbr;
  
  for (auto t : active) {
    int active_count = 0;
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
	for (int k = -1; k <= 1; k++) {
	  for (int m = -1; m <= 1; m++) {
	    if (!i && !j && !k && !m) continue;
	    int x, y, z, w;
	    tie(x,y,z, w) = t;
	    x += i;  y += j;  z += k;  w += m;
	    if (active.count(ti4(x,y,z,w))) {
	      active_count++;
	    } else {
	      nbr[ti4(x,y,z,w)]++;
	    }
	  }
	}
      }
    }
    if (active_count == 2 || active_count == 3) {
      ans.insert(t);
    }
  }

  for (auto p : nbr) {
    if (p.second == 3) {
      ans.insert(p.first);
    }
  }

  return ans;
}

void partB(set<ti4> activeB)
{
  for (int i = 0; i < 6; i++) {
    activeB = stepB(activeB);
  }
  
  cout << "B = " << activeB.size() << endl;
}

int main()
{
  int x = 0;
  string s;
  
  set<ti3> activeA;
  set<ti4> activeB;
  
  while (getline(cin, s)) {
    for (int y = 0; y < s.length(); y++) {
      if (s[y] == '#') {
	activeA.emplace(x, y, 0);
	activeB.emplace(x, y, 0, 0);
      }
    }
    x++;
  }

  partA(activeA);
  partB(activeB);


  return 0;
}
