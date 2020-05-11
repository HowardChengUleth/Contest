/* @JUDGE_ID: 1102NT 140 C "" */

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

FILE *in, *out;
int num_vert;
char adj[26][26];
char vert[9];
char best[9];
int best_val;
char buff[1024];


int Compute(char *v)
{
   int i, j;
   int big = 0;
   int diff;

   for( i=0; i<num_vert-1; i++ ) {
      for( j=i+1; j<num_vert; j++ ) {
         if( adj[v[i]-'A'][v[j]-'A'] ) {
            diff = j-i;
            if( diff > big )
               big = diff;
         }
      }
   }

   return big;
}

void Permute(char *v, int n)
{
   int val, i;
   char t;

   if( n==num_vert-1 ) {
      val = Compute(v);
      if( val < best_val || (val == best_val && strcmp(v,best) < 0) ) {
         strcpy(best,v);
         best_val = val;
      }
      return;
   }

   for( i=n; i<num_vert; i++ ) {
      t = v[i];
      v[i] = v[n];
      v[n] = t;
      Permute(v,n+1);
      t = v[i];
      v[i] = v[n];
      v[n] = t;
   }
}


void InsertVert(char v)
{
   int i;
   for( i=0; i<num_vert; i++ ) {
      if( vert[i] == v )
         return;
   }
   vert[num_vert++] = v;
}

void main(void)
{
   int i, j;
   char *p;

   in = stdin;
   out = stdout;
   while( fgets(buff, 1024, in) && buff[0] != '#' ) {
      num_vert = 0;
      for( i=0; i<26; i++ ) {
         for( j=0; j<26; j++ ) {
            adj[i][j] = 0;
         }
      }

      for( p = strtok(buff,";"); p != NULL; p=strtok(NULL,";") ) {
         assert( isalpha(*p) );
         i = *p - 'A';
         InsertVert(*p);
         p+=2;
         for( ; *p != 0 && !isspace(*p); p++ ) {
            assert( isalpha(*p) );
            adj[i][*p-'A'] = 1;
            adj[*p-'A'][i] = 1;
            InsertVert(*p);
         }
      }

      strcpy(best,vert);
      best_val = Compute(vert);
      Permute(vert,0);

      for( i=0; i<num_vert; i++ ) {
         fprintf(out,"%c ",best[i]);
      }
      fprintf(out,"-> %d\n",best_val);
   }

}
