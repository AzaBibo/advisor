#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

void myTreePrint(tree_node * t){
   for(int i = tree_node_depth(t); i > 0; i--){
      printf("    ");
      tree_node * sibling = t;
      for(int j = i-1; j>0; j--){
         sibling = sibling->parent;
      }
      if (sibling->next != 0x0 && i != 1) printf("|");
   }
    if(t->parent != NULL) printf("+");

   if(tree_node_depth(t) > 1) printf("--");
   printf("%s\n", t->elem) ;
   
   if (t->child == NULL)
      return ;
   
   for (tree_node * i = t->child ; i != NULL ; i = i->next) {
      myTreePrint(i) ;
   }
}

int main() {
    int N, R;
    scanf("%d %d", &N, &R) ; // reads number of Names and number of Relations

    tree_node ** nodes = malloc(N * sizeof(tree_node*)); //allocating tree_node array

    for (int i = 0 ; i < N ; i++) { //initializing each element of "nodes" array
        nodes[i] = malloc(sizeof(tree_node));
        nodes[i]->elem = malloc(10 * sizeof(char));
        nodes[i]->parent = NULL;
        nodes[i]->next = NULL;
        nodes[i]->child = NULL;
    }

    int name_index = 0;
    char **relations = malloc(R * sizeof(char*));
    for(int i = 0; i < R; i++) { //initializing each element of "relations" array
        relations[i] = malloc(20 * sizeof(char*)); // Allocate memory for up to 20 characters per relation
    }

    for(int i = 0; i < R; i++) {
        scanf(" %[^\n]", relations[i]); // read entire line of input and store it to "relations" array
        char *name1 = malloc(10 * sizeof(char));
        char *name2 = malloc(10 * sizeof(char));    
        name1[0] = '\0';
        name2[0] = '\0';
        sscanf(relations[i], "%s %s", name1, name2);  //separate a "relation" into 2 names
        

        // Check if name1 is already in the list
        int found1 = 0;
        for(int j = 0; j < N; j++) {
            if(strcmp(nodes[j]->elem, name1) == 0) {
                found1 = 1;
                break;
            }
        }
        // If name1 is not in the list, add it
        if(!found1) {
            strcpy(nodes[name_index]->elem, name1);
            name_index++;
        }

        // Check if name2 is already in the list
        int found2 = 0;
        for(int k = 0; k < N; k++) {
            if(strcmp(nodes[k]->elem, name2) == 0) {
                found2 = 1;
                break;
            }
        }
        // If name2 is not in the list, add it
        if(!found2) {
            strcpy(nodes[name_index]->elem,name2);
            name_index++;
        }

        free(name1); //freeing names
        free(name2);
    }

    for(int j = 0; j < R; j++) { //iterates through "relations" array , and gets two names
        char first[10], second[10];
        sscanf(relations[j], "%s %s", first, second);

        int f, s;
        for(f = 0; f < N; f++) { //finds first name in "nodes" array
            if(strcmp(first, nodes[f]->elem) == 0) {
                break;
            }
        }
        
        for(s = 0; s < N; s++) { //finds second name in "nodes" array
            if(strcmp(second, nodes[s]->elem) == 0) {
                break;
            }
        }

        tree_child_add(nodes[f], nodes[s]);  //makes a connection between two tree_nodes
    }

    tree_node * root = tree_alloc("");  //create a root array (a.k.a the the first array in the tree)
    for(int i = 0; i < N; i++) { 
        if(nodes[i]->parent == 0x0) {  //find tree_nodes in "nodes" array that do not have a parent and make them "root" 's children
            //myTreePrint(nodes[i]);
            tree_child_add(root, nodes[i]);
        }
    }

    myTreePrint(root); printf("\n");  //print the tree
    
    //freeing what we haven't freed
    for (int i = 0 ; i < N ; i++) {
        free(nodes[i]->elem);
        free(nodes[i]);
    }

    free(nodes);

    for(int i = 0; i < R; i++) {
        free(relations[i]);
    }

    free(relations);
}