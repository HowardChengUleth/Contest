// Idea: this is greedy algorithm: if you can finish the job without training
// anyone, you are done.
//
// If not, it is always best to train as soon as possible (so the newly
// certified coders can code more earlier).  Just train as many as you
// can, move forward by 4 days, and repeat.  Either we can finish the job
// without training, or we run out of people to train.
//
// As long as we are training, the number of certified people doubles.  So
// it takes about O(log E) steps to train everyone.  That is also the worst
// case complexity.

#include <iostream>
#include <algorithm>

using namespace std;

void solve()
{
  long long D, E, L;
  cin >> D >> E >> L;

  long long currday = 0;
  long long cert = 1;
  
  while (currday <= D) {
    long long daysleft = D - currday;
    long long cando = (cert * 200 + (E - cert) * 40) * daysleft;

    if (cando >= L) {
      cout << "Yes" << endl;
      return;
    }
    
    long long totrain = min(cert, E-cert);
    if (totrain == 0) break;   // can't train more: can't do any better

    // I am not doing any bound checking here to make sure that there are
    // at least 4 days left...how did I get away with that?
    long long next4 = 4*((cert - totrain)*200 + (E - cert - totrain)*40);
    L -= next4;

    cert += totrain;
    currday += 4;
  }

  cout << "No" << endl;
}

int main()
{
  int T;
  cin >> T;
  while (T--)
    solve();
  
  return 0;
}
