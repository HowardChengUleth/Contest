#include <bits/stdc++.h>

using namespace std;

vector<vector<string>> food;
vector<vector<string>> allergens;

set<string> i_name, a_name;
set<string> safe_ing;

void solveA()
{
  for (auto ing : i_name) {
    bool safe = true;

    for (auto allerg : a_name) {
      bool possible = true;
      for (int i = 0; i < food.size(); i++) {
	auto &fv = food[i];
	auto &av = allergens[i];
	if (find(begin(fv), end(fv), ing) == end(fv) &&
	    find(begin(av), end(av), allerg) != end(av)) {
	  possible = false;
	  break;
	}
      }
      if (possible) {
	safe = false;
	break;
      }
    }
    if (safe) {
      safe_ing.insert(ing);
    }
  }

  int ans = 0;
  for (const auto &f : food) {
    for (auto s : f) {
      if (safe_ing.count(s)) {
	ans++;
      }
    }
  }

  cout << "A = " << ans << endl;
}

void solveB()
{
  vector<string> unsafe;
  for (auto s : i_name) {
    if (safe_ing.count(s) == 0) {
      unsafe.push_back(s);
    }
  }
  sort(begin(unsafe), end(unsafe));
  do {
    bool possible = true;
    for (int i = 0; i < food.size(); i++) {
      auto &fv = food[i];
      auto &av = allergens[i];
      for (auto a : av) {
	int index = distance(a_name.begin(), a_name.find(a));
	string ing = unsafe[index];
	if (find(begin(fv), end(fv), ing) == end(fv)) {
	  possible = false;
	  break;
	}
      }
      if (!possible) {
	break;
      }
    }

      
    if (possible) {
      cout << "B = ";
      for (int i = 0; i < (int)unsafe.size(); i++) {
	if (i) cout << ',';
	cout << unsafe[i];
      }
      cout << endl;
      return;
    }
  } while (next_permutation(begin(unsafe), end(unsafe)));
  

}

int main()
{
  string line;
  while (getline(cin, line)) {
    for (auto &c : line) {
      if (c == ',' || c == '(' || c == ')') {
	c = ' ';
      }
    }
    
    istringstream iss(line);
    string w;
    vector<string> ingred, allerg;
    while (iss >> w && w != "contains") {
      ingred.push_back(w);
      i_name.insert(w);
    }
    while (iss >> w) {
      allerg.push_back(w);
      a_name.insert(w);
    }
    food.push_back(ingred);
    allergens.push_back(allerg);
  }

  solveA();
  solveB();
  
  return 0;
}
