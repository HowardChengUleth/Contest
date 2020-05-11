// - Reduce the graph to a path between B and C.
// - Relabel A as the closest node to A on the path.
// - We are only interested in the length of the path between (A and B) and (A and C) [ bb and cc in the code ]
// - We will find the probability of returning to the position you're in now (P(x) = comeback[x])
//  - P(1) = 0
//  - P(2) = 1/2 + (1/2)^3 + (1/2)^5 + ...
//  - P(n) = sum_{k=0}^inf (P(n-1)^(k-1)) / (2^k)
//
// Then, to find out the probability of making it to the bottom, we do this:
//  - 1/2*(1-P(bb)) * sum_{k=0}^inf (1/2 * (P(bb) + P(cc)))^k

#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_N = 130;
const double EPS = 1e-8;
bool A[MAX_N][MAX_N];
int N;
double comeback[MAX_N];

bool findPath(int lvl,int v,int dest,int p,int path[],int& pathLen){
	path[lvl] = v;
	if(v == dest) { pathLen = lvl+1; return true; }
	
	for(int i=1;i<=N;i++)
		if(A[v][i] && i != p){
			if(findPath(lvl+1,i,dest,v,path,pathLen))
				return true;
		}
	return false;
}

void preCompute(){
	comeback[0] = comeback[1] = 0;
	for(int i=2;i<MAX_N;i++){
		comeback[i] = 0.5;
		double add = 0.5;
		while(add > EPS){
			add *= comeback[i-1]/2;
			comeback[i] += add;
		}
	}
}

int main(){
	preCompute();
	
	cout << setprecision(6) << fixed;
	int a,b,c,u,v,pathB[MAX_N],pathC[MAX_N],lenB,lenC;
	while(cin >> N >> a >> b >> c){
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
				A[i][j] = false;
		for(int i=0;i<N-1;i++){
			cin >> u >> v;
			A[u][v] = A[v][u] = true;
		}
		
		findPath(0,a,b,-1,pathB,lenB);
		findPath(0,a,c,-1,pathC,lenC);
		
		int same = 0;
		for(;same<min(lenB,lenC) && pathB[same] == pathC[same];same++) ;
		int bb = lenB - same;
		int cc = lenC - same;
		
		if(bb == 0 && cc != 0){
			cout << 1.0 << endl;
			continue;
		}
		if(cc == 0 && bb != 0){
			cout << 0.0 << endl;
			continue;
		}
		
		double prob = 0,add = (1 - comeback[bb])/2;
		while(add > EPS){
			prob += add;
			add *= (comeback[bb] + comeback[cc])/2;
		}
		cout << prob << endl;
	}
	return 0;
}
