#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int indexOfPerson(char ** list,int listLen, char * name){
   if(listLen = 0 ){
      return -1;
   }
   for(int i = 0; list[i] != 0x0; i++){
      if(!strcmp(list[i], name)) return i;
   }
   return -1;
}

void myTreePrint(tree_node * t){
   for(int i = tree_node_depth(t); i > 0; i--){
      printf("    ");
      tree_node * sibling = t;
      for(int j = i-1; j>0; j--){
         sibling = sibling->parent;
      }
      if (sibling->next != 0x0 && i != 1) printf("|");
   }
   if(t->parent != 0x0) printf("+");
   if(tree_node_depth(t) > 1) printf("--");
   printf("%s\n", t->elem) ;
   
   if (t->child == NULL)
      return ;
   
   for (tree_node * i = t->child ; i != NULL ; i = i->next) {
      myTreePrint(i) ;
   }
}

int main ()
{
   int nPeople = 0;
   int peopleListCounter = 0;
   int nRelations = 0;
   scanf("%d %d", &nPeople, &nRelations);

   char **names = malloc(nPeople * sizeof(char*));
   tree_node ** t = malloc(sizeof(tree_node *) * nPeople);
   for(int i = 0; i < nRelations; i++){
      char name1[20] = "";
      char name2[20] = "";
      scanf("%s %s", name1, name2);
      int id1 = indexOfPerson(names, peopleListCounter, name1);
      int id2 = indexOfPerson(names, peopleListCounter, name2);
      if( id1 == -1){
         names[peopleListCounter] = malloc(20 * sizeof(char));
         strcpy(names[peopleListCounter], name1);
         t[peopleListCounter] = tree_alloc(name1);
         peopleListCounter++;
      }
      if( id2 == -1){
         names[peopleListCounter] = malloc(20 * sizeof(char));
         strcpy(names[peopleListCounter], name2);
         t[peopleListCounter] = tree_alloc(name2);
         peopleListCounter++;
      }
      id1 = indexOfPerson(names, peopleListCounter, name1);
      id2 = indexOfPerson(names, peopleListCounter, name2);
      tree_child_add(t[id1], t[id2]);
   }

   tree_node * main = tree_alloc("");
   for(int i = 0; i<nPeople; i++){
      if(t[i]->parent == 0x0) tree_child_add(main, t[i]);
   }

   myTreePrint(main);
   printf("\n");
   free(main);

   return 0;
}