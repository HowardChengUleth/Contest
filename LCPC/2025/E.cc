#include <bits/stdc++.h>

using namespace std;

int total[256];
int freq[256][256];

void training(string train)
{
  train += "$";

  for (int i = 0; i < train.length()-1; i++) {
    freq[train[i]][train[i+1]]++;
    total[train[i]]++;
  }
}

int main()
{
  string word;
  cin >> word;
  word += "$";
  
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    string train;
    cin >> train;
    training(train);
  }

  for (int i = 0; i < 256; i++) {
    if (total[i] == 0) {
      freq[i]['$'] = total[i] = 1;
    }
  }

  double prob = 1.0;
  for (int i = 0; i < word.length()-1; i++) {
    prob *= (double)freq[word[i]][word[i+1]] / total[word[i]];
  }

  cout << fixed << setprecision(12) << prob << endl;

  return 0;
}
