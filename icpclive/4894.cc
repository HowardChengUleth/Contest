#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <utility>

using namespace std;

bool allwhite(const string &line)
{
  for (unsigned int i = 0; i < line.length(); i++) {
    if (!isspace(line[i])) return false;
  }
  return true;
}

bool do_case(int id)
{
  typedef unsigned long long ull;
  typedef map<ull, string> mymap;
  mymap nodes[33];
  string line;

  if (!getline(cin, line) || allwhite(line)) {
    return false;
  }

  string total = line;
  while (getline(cin, line) && !allwhite(line)) {
    total += '\n';
    total += line;
  }

  for (int i = total.length()-1; i >= 0; i--) {
    if (total[i] == '(' || total[i] == ')') {
      total.insert(i+1, " ");
      total.insert(i, " ");
    }
  }
  
  cout << "Case " << id << ":" << endl;

  istringstream iss(total);

  char mode;
  iss >> mode;
  iss.putback(mode);

  if (mode == '(') {
    char dummy;
    while (iss >> dummy) {
      int level;
      ull pos;
      string label;
      iss >> level >> dummy >> pos >> dummy >> label >> dummy;
      nodes[level][pos] = label;
    }
  } else {
    int level = 1;
    string cmd;
    while (iss >> cmd) {
      if (cmd == "level") level++;
      else {
	ull pos;
	string label;
	iss >> pos >> label;
	nodes[level][pos] = label;
      }
    }
  }

  for (int level = 1; level <= 32; level++) {
    for (mymap::const_iterator it = nodes[level].begin();
	 it != nodes[level].end(); ++it) {
      int pos = it->first;
      if (pos > (1ULL << (level-1))) {
	cout << "    Not viable: too many nodes on a level." << endl;
	return true;
      }

      if (level == 1) continue;
      int parent = (pos+1)/2;
      if (nodes[level-1].find(parent) == nodes[level-1].end()) {
	cout << "    Not viable: a non-root node has no parent." << endl;
	return true;
      }
    }
  }

  if (mode == '(') {
    int prev_level = 1;
    for (int level = 1; level <= 32; level++) {
      for (mymap::const_iterator it = nodes[level].begin();
	   it != nodes[level].end(); ++it) {
	while (prev_level < level) {
	  cout << "   level" << endl;
	  prev_level++;
	}
	cout << "   node " << it->first << ' ' << it->second << endl;
      }
    }


  } else {
    for (int level = 1; level <= 32; level++) {
      for (mymap::const_iterator it = nodes[level].begin();
	   it != nodes[level].end(); ++it) {
	cout << "   (" << level << ", " << it->first << ", "
	     << it->second << ")" << endl;
      }
    }
  }
  cout << endl;
  return true;
}

int main(void)
{
  int case_num = 1;

  while (do_case(case_num++))
    ;

  return 0;
}
