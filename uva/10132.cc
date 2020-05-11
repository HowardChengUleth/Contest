#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool start(const string &s, const string &prefix)
{
  return s.find(prefix) == 0;
}

bool end(const string &s, const string &suffix)
{
  return s.find(suffix, s.length()-suffix.length()) != string::npos;
}

bool test(string frag[], int N, unsigned int len, const string &cand, 
	  bool used[], int selected = 0)
{
  if (selected == N) {
    return true;
  }
  
  // look for the first string that is unused
  int index = find(used, used+N, false) - used;
  used[index] = true;

  for (int i = index+1; i < N; i++) {
    if (used[i]) continue;
    if (frag[i].length() + frag[index].length() != len) {
      continue;
    }
    
    // try starting with the string
    used[i] = true;
    if (start(cand, frag[index]) && end(cand, frag[i]) &&
	test(frag, N, len, cand, used, selected+2)) {
      return true;
    }
    
    // try ending with the string
    if (start(cand, frag[i]) && end(cand, frag[index]) &&
	test(frag, N, len, cand, used, selected+2)) {
      return true;
    }
    used[i] = false;
  }
  
  // can't start or end, impossible
  used[index] = false;
  return false;
}

bool test(string frag[], int N, unsigned int len, const string &cand)
{
  bool used[300];
  fill(used, used+N, false);

  return test(frag, N, len, cand, used);
}

void do_case(void)
{
  string frag[300];
  int N = 0;
  unsigned int total_len = 0;
  while (getline(cin, frag[N]) && frag[N] != "") {
    total_len += frag[N].length();
    N++;
  }
 
  unsigned int len = total_len / (N/2);

  for (int i = 1; i < N; i++) {
    if (frag[i].length() + frag[0].length() != len) continue;
    string cand = frag[0] + frag[i];
    if (test(frag, N, len, cand)) {
      cout << cand << endl;
      return;
    }
    cand = frag[i] + frag[0];
    if (test(frag, N, len, cand)) {
      cout << cand << endl;
      return;
    }
  }
}

int main(void)
{
  int N;
  cin >> N;
  cin.ignore(1);
  cin.ignore(1);
  while (N-- > 0) {
    do_case();
    if (N > 0) {
      cout << endl;
    }
  }
  return 0;
}
