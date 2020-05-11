#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string dict[10000];
int len[10000];
int n;

int main(void)
{
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> dict[i];
    len[i] = dict[i].length();
  }
  int q;
  cin >> q;
  while (q--) {
    string word;
    cin >> word;
    cout << word << " is ";
    if (find(dict, dict+n, word) != dict+n) {
      cout << "correct" << endl;
      continue;
    }

    int found = -1;
    int wlen = word.length();
    for (int i = 0; i < n && found < 0; i++) {
      if (len[i] == wlen) {
	// rule 2 or 3
	int wrong = 0;
	int adj = 0;
	for (int j = 0; j < wlen; j++) {
	  if (dict[i][j] != word[j]) { 
	    wrong++;
	    if (j+1 < wlen && 
		dict[i][j] == word[j+1] && dict[i][j+1] == word[j]) {
	      adj++;
	    }
	  }
	}
	if (wrong == 1 || (wrong == 2 && adj == 1)) {
	  found = i;
	}
      } else if (len[i]-1 == wlen) {
	// rule 1
	for (int j = 0; j < len[i] && found < 0; j++) {
	  string s = dict[i];
	  s.erase(j, 1);
	  if (s == word) {
	    found = i;
	  }
	}
      } else if (len[i] == wlen-1) {
	// rule 1
	for (int j = 0; j < wlen && found < 0; j++) {
	  string s = word;
	  s.erase(j, 1);
	  if (s == dict[i]) {
	    found = i;
	  }
	}
      }
    }

    if (found < 0) {
      cout << "unknown" << endl;
    } else {
      cout << "a misspelling of " << dict[found] << endl;
    }
  }

  return 0;
}
