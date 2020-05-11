/* @JUDGE_ID: 1102NT 10100 C++ "" */

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <iomanip>

using namespace std;

void parse_words(string& s, vector<string>& v)
{
  // NOTE: digits are "letters" too for this problem
  for (unsigned int i = 0; i < s.length(); i++) {
    if (!isalnum(s[i])) {
      s[i] = ' ';
    }
  }
  istringstream sstr(s);
  string t;
  while (sstr >> t) {
    v.push_back(t);
  }
}

int match(const vector<string>& v1, const vector<string> &v2)
{
  int n1 = v1.size(), n2 = v2.size();
  int **A = new int *[n1+1];
  for (int i = 0; i <= n1; i++) {
    A[i] = new int[n2+1];
  }
  for (int i = 0; i <= n1; i++) {
    A[i][0] = 0;
  }
  for (int j = 0; j <= n2; j++) {
    A[0][j] = 0;
  }

  for (int i = 1; i <= n1; i++) {
    for (int j = 1; j <= n2; j++) {
      if (v1[i-1] == v2[j-1]) {
	A[i][j] = 1 + A[i-1][j-1];
      } else {
	A[i][j] = A[i-1][j];
	if (A[i][j] < A[i][j-1]) {
	  A[i][j] = A[i][j-1];
	}
      }
    }
  }
  int res = A[n1][n2];
  for (int i = 0; i <= n1; i++) {
    delete[] A[i];
  }
  delete[] A;
  return res;
}

int main(void)
{
  int cases;
  string s1, s2;

  cases = 1;

  // NOTE: the last line may not be terminated with '\n'!
  while (getline(cin, s1) && getline(cin, s2)) {
    cout << setw(2) << cases++ << ". ";
    vector<string> v1, v2;
    
    parse_words(s1, v1);
    parse_words(s2, v2);

    if (s1.length() == 0 || s2.length() == 0) {
      cout << "Blank!" << endl;
    } else {
      cout << "Length of longest match: " << match(v1, v2) << endl;
    }
  }
  
  return 0;
}
