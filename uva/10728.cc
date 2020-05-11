/* @JUDGE_ID: 1102NT 10728 C++ "" */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void read_line(vector<string> &p)
{
  string line, s;
  getline(cin, line);
  p.clear();

  istringstream is(line);
  while (is >> s) {
    p.push_back(s);
  }
}

int main(void)
{
  int n;
  vector<string> p1, p2;
  map<string,string> sub1, sub2;
  bool good;

  cin >> n;
  cin.ignore();
  while (n-- > 0) {
    read_line(p1);
    read_line(p2);
    sub1.clear();
    sub2.clear();
    good = p1.size() == p2.size();
    
    for (int pass = 0; pass < 2 && good; pass++) {
      for (unsigned int i = 0; i < p1.size() && good; i++) {
	if (p1[i][0] == '<') {
	  if (p2[i][0] == '<') {
	    if (sub1[p1[i]] != "") {
	      good = (sub2[p2[i]] == "" || sub1[p1[i]] == sub2[p2[i]]);
	      sub2[p2[i]] = sub1[p1[i]];
	    } else if (sub2[p2[i]] != "") {
	      good = (sub1[p1[i]] == "" || sub2[p2[i]] == sub1[p1[i]]);
	      sub1[p1[i]] = sub2[p2[i]];
	    }
	  } else {
	    good = (sub1[p1[i]] == "" || sub1[p1[i]] == p2[i]);
	    sub1[p1[i]] = p2[i];
	  }
	} else if (p2[i][0] == '<') {
	  good = (sub2[p2[i]] == "" || sub2[p2[i]] == p1[i]);
	  sub2[p2[i]] = p1[i];
	}
      }
    }
    if (!good) {
      cout << "-" << endl;
    } else {
      for (unsigned int i = 0; i < p1.size(); i++) {
	if (i) {
	  cout << " ";
	}
	if (p1[i][0] != '<') {
	  cout << p1[i];
	} else if (sub1[p1[i]] != "") {
	  cout << sub1[p1[i]];
	} else {
	  cout << "a";
	}
      }
      cout << endl;
    }
  }

  return 0;
}
