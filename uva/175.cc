#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>
#include <cctype>

using namespace std;

struct Profile {
  int thresh;
  vector<string> keyword;

  bool match(const vector<string> &title) const {
    unsigned int i, j, x, y;

    for (i = 0; i < keyword.size(); i++) {
      for (j = i+1; j < keyword.size(); j++) {
	for (x = 0; x < title.size(); x++) {
	  if (keyword[i] != title[x]) continue;
	  for (y = 0; y < title.size(); y++) {
	    if (keyword[j] != title[y] || x == y) continue;
	    if ((int)(x) - (int)y - 1 <= thresh && 
		(int)(y) - (int)x - 1 <= thresh) {
	      return true;
	    }
	  }
	}
      }
    }
    return false;
  }
};

istream &operator>>(istream &is, Profile &p)
{
  is >> p.thresh;

  string s;
  getline(is, s);
  istringstream iss(s);
  string kw;
  p.keyword.clear();
  while (iss >> kw) {
    p.keyword.push_back(kw);
  }
  return is;
}

void read_title(vector<string> &line)
{

  string s;
  char ch;
  while (cin.get(ch) && ch != '|') {
    if (ch == ' ' || isalpha(ch)) {
      s += tolower(ch);
    }
  }

  istringstream is(s);
  line.clear();
  string w;
  while (is >> w) {
    line.push_back(w);
  }
}

int main(void)
{
  char ch;
  vector<Profile> prof;
  vector< vector<string> > title;

  while (cin >> ch && ch != '#') {
    cin.ignore(1);
    if (ch == 'P') {
      Profile p;
      cin >> p;
      prof.push_back(p);
    } else if (ch == 'T') {
      vector<string> line;

      read_title(line);

      title.push_back(line);
    }
  }

  for (unsigned int i = 0; i < prof.size(); i++) {
    cout << i+1 << ": ";

    bool first = true;
    for (unsigned int j = 0; j < title.size(); j++) {
      if (prof[i].match(title[j])) {
	if (!first) {
	  cout << ",";
	}
	cout << j+1;
	first = false;
      }
    }
    cout << endl;
  }

  return 0;
}
