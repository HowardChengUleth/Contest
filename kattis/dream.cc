#include <bits/stdc++.h>

using namespace std;

stack<string> events;
map<string,int> last;   // for an event, when was the last time it happened?

void add_event()
{
  string e;
  cin >> e;
  last[e] = events.size();
  events.push(e);
}

void dream()
{
  int r;
  cin >> r;

  for (int i = 0; i < r; i++) {
    string e = events.top();
    events.pop();
    last.erase(e);
  }
}

void scenario()
{
  int k;
  cin >> k;

  int must_include = -1;         // we must include this index and earlier
  int must_remove = INT_MAX;     // must remove this index and later
  
  for (int i = 0; i < k; i++) {
    string e;
    cin >> e;

    if (e[0] != '!') {
      if (last.find(e) == end(last)) {
	must_include = INT_MAX;        // impossible
      } else {
	must_include = max(must_include, last[e]);
      }
    } else {
      e = e.substr(1);
      if (last.find(e) == end(last)) {
	// no need to do anything
      } else {
	must_remove = min(must_remove, last[e]);
      }
    }
  }

  if (must_remove <= must_include) {
    cout << "Plot Error" << endl;
  } else if (must_remove > events.size()) {
    cout << "Yes" << endl;
  } else {
    cout << events.size() - must_remove << " Just A Dream" << endl;
  }
}


int main()
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    char cmd;
    cin >> cmd;
    switch (cmd) {
    case 'E':
      add_event();
      break;

    case 'D':
      dream();
      break;

    case 'S':
      scenario();
      break;
    }
  }



  return 0;
}
