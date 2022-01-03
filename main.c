#include<stdio.h>
#include "graph.h"
#define true 0



int main(){
    char ans1;
    pnode head;
  while (scanf("%c", &ans1)!=EOF){    
 if(ans1=='A'){
     build_graph_cmd(&head);
 }
 if(ans1=='B'){
    insert_node_cmd(&head);
 }
 if(ans1=='D'){
      delete_node_cmd(&head);
 }
 if(ans1=='S'){
    printf("Dijsktra shortest path: ");
    shortsPath_cmd(head); 
     printf("\n");
 }
 if(ans1=='T'){
     printf("TSP shortest path: ");
     TSP_cmd(head); 
      printf("\n");
 }
    }

    return 0;
}
