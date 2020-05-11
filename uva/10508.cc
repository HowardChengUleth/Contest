#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

struct Word {
  string word;
  int dist;
  
  Word(const string &w, const string &src)
    : word(w)
  {
    dist = 0;
    for (unsigned int i = 0; i < w.length(); i++) {
      if (w[i] != src[i]) {
	dist++;
      }
    }
  }

  bool operator<(const Word &w) const
  {
    return dist < w.dist;
  }
};

ostream &operator<<(ostream &os, const Word &w)
{
  return os << w.word;
}

int main(void)
{
  int num_words, len;

  while (cin >> num_words >> len) {
    vector<Word> v;
    string src;

    cin >> src;
    v.push_back(Word(src, src));

    for (int i = 1; i < num_words; i++) {
      string w;
      cin >> w;
      v.push_back(Word(w, src));
    }
    sort(v.begin(), v.end());
    for (unsigned int i = 0; i < v.size(); i++) {
      cout << v[i] << endl;
    }
  }
  return 0;
}
