#include <iostream>
#include <map>
#include <set>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

bool do_case(int num)
{
  multiset<string> terms;
  string line;

  // read the terms
  while (getline(cin, line) && line != "") {
    for (string::size_type i = 0; i < line.length(); i++) {
      line[i] = toupper(line[i]);
    }
    terms.insert(line);
  }
  
  if (terms.size() == 0) {
    return false;
  }

  // now process the text
  map<string, set<int> > index;
  int line_num = 1;
  while (getline(cin, line) && line != "") {
    for (string::size_type i = 0; i < line.length(); i++) {
      if (isalnum(line[i])) {
	line[i] = toupper(line[i]);
      } else {
	line[i] = ' ';
      }
    }
    istringstream iss(line);
    string word;
    while (iss >> word) {
      if (terms.count(word) < 1) continue;
      index[word].insert(line_num);
    }
    line_num++;
  }

  // print the index
  if (num > 1) {
    //    cout << endl;
  }
  cout << "Case " << num << endl;
  for (multiset<string>::const_iterator term_it = terms.begin();
       term_it != terms.end(); ++term_it) {
    if (index.find(*term_it) == index.end()) continue;

    cout << *term_it << ' ';
    const set<int> &pages = index[*term_it];
    bool printed = false;
    set<int>::const_iterator page_it = pages.begin();
    while (page_it != pages.end()) {
      set<int>::const_iterator next_it = page_it;
      ++next_it;
      int first = *page_it;
      int prev = first;
      while (next_it != pages.end() && *next_it == prev+1) {
	prev = *next_it;
	++next_it;
      }
      if (printed) {
	cout << ", ";
      }
      if (first == prev) {
	cout << first;
      } else {
	cout << first << '-' << prev;
      }
      printed = true;
      page_it = next_it;
    }
    cout << endl;
  }
  cout << endl;

  return true;
}

int main(void)
{
  int num = 1;
  while (do_case(num++))
    ;

  return 0;
}
