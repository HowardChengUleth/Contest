// Rubik's Cube:
//
// This is how the faces are labelled. Note that you fold the box
//  away from you, so C is the closest face to you and E is the
//  farthest:
//
//         +-------+
//         |       |
//         |   A   |
//         |       |
// +-------+-------+-------+-------+
// |       |       |       |       |
// |   B   |   C   |   D   |   E   |
// |       |       |       |       |
// +-------+-------+-------+-------+
//         |       |
//         |   F   |
//         |       |
//         +-------+
//
// The assigning of array entries is as follows:
//
//         +-------+
//         | 1 2 3 |
//         | 8 0 4 |
//         | 7 6 5 |
// +-------+-------+-------+-------+
// | 1 2 3 | 1 2 3 | 1 2 3 | 1 2 3 |
// | 8 0 4 | 8 0 4 | 8 0 4 | 8 0 4 |
// | 7 6 5 | 7 6 5 | 7 6 5 | 7 6 5 |
// +-------+-------+-------+-------+
//         | 1 2 3 |
//         | 8 0 4 |
//         | 7 6 5 |
//         +-------+
//
// If you would like to rotate Face X 90 degrees clockwise,
//    then call rotateFace(X)
// If you would like to rotate Face X 90 degrees counterclockwise,
//    then call rotateFace(X) 3 times
//
// The main is the solution to 12492 -- Rubik Cycle
//  They used different labels for their faces, so I just mapped their
//  names to mine.

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;

string rot[6] = {"BEDC1111","ACFE7773",
		 "ADFB5713","AEFC3733",
		 "ABFD1753","BCDE5555"};
int cube[6][9];

int m9(int x){ return (x % 9 == 0 ? 1 : x % 9); }

void rotateFace(char F){
   int ind = F - 'A';
   rotate(cube[ind]+1,cube[ind]+7,cube[ind]+9);
   
   int t[3];
   string r = rot[ind];
   for(int i=0;i<3;i++)
      t[i] = cube[r[3]-'A'][m9(r[7]-'0'+i)];

   for(int i=7;i>4;i--)
      for(int j=0;j<3;j++)
	 cube[r[i-4]-'A'][m9(r[i]-'0'+j)] = cube[r[i-5]-'A'][m9(r[i-1]-'0'+j)];
   for(int j=0;j<3;j++)
      cube[r[0]-'A'][m9(r[4]-'0'+j)] = t[j];
}

void printCube(){
   string o = "123804765";
   for(int F=0;F<6;F++){
      cout << "Face " << char(F+'A') << endl;
      for(int i=0;i<3;i++){
	 for(int j=0;j<3;j++)
	    cout << setw(3) << cube[F][o[i*3+j]-'0'];
	 cout << endl;
      }
   }
}

long long gcd(long long a, long long b){
  long long r;
  while (b) {
     r = a % b;
     a = b;
     b = r;
  }
  return a;
}

long long lcm(long long x,long long y){
   return (x/gcd(x,y))*y;
}

int main(){
   int minTime[6][9];
   
   string faces = "ULFRBD";
   string lower = "ulfrbd";
   string s;
   while(getline(cin,s)){
      int ctr = 0;
      for(int i=0;i<6;i++)
	 for(int j=0;j<9;j++)
	    cube[i][j] = ctr++;
      int numDone = 0;
      for(int i=0;i<6;i++)
	 fill(minTime[i],minTime[i]+9,-1);

      long long LCM = 1;
      int timeCtr = 1;
      while(numDone < 54){
	 for(int i=0;i<s.length();i++)
	    if(faces.find(s[i]) != string::npos){
	       rotateFace(faces.find(s[i]) + 'A');
	    } else {
	       for(int j=0;j<3;j++)
		  rotateFace(lower.find(s[i]) + 'A');
	    }

	 bool foundSome = false;
	 for(int i=0;i<6;i++)
	    for(int j=0;j<9;j++){
	       if(minTime[i][j] != -1)
		  continue;
	       if(cube[i][j] == i*9+j){
		  minTime[i][j] = timeCtr;
		  numDone++;
		  foundSome = true;
	       }
	    }
	 if(foundSome)
	    LCM = lcm(LCM,timeCtr);
	 timeCtr++;
      }
      
      cout << LCM << endl;
   }
   
   return 0;
}
