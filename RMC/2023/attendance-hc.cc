#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  bool absence = false;
  vector<string> callout(N);
  for (int i = 0; i < N; i++) {
    cin >> callout[i];
  }
  callout.push_back("*****");
  
  for (int i = 0; i < N; i++) {
    if (callout[i] == "Present!") continue;
    if (callout[i+1] != "Present!") {
      absence = true;
      cout << callout[i] << endl;
    }
  }
  if (!absence) {
    cout << "No Absences" << endl;
  }
  return 0;
}
