#include<bits/stdc++.h>
using namespace std;
void calc();
bool isPrime(int count);
vector<int> primes;
int main()
{
  calc();
  int cases, numFlowers;
  long double remainingMoves;
  cin >> cases;
  while(cases--) {
    int count = 0;
    int answer = 0;
    long double fx, fy, cx, cy, total = 0;
    cy = cx = 0;
    cin >> numFlowers >> remainingMoves;
    while(numFlowers--) {
      cin >> fx >> fy;

      long double movesNeeded;
      movesNeeded = sqrt(pow(static_cast<long double>(cx-fx), 2) +
			 pow(static_cast<long double>(cy-fy), 2));
      total += movesNeeded;
      if (total <= remainingMoves) {
	count++;
      }
      if(isPrime(count)) {
	answer = count;
      }
	 
      cx = fx;
      cy = fy;       
    }
      
    cout << answer << endl;
  } 
           
  return 0;
}

void calc()
{
  primes.push_back(2);
  primes.push_back(3);
  
  for(int i = 5; i < 20100; i += 2) {
    bool prime = true;
    for(int j = 3; j*j <= i; j += 2) {
      if ((i%j)==0) {
	prime = false;
	break;
      }
    }
    if (prime)
      primes.push_back(i);
  }
}

bool isPrime(int count)
{
  return find(begin(primes), end(primes), count) != end(primes);
}
   
