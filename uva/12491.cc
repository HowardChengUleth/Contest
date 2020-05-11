#include <iostream>
#include <queue>
using namespace std;

struct tri{
   int Set, word, letter;
   bool operator<(const tri& x) const{
      if(Set != x.Set) return Set < x.Set;
      if(word != x.word) return word < x.word;
      return letter < x.letter;
   }
};

const int MAX_N = 25;
const int MAX_L = 45;
string s[2][MAX_N];
bool searched[2][MAX_N][MAX_L];

bool do_case(int N[]){
   for(int i=0;i<2;i++)
      for(int j=0;j<N[i];j++)
	 cin >> s[i][j];

   for(int i=0;i<2;i++)
      for(int j=0;j<=N[i];j++)
	 for(int k=0;k<=s[i][j].length();k++)
	    searched[i][j][k] = false;
   
   queue<tri> q;
   for(int i=0;i<N[0];i++){
      tri tmp = {0,i,0};
      q.push(tmp);
      searched[0][i][0] = true;
   }

   int val,ind;
   while(!q.empty()){
      tri t = q.front(); q.pop();
      int v = t.Set;
      int w = t.word;
      int L = t.letter;
      // For each word in the other set, find all strings whose
      // prefixes match the current suffix
      for(int i=0;i<N[1-v];i++){
	 for(int j=0;j<s[1-v][i].length() && j+L<s[v][w].length();j++)
	    if(s[1-v][i][j] != s[v][w][j+L])
	       goto nextI;
	 // This is the amount of "extra stuff"
	 val = s[1-v][i].length() - (s[v][w].length()-L);
	 if(val == 0) return true;
	 if(val > 0){
	    ind = s[1-v][i].length()-val;
	    if(!searched[1-v][i][ind]){
	       tri tmp = {1-v,i,ind};
	       searched[1-v][i][ind] = true;
	       q.push(tmp);
	    }
	 } else {
	    ind = s[v][w].length()+val;
	    if(!searched[v][w][ind]){
	       tri tmp = {v,w,ind};
	       searched[v][w][ind] = true;
	       q.push(tmp);
	    }	    
	 }
	nextI:;
      }
   }
   return false;
}

int main(){
   int N[2];
   while(cin >> N[0] >> N[1])
      cout << (do_case(N) ? 'S' : 'N') << endl;
   return 0;
}
