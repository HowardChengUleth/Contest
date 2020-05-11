#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_PERSON 10
#define MAX_NAME   13

int num_person;
char names[MAX_PERSON][MAX_NAME];
int owe[MAX_PERSON];

int find_index(char *name)
{
   int i;
   for (i = 0; i < num_person; i++) {
     if (strcmp(names[i], name) == 0) {
         return i;
     }
   }
   assert(0);
}

int main(void)
{
   char buffer[MAX_NAME];
   int index1, index2;
   int i, j, num_give, amount;
   int group_count = 0;
   while (scanf("%d", &num_person) == 1) {
     if (group_count > 0) {
         printf("\n");
     }
      group_count++;
      for (i = 0; i < num_person; i++) {
         scanf("%s", names[i]);
         owe[i] = 0;
      }
      for (i = 0; i < num_person; i++) {
         scanf("%s", buffer);
         index1 = find_index(buffer);
         scanf("%d %d", &amount, &num_give);
         for (j = 0; j < num_give; j++) {
            scanf("%s", buffer);
            index2 = find_index(buffer);
            owe[index2] += amount / num_give;
            owe[index1] -= amount / num_give;
         }
      }
      for (i = 0; i < num_person; i++) {
         printf("%s %d\n", names[i], owe[i]);
      }
   }
   return 0;
}
