#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#define true 0
void freeGraph(pnode *head)
{
  if (head == NULL){
    free(head);
    return;
  }
  pnode h = *head;
  pnode *n = head;
  pedge *ed;
  while (h)
  {
    edge *e = (*n)->edges;
    ed = &((*n)->edges);
    while (e)
    {
      *ed = e->next;
      
      free(e);
      e = *ed;
    }
    *n = h->next;
     free(h);
    h = *n;
  }
}
int main()
{
  char ans1;
  pnode head=NULL;
  while (scanf("%c", &ans1) != EOF)
  {
    if (ans1 == 'A')
    {
      freeGraph(&head);
      head = (struct GRAPH_NODE_ *)malloc(sizeof(struct GRAPH_NODE_));
      build_graph_cmd(&head);
    }
    if (ans1 == 'B')
    {
      insert_node_cmd(&head);
    }
    if (ans1 == 'D')
    {
      delete_node_cmd(&head);
    }
    if (ans1 == 'S')
    {
      printf("Dijsktra shortest path: ");
      shortsPath_cmd(head);
      printf("\n");
    }
    if (ans1 == 'T')
    {
      printf("TSP shortest path: ");
      TSP_cmd(head);
      printf("\n");
    }
  }
   freeGraph(&head);
  return 0;
}