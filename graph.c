#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"
void printGraph_cmd(pnode head)
{
    pnode h = head;
    while (h)
    {
        printf("id=%d,", h->node_num);
        pedge e = h->edges;
        while (e)
        {
            printf("e= %d\n", e->endpoint->node_num);
            e = e->next;
        }
        h = h->next;
    }

} 
node *isFound(pnode *head, int dest)
{
    node *p = *head;
    while (p != NULL)
    {
        if (p->node_num == dest)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
node *creatNode(int id)
{
    node *n = (node *)malloc(sizeof(node));
    n->node_num = id;
    n->edges = NULL;
    n->next = NULL;
    return n;
}

void build_graph_cmd(pnode *head)
{
    pnode *tempn = head;
    pedge *tempE = NULL;
    int size;
    char c;
    edge *e;
    scanf("%d", &size);
    scanf("%c", &c);
    scanf("%c", &c);
    for (int i = 0; i < size; i++)
    {
       node *n = creatNode(i);
       *tempn = n;
        tempn = &((*tempn)->next);
         free(n);
    }
    
    for (int i = 0; i < size; i++)
    {
        int id;
        scanf("%d", &id);
        scanf("%c", &c);
        node *q = isFound(head, id);
        tempE = &(q->edges);
        int w;
        int dest;
        while (scanf("%d%d", &dest, &w))
        {
            e = (edge *)malloc(sizeof(edge));
            if (e == NULL)
            {
                printf("error");
                return;
            }
            e->weight = w;
            node *p = isFound(head, dest);
            e->endpoint = p;
            *tempE = e;
            tempE = &((*tempE)->next);
            free(e);
  
        }

        if (i != size - 1)
        {
            scanf("%c", &c);
        }
    }
}
void insert_node_cmd(pnode *head)
{
    int id;
    int dest;
    int w;
    pnode *temp = head;
    scanf("%d", &id);
    node *n = isFound(head, id);
    if (n == NULL)
    {
        n = creatNode(id);
        if (*temp == NULL)
        {
            *temp = n;
        }
        else
        {
            while ((*temp)->next)
            {
                temp = &((*temp)->next);
            }
        }
        (*temp)->next = n;
    }
    else
    {
        pedge *tempE = &(n->next->edges);
        pedge t = *tempE;
        while (t)
        {
            *tempE = t->next;
            free(t);
            t = *tempE;
        }
    }
    pedge *tempE = &(n->edges);
    while (scanf("%d%d", &dest, &w))
    {
        edge *e = (edge *)malloc(sizeof(edge));
        if (e == NULL)
        {
            printf("error");
            return;
        }
        e->weight = w;
        node *p = isFound(head, dest);
        e->endpoint = p;
        *tempE = e;
        tempE = &((*tempE)->next);
    }
}

void delete_node_cmd(pnode *head)
{
    int id;
    scanf("%d", &id);
    node *n = *head;
    pnode *p = head;
    while (n)
    {
        if (n->node_num == id)
        {
            *p = n->next;
            free(n);
            return;
        }
        else
        {
            edge *e = n->edges;
            pedge *ed = &(n->edges);
            while (e)
            {
                if (e->endpoint->node_num == id)
                {
                    *ed = e->next;
                    free(e);
                    e = *ed;
                }
                else
                {
                    ed = &(e->next);
                    e = e->next;
                }
            }
            p = &(n->next);
            n = n->next;
        }
    }
}
void changeMaxVal(pnode *head)
{
    pnode p = *head;
    while (p)
    {
        p->tag = __INT_MAX__;
        p = p->next;
    }
}

void Dikstra(pnode *head, int src)
{
    changeMaxVal(head);
    pnode p = isFound(head, src);
    pedge listofedge = p->edges;
    p->tag = 0;
    while (p)
    {
        pedge q = p->edges;
        while (q)
        {
            int a = p->tag + q->weight;
            if (a < 0)
            {
                a = __INT_MAX__;
            }
            int b = q->endpoint->tag;
            if (a < b)
            {
                q->endpoint->tag = p->tag + q->weight;
                q->endpoint->parent = p;
            }
            q = q->next;
        }
        if (listofedge != NULL)
        {
            p = listofedge->endpoint;
            listofedge = listofedge->next;
        }
        else
        {
            p = p->next;
        }
    }
}

void shortsPath_cmd(pnode head)
{
    int src;
    int dest;
    scanf("%d%d", &src, &dest);
    Dikstra(&head, src);
    pnode a = isFound(&head, dest);
    if (a->tag == __INT_MAX__)
    {
        printf("-1 ");
    }
    else
    {
        printf("%d ", a->tag);
    }
}
int shortsPath(pnode head, int src, int dest)
{
    Dikstra(&head, src);
    pnode a = isFound(&head, dest);
    if (a->tag == __INT_MAX__)
    {
        return -1;
    }
    else
    {
        return a->tag;
    }
}


int sum(int *a, int (*b)[10], int size)
{
    int sum1 = 0;
    for (int i = 0; i < size - 1; i++)
    {
        if ( b[a[i]][a[i+1]]==-1 )
        {
            return __INT_MAX__;
        }
        sum1 = sum1 + b[a[i]][a[i + 1]];
        if (sum1 < 0)
            return __INT_MAX__;
    }
    return sum1;
}
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int k = 0;
int arr1[1000];
void permute(int *a, int (*b)[10], int i, int n)
{
    if (i == (n - 1))
    {
    
        arr1[k] = sum(a, b, n);
        k++;
    }
    else
    {
        for (int j = i; j < n; j++)
        {
            swap((a + i), (a + j));
            permute(a, b, i + 1, n);
            swap((a + i), (a + j));
        }
    }
}
void TSP_cmd(pnode head)
{

    k = 0;
    int num;
    int size;
    scanf("%d", &size);
    int *arr = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &num);
        arr[i] = num;
    }

    int matrix[10][10];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 0;
            }
            else
            {
                matrix[i][j] = shortsPath(head, arr[i], arr[j]);
             
            }
        }
    }
    int min = __INT_MAX__;
    int arr3[size];
    for (int r = 0; r < size; r++)
    {
        arr3[r] = r;
    }
    permute(arr3, matrix, 0, size);
    for (int t = 0; t < k; t++)
    {
        if (arr1[t] < min)
        {
            min = arr1[t];
        }
    }
 
    if (min==__INT_MAX__){
       min=-1; 
    }

    printf("%d ", min);
    free(arr);
}

