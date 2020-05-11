#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <cassert>

using namespace std;

string decrypt(const string &line, int K)
{
  string plain = line;

  for (unsigned int i = 0; i < line.length(); i++) {
    int v;
    if (line[i] == ' ') {
      v = 0;
    } else {
      v = line[i] - 'A' + 1;
    }
    v = v - K;
    if (v < 0) v += 27;
    plain[i] = (v) ? v - 1 + 'A' : ' '; 
  }
  return plain;
}

int match(const string &plain, const set<string> &dict)
{
  istringstream is(plain);
  string word;
  int count = 0;

  while (is >> word) {
    if (dict.find(word) != dict.end()) {
      count++;
    }
  }
  return count;
}

int main(void)
{
  string s;
  set<string> dict;

  while (getline(cin, s) && s != "#") {
    dict.insert(s);
  }

  string line;
  getline(cin, line);

  int best_K = -1;
  int best_words = -1;
  string best_plain;
  for (int K = 0; K < 27; K++) {
    string plain = decrypt(line, K);
    int t = match(plain, dict);
    if (best_K == -1 || best_words < t) {
      best_K = K;
      best_words = t;
      best_plain = plain;
    }
  }

  while (best_plain[best_plain.length()-1] == ' ') {
    best_plain.erase(best_plain.length()-1, 1);
  }

  while (best_plain.length() > 60) {
    int i, j;
    for (i = 60; i >= 0 && best_plain[i] != ' '; i--)
      ;
    assert(i >= 0);
    for (j = i; j-1 >= 0 && best_plain[j-1] == ' '; j--)
      ;

    cout << best_plain.substr(0, j) << endl;
    best_plain.erase(0, i+1);
  }
  if (best_plain.length() > 0) {
    cout << best_plain << endl;
  }


  return 0;
}
