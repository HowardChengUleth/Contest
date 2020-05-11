/* @JUDGE_ID: 1102NT 153 C "Recursive computation" */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int hist[26];

int gcd(int a, int b)
{
   int r;

   while (b) {
      r = a % b;
      a = b;
      b = r;
   }
   assert(a >= 0);
   return a;
}

int mult(int *A, int n, int *B, int m)
{
   int i, j;
   int prod, d;

   for (i = 0; i < n; i++) {
      for (j = 0; j < m; j++) {
         d = gcd(A[i], B[j]);
         A[i] /= d;
         B[j] /= d;
      }
   }
   prod = 1;
   for (i = 0; i < n; i++) {
      prod *= A[i];
   }
   for (j = 0; j < m; j++) {
      assert(B[j] == 1);
   }
   return prod;
}

int calc(void)
{
   int total = 0;
   int A[100], B[2000];
   int n, m, i, j;

   n = m = 0;
   for (i = 0; i < 26; i++) {
      total += hist[i];
   }
   for (i = 1; i <= total; i++) {
      A[i-1] = i;
   }
   n = total;

   for (i = 0; i < 26; i++) {
      for (j = 1; j <= hist[i]; j++) {
         B[m++] = j;
      }
   }
   return mult(A, n, B, m);
}

int index(char *str)
{
   int sum;
   int i, j;

   if (strlen(str) <= 1) {
      return 1;
   }

   sum = 0;
   for (i = 0; i < *str - 'a'; i++) {
      if (hist[i] == 0) {
         continue;
      }
      hist[i]--;
      sum += calc();
      hist[i]++;
   }
   assert(hist[*str - 'a'] > 0);
   hist[*str - 'a']--;
   sum += index(str+1);
   hist[*str - 'a']++;
   return sum;
}

int do_case(void)
{
   char buffer[100];
   int i;

   fgets(buffer, 100, stdin);
   if (*buffer == '#') {
      return 0;
   }
   buffer[strlen(buffer)-1] = 0;
   for (i = 0; i < 26; i++) {
      hist[i] = 0;
   }
   for (i = 0; i < strlen(buffer); i++) {
      hist[buffer[i]-'a']++;
   }
   printf("%10d\n", index(buffer));
   return 1;
}

int main(void)
{
   while (do_case());

   return 0;
}
