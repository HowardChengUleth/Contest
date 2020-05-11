#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int N;
  while (cin >> N) {
    bool awake[26] = {false};
    int M;
    cin >> M;

    string s;
    cin >> s;
    for (int i = 0; i < 3; i++) {
      awake[s[i]-'A'] = true;
    }

    bool adj[26][26];
    for (int i = 0; i < 26; i++) {
      fill(adj[i], adj[i]+26, false);
    }
    while (M--) {
      cin >> s;
      adj[s[0]-'A'][s[1]-'A'] = true;
      adj[s[1]-'A'][s[0]-'A'] = true;
    }

    bool changed = true;
    int count = 3;
    int years = 0;
    bool awake2[26] = { false };
    
    while (count < N && changed) {
      copy(awake, awake+26, awake2);

      changed = false;

      for (int i = 0; i < 26; i++) {
	if (awake2[i]) continue;

	int c = 0;
	for (int j = 0; j < 26; j++) {
	  if (adj[i][j] && awake2[j]) c++;
	}
	if (c >= 3) {
	  awake[i] = true;
	  count++;
	  changed = true;
	}
      }
      years++;
    }

    if (count == N) {
      cout << "WAKE UP IN, " << years << ", YEARS" << endl;
    } else {
      cout << "THIS BRAIN NEVER WAKES UP" << endl;
    }
    
  }

  return 0;
}
