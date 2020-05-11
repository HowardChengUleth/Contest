// brute force.  If we wanted to we can easily find the first and last
// character in the permutation (if they are unique), but it is not
// necessary for this problem.  We can also use topological sort, or
// even transitive closure.

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(void)
{
  int N;
  int case_num = 1;
  while (cin >> N && N) {
    cout << "Case " << case_num++ << ":" << endl;
    cout << "  ";
    
    string seq[100];
    bool visit[256] = {0};
    int count = 0;
    string perm;
    for (int i = 0; i < N; i++) {
      cin >> seq[i];
      for (unsigned int j = 0; j < seq[i].length(); j++) {
	if (!visit[seq[i][j]]) {
	  visit[seq[i][j]] = true;
	  count++;
	  perm += seq[i][j];
	}
      }
    }

    if (count != 9) {
      cout << " Ambiguous" << endl << endl;
      continue;
    }

    sort(perm.begin(), perm.end());
    int num_found = 0;
    string perm_found = "";
    do {
      bool good = true;
      for (int i = 0; good && i < N; i++) {
	good &= perm.find(seq[i]) != string::npos;
      }
      if (good) {
	num_found++;
	perm_found = perm;
      }
    } while (next_permutation(perm.begin(), perm.end()) &&
	     num_found <= 1);

    if (num_found != 1) {
      cout << " Ambiguous" << endl;
    } else {
      for (int i = 0; i < 9; i++) {
	cout << ' ' << i+1;
      }
      cout << endl << "  ";
      for (int i = 0; i < 9; i++) {
	cout << ' ' << perm_found[i];
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}
