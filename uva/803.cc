#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>
#include <cctype>
#include <algorithm>

using namespace std;

const int N = 8;

string tolower(const string &word)
{
  string result = word;
  for (string::iterator it = result.begin(); it != result.end(); ++it) {
    *it = tolower(*it);
  }
  return result;
}

void read_words(vector<string> &words)
{
  words.clear();
  
  string line, word;
  getline(cin, line);
  istringstream iss(line);
  while (iss >> word) {
    words.push_back(tolower(word));
  }
}

int compute_score(const vector<string> &page, const vector<string> &words)
{
  int score = 0;
  int N1, N2;

  N1 = N;
  for (unsigned int i = 0; i < page.size(); i++, N1--) {
    N2 = N;
    for (unsigned int j = 0; j < words.size(); j++, N2--) {
      if (page[i] == words[j]) {
	score += N1 * N2;
      }
    }
  }

  return score;
}

void process_query(const vector< vector<string> > &page,
		   const vector<string> &words)
{
  vector< pair<int, int> > score;
  for (unsigned int i = 0; i < page.size(); i++) {
    int page_num = i+1;
    int page_score = compute_score(page[i], words);
    score.push_back(make_pair(-page_score, page_num));
  }

  sort(score.begin(), score.end());
  
  int printed = 0;
  for (unsigned int i = 0; i < page.size() && printed < 5; i++) {
    if (score[i].first == 0) continue;
    if (!printed) {
      cout << "  ";
    }
    cout << " P" << score[i].second;
    //    cout << "(" << score[i].first << ")";
    printed++;
  }
}

int main(void)
{
  vector< vector<string> > page;

  cout << "Query Pages" << endl;
  
  int query_num = 1;
  char code;
  vector<string> words;
  while (cin >> code && code != 'E') {
    read_words(words);
    switch (code) {
      case 'P':
	page.push_back(words);
	break;
      case 'Q':
	cout << "Q" << query_num++ << ":";
	process_query(page, words);
	cout << endl;
	break;
      default:
	assert(0);
    }
  }

  return 0;
}
