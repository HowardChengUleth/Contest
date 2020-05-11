// the idea is that this is basically like a string with two types of balanced
// brackets

#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

char closing[256];

void clean_stack(vector<char> &S, char x)
{
  switch (x) {
    case 'a':
    case 'i':
      assert(S.size() > 0 && S[S.size()-1] == x);
      S.pop_back();
      break;
    case 'e':
    case 'o':
      S.push_back(closing[x]);
      break;
  }
}

void solve(const string &s)
{
  if (s.length() == 0 || s.length() % 2 != 0) {
    cout << "INVALID" << endl;
    return;
  }

  // now we sweep forward and try to look for the next one with the given
  // prefix.  The last one that works is the one.
  int besti = -1;
  int bestj = -1;
  string cand = "oiea";
  vector<char> S;
  for (unsigned int i = 0; i < s.length(); i++) {
    for (int j = 0; j < 4; j++) {
      if (cand[j] <= s[i]) continue;
      
      // now we try the prefix
      bool bad = false;
      switch (cand[j]) {
	case 'a':
	case 'i':
	  S.push_back(cand[j]);
	  break;
	case 'e':
	case 'o':
	  if (S.size() == 0 || S[S.size()-1] != closing[cand[j]]) {
	    bad = true;
	  } else {
	    S.pop_back();
	  }
	  break;
      }

      if (bad) continue;

      // now try to balance whatever is in the stack
      if (S.size() <= s.length() - i - 1) {
	besti = i;
	bestj = j;
      }

      clean_stack(S, cand[j]);
    }

    switch (s[i]) {
      case 'a':
      case 'i':
	S.push_back(s[i]);
	break;
      case 'e':
      case 'o':
	if (S.size() == 0 || S[S.size()-1] != closing[s[i]]) {
	  cout << "INVALID" << endl;
	  return;
	}
	S.pop_back();
	break;
    }
  }

  if (besti < 0) {
    cout << "ULTIMATE" << endl;
    return;
  }

  // it is possible, so add as many a^k e^k as possible and then
  // closing out the rest
  string answer = s.substr(0, besti) + cand[bestj];
  S.clear();

  for (unsigned int i = 0; i < answer.length(); i++) {
    switch (answer[i]) {
      case 'a':
      case 'i':
	S.push_back(answer[i]);
	break;
      case 'e':
      case 'o':
	S.pop_back();
	break;
    }
  }

  answer.insert(answer.length(), (s.length() - besti - 1 - S.size())/2, 'a');
  answer.insert(answer.length(), (s.length() - besti - 1 - S.size())/2, 'e');
  for (vector<char>::const_reverse_iterator it = S.rbegin();
       it != S.rend(); ++it) {
    answer += closing[*it];
  }    
  
  cout << answer << endl;
}

int main(void)
{
  closing['e'] = 'a';
  closing['o'] = 'i';
  closing['a'] = 'e';
  closing['i'] = 'o';

  int Z;
  cin >> Z;

  while (Z--) {
    string s;
    cin >> s;
    solve(s);
  }
  
  return 0;
}
