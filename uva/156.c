/* @JUDGE_ID: 1102NT 156 C "" */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD 1001
#define MAX_LEN 22

char dict[MAX_WORD][MAX_LEN];
char print[MAX_WORD];

int anagram(char *str1, char *str2)
{
   int n1 = strlen(str1);
   int n2 = strlen(str2);
   char count1[26], count2[26];
   int i;

   if (n1 != n2) {
      return 0;
   }
   for (i = 0; i < 26; i++) {
      count1[i] = count2[i] = 0;
   }
   for (i = 0; i < n1; i++) {
      count1[toupper(str1[i]) - 'A']++;
      count2[toupper(str2[i]) - 'A']++;
   }
   for (i = 0; i < 26; i++) {
      if (count1[i] != count2[i]) {
         return 0;
      }
   }
   return 1;
}

int main(int argc, char **argv, char **envp)
{
   int num_words = 0;
   int i, j;
   for (i = 0; i < MAX_WORD; i++) {
      print[i] = 1;
   }
   while (scanf("%s", dict[num_words]) == 1 &&
          dict[num_words][0] != '#') {
      num_words++;
   }
   qsort(dict, num_words, sizeof(char[MAX_LEN]), strcmp);
   for (i = 0; i < num_words; i++) {
      if (strlen(dict[i]) == 1) {
         continue;
      }
      for (j = i+1; j < num_words; j++) {
         if (anagram(dict[i], dict[j])) {
            print[i] = print[j] = 0;
         }
      }
   }
   for (i = 0; i < num_words; i++) {
      if (print[i]) {
         printf("%s\n", dict[i]);
      }
   }
   return 0;
}



