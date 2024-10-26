#include <bits/stdc++.h>

using namespace std;

const string color = "RGUB";

int n;
vector<vector<char>> person;

bool check(vector<int> subset)
{
  for (int i = 0; i < 4; i++) {
    string str;
    for (auto v : subset) {
      str += person[v][i];
    }
    sort(begin(str), end(str));
    if (str[0] != str.back()) {
      for (int j = 1; j < str.length(); j++) {
	if (str[j-1] == str[j]) {
	  return false;
	}
      }
    }
  }
  return true;
}

int main()
{
  cin >> n;
  person.resize(n);
  
  for (int i = 0; i < n; i++) {
    person[i].resize(4);
    for (auto &c : person[i]) {
      cin >> c;
    }
  }

  
  int best = 1;
  
  // try all pairs, triples, quads of people
  for (int p1 = 0; p1 < n; p1++) {
    for (int p2 = p1+1; p2 < n; p2++) {
      if (check(vector<int>{p1, p2})) {
	best = max(best, 2);
      }
      for (int p3 = p2+1; p3 < n; p3++) {
	if (check(vector<int>{p1,p2,p3})) {
	  best = max(best, 3);
	}
	for (int p4 = p3+1; p4 < n; p4++) {
	  if (check(vector<int>{p1,p2,p3,p4})) {
	    best = max(best, 4);
	  }
	}
      }
    }
  }
  
  // now try all possible colour combinations and pick the same ones
  for (int c0 = 0; c0 < 4; c0++) {
    for (int c1 = 0; c1 < 4; c1++) {
      for (int c2 = 0; c2 < 4; c2++) {
	for (int c3 = 0; c3 < 4; c3++) {
	  int count = 0;
	  for (auto v : person) {
	    if (v[0] == color[c0] && v[1] == color[c1] &&
		v[2] == color[c2] && v[3] == color[c3]) {
	      count++;
	    }
	  }
	  best = max(best, count);
	}
      }
    }
  }

  cout << best << endl;
  return 0;
}
