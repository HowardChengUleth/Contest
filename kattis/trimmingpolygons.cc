#include <bits/stdc++.h>

// I like using this and I use it often enough
#define FR(i, n) for (int i = 0; i < (n); ++i)
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii; 
ll x[401],y[401],c[401];
//typedef vector<int> vi;   
long long F[401][401];

long long calcTri(int a,int n,int b){
    ii l[2];
    l[0]=make_pair(x[a]-x[n],y[a]-y[n]);
    l[1]=make_pair(x[a]-x[b],y[a]-y[b]);
    return abs(l[0].first*l[1].second-l[0].second*l[1].first);
}

long long f(int a,int b){
    if(b-a==1)
      return 0;
    assert(b > a);
    long long tmp=0;
    if(F[a][b]==-1){
        for(int n=a+1;n<b;n++){
            tmp+=c[n];
        }
        for(int n=a+1;n<b;n++){
            tmp=max(tmp,f(a,n)+f(n,b)+calcTri(a,n,b));
        }
        F[a][b]=tmp;
    }
    return F[a][b];
}

int main() {
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   int n; cin>>n;
   long long total=0;
   FR(i,n){cin>>x[i]>>y[i]>>c[i];}
   FR(i,401){fill(F[i],F[i]+401,-1);}
   copy(x,x+n,x+n);
   copy(y,y+n,y+n);
   copy(c,c+n,c+n);
   FR(i,n){
       total+=c[i];
   }
   FR(i,n){
       for(int m=i+1;m<n;m++){
           total=max(f(i,m)+f(m,i+n),total);
       }
   }
   cout<<total<<endl;
}
