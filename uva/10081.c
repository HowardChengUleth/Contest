/* @JUDGE_ID: 1102NT 10081 C "" */

#include <stdio.h>

double x[100][10];  double s;

main(){
   int i,j,k,n;
   while (2 == scanf("%d%d",&k,&n)){
      k++;
      for (i=0;i<n;i++) for (j=0;j<k;j++) x[i][j] = 0;
      for (i=0;i<k;i++) x[0][i] = 100.0/k;
      for (i=1;i<n;i++) {
         for (j=0;j<k;j++) x[i][j] += x[i-1][j]/k;
         for (j=1;j<k;j++) x[i][j] += x[i-1][j-1]/k;
         for (j=0;j<k-1;j++) x[i][j] += x[i-1][j+1]/k;
      }
      for (s=i=0;i<k;i++) s += x[n-1][i];
      printf("%0.5lf\n",s);
   }
}
