#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

const int MAX_K = 1000;

typedef pair<string, int> BFSnode;

string x, y;
int k;
string word[MAX_K];

  queue<BFSnode> q;
  set<string> visited;
  
void add_node(queue<BFSnode> &q, const string &s, set<string> &visited, 
	      int dist)
{
  if (visited.find(s) == visited.end()) {
    q.push(make_pair<string, int>(s, dist));
    visited.insert(s);
  }
}

int solve(void)
{
  int nx = x.length(), ny = y.length();

  // first see if they have the same length
  if (nx == ny) {
    return (x == y) ? 0 : -1;
  }

  // see if one is a substring of the other
  if (ny < nx) {
    swap(nx, ny);
    swap(x, y);
  }
  if (y.find(x)) {
    return -1;
  }

  /* now we start a BFS search on the part that "sticks out" */
  queue<BFSnode> q;
  set<string> visited;
  
  add_node(q, y.substr(nx), visited, 0);
  while (!q.empty()) {
    BFSnode u = q.front();
    q.pop();

    string &suffix = u.first;
    int suffix_len = suffix.length();

    // now look for a word that can be used for adjustment
    for (int i = 0; i < k; i++) {
      int w_len = word[i].length();
      if (suffix == word[i]) {
	// we are done
	return u.second+1;
      }
      if (suffix_len < w_len) {
	if (!word[i].find(suffix)) {
	  add_node(q, word[i].substr(suffix_len), visited, u.second+1);
	}
      } else if (suffix_len > w_len) {
	if (!suffix.find(word[i])) {
	  add_node(q, suffix.substr(w_len), visited, u.second+1);
	}
      }
    }

  }
  return -1;
}

int main(void)
{
  int cases;

  cin >> cases;
  while (cases-- > 0) {
    cin >> x >> y;
    cin >> k;
    for (int i = 0; i < k; i++) {
      cin >> word[i];
    }
    cout << solve() << endl;
  }
  return 0;
}
