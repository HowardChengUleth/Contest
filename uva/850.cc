#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

vector<string> lines;

const string known = "the quick brown fox jumps over the lazy dog";

void read_case(void)
{
  string line;
  lines.clear();
  while (getline(cin, line) && line != "") {
    lines.push_back(line);
  }
}

bool decode(const string &line, char *mapping)
{
  if (line.length() != known.length()) {
    return false;
  }

  bool used[256];
  fill(mapping, mapping+256, '?');
  fill(used, used+256, false);

  for (unsigned int i = 0; i < line.length(); i++) {
    if ((isalpha(line[i]) && !isalpha(known[i])) ||
	(!isalpha(line[i]) && isalpha(known[i]))) {
      return false;
    }
    if (mapping[line[i]] == '?') {
      if (used[known[i]]) {
	return false;
      } else {
	mapping[line[i]] = known[i];
	used[known[i]] = true;
      }
    } else if (mapping[line[i]] != known[i]) {
      return false;
    }
  }
  return true;
} 

void process_case(void)
{
  char mapping[256];
  bool found = false;

  for (unsigned int i = 0; i < lines.size(); i++) {
    if (found = decode(lines[i], mapping)) {
      break;
    }
  }
  if (!found) {
    cout << "No solution." << endl;
  } else {
    mapping[' '] = ' ';
    for (unsigned int i = 0; i < lines.size(); i++) {
      for (unsigned int j = 0; j < lines[i].length(); j++) {
	cout << mapping[lines[i][j]];
      }
      cout << endl;
    }
  }
}

int main(void)
{
  int cases;
  cin >> cases;

  string line;
  getline(cin, line);
  getline(cin, line);
  
  while (cases-- > 0) {
    read_case();
    process_case();
    if (cases > 0) {
      cout << endl;
    }
  }

  return 0;
}
