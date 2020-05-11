#include <iostream>
#include <string>
#include <vector>

#define DEBUG 0

using namespace std;

int main()
{
  int t;
  cin>>t;
  for (; t > 0; t--)
  {
    int n, mx = 0;
    cin>>n;
    vector <string> v;
    for (int i = 0; i < n; i++)
    {
      string s;
      cin>>s;
      v.push_back(s);
      int s1, s2;
      s1 = v[i].length();
      for (int j = 0; j < i; j++)
      {
        s2 = v[j].length();
        for (int k = s2-1; k > -s2; k--){
          int c = 0;
          if (min(s2-k, s1) - max(-k, 0) > mx)
            for (int l = max(-k, 0); l < min(s2-k, s1); l++)
            {
              if (DEBUG)cout<<l<<k+l<<v[i][l]<<v[j][k+l]<<endl;
              if (v[i][l] == v[j][k+l]) c++;
            }
          mx = max(c,mx);
          if (DEBUG)
            cout<<"Offset:"<<k<<endl;
        }
      }
    }
    cout<<mx<<endl;
  }
}