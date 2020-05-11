#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool article(const vector<string> &sent, int start, int end)
{
  if (start+1 != end) return false;
  return sent[start] == "a" || sent[start] == "the";
}

bool noun(const vector<string> &sent, int start, int end)
{
  const string list[] = { "tom", "jerry", "goofy", "mickey", "jimmy", "dog",
			  "cat", "mouse" };
  
  if (start+1 != end) return false;
  return (find(list, list+8, sent[start]) - list) != 8;
}

bool verb(const vector<string> &sent, int start, int end)
{
  const string list[] = { "hate", "love", "know", "like" };
  
  if (start+1 != end) return false;
  for (int i = 0; i < 4; i++) {
    if (sent[start].find(list[i]) != 0) continue;
    bool good = true;
    for (int j = 4; j < sent[start].length(); j++) {
      good &= (sent[start][j] == 's');
    }
    if (good) return true;
  }
  return false;
}

bool actor(const vector<string> &sent, int start, int end)
{
  if (start+1 == end) {
    return noun(sent, start, end);
  } else if (start+2 == end) {
    return article(sent, start, start+1) && noun(sent, start+1, end);
  } else {
    return false;
  }
}

bool active_list(const vector<string> &sent, int start, int end)
{
  if (actor(sent, start, end)) {
    return true;
  }
  int pos = find(sent.begin()+start, sent.begin()+end, "and") - sent.begin();
  if (pos == end) {
    return false;
  }
  return actor(sent, start, pos) && active_list(sent, pos+1, end);
}

bool action(const vector<string> &sent, int start, int end)
{
  for (int i = start+1; i+1 < end; i++) {
    if (verb(sent, i, i+1) && active_list(sent, start, i) &&
	active_list(sent, i+1, end)) {
      return true;
    }
  }
  return false;
}

bool statement(const vector<string> &sent, int start, int end)
{
  if (action(sent, start, end)) {
    return true;
  }

  int pos = find(sent.begin()+start, sent.begin()+end, ",") - sent.begin();
  if (pos == end) {
    return false;
  }

  return action(sent, start, pos) && statement(sent, pos+1, end);
}

int main(void)
{
  string s;
  while (getline(cin, s)) {
    for (int i = s.length()-1; i >= 0; i--) {
      if (s[i] == ',') {
	s.insert(i+1, " ");
	s.insert(i, " ");
      }
    }
    
    istringstream iss(s);
    vector<string> sent;
    string word;
    while (iss >> word) {
      sent.push_back(word);
    }
    
    if (statement(sent, 0, sent.size())) {
      cout << "YES I WILL" << endl;
    } else {
      cout << "NO I WON'T" << endl;
    }
  }

  return 0;
}
