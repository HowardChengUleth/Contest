#include <iostream>
#include <algorithm>

using namespace std;

int M[500][500];

int gcd(int a, int b)
{
  while (b) {
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int count(int Am, int An, int Bm, int Bn)
{
  // look at each Bm x Bn blocks, they have to be rational multiples
  // of each other
  for (int block_i = 0; block_i < Am; block_i++) {
    for (int block_j = 0; block_j < An; block_j++) {
      for (int i = 0; i < Bm; i++) {
	for (int j = 0; j < Bn; j++) {
	  if (M[block_i * Bm][block_j * Bn] * M[i][j] != 
	      M[0][0] * M[block_i*Bm+i][block_j*Bn+j]) {
	    return 0;
	  }
	}
      }
    }
  }
  
  return 1;
}

bool do_case(void)
{
  int r, c;
  cin >> r >> c;
  if (r == 0 && c == 0) return false;

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> M[i][j];
    }
  }

  // now the smallest A[i][j] must be a factor of the GCD of the matrix
  int G = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      G = gcd(G, M[i][j]);
    }
  }
  int Gfactors = 1;
  for (int i = 1; i <= G/2; i++) {
    if (G % i == 0) {
      Gfactors++;
    }
  }

  int ans = 0;
  for (int Am = 1; Am <= r; Am++) {
    if (r % Am) continue;
    for (int An = 1; An <= c; An++) {
      if (Am == 1 && An == 1) continue;
      if (Am == r && An == c) continue;
      if (c % An) continue;

      int Bm = r / Am, Bn = c / An;

      // now we want to see how many ways is there to form a tensor
      // product with Am x An matrix and Bm x Bn matrix
      ans += count(Am, An, Bm, Bn) * Gfactors;
    }
  } 
  cout << ans << endl;
  return true;
}

int main(void)
{
  while (do_case())
    ;
  return 0;
}
