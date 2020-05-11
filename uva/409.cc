#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

int parse(string s, const set<string> &keywords)
{
  for (unsigned int i = 0; i < s.length(); i++) {
    if (!isalpha(s[i])) {
      s[i] = ' ';
    } else {
      s[i] = tolower(s[i]);
    }
  }

  istringstream is(s);
  string token;
  int count = 0;
  while (is >> token) {
    if (keywords.find(token) != keywords.end()) {
      count++;
    }
  }
  return count;
}

int main(void)
{
  int K, E;
  int case_num = 1;

  while (cin >> K >> E) {
    set<string> keywords;
    string excuse[20];
    int match[20];
    for (int i = 0; i < K; i++) {
      string kw;
      cin >> kw;
      cin.ignore();
      keywords.insert(kw);
    }

    for (int i = 0; i < E; i++) {
      getline(cin, excuse[i]);
      match[i] = parse(excuse[i], keywords);
    }
    
    int best = *max_element(match, match + E);
    cout << "Excuse Set #" << case_num++ << endl;
    for (int i = 0; i < E; i++) {
      if (match[i] == best) {
	cout << excuse[i] << endl;
      }
    }
    cout << endl;
  }
  
  return 0;
}
