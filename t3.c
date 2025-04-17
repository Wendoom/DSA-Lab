/*
The major steps of the algorithm are as follows:
Start off with all nodes being white. Initialize an empty queue.
Mark the source s as grey and enqueue it
While the queue is not empty:
    Dequeue a node u
    For each white node v adjacent to u:
        Mark v as grey
        Enqueue v
    Mark u as black
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Queue
typedef struct linked_list_node
{
    int data;
    struct linked_list_node *next;
} ll_node;

typedef struct stack
{
    ll_node *top;
} stack;

stack* get_stack()
{
    stack *S = (stack*) malloc(sizeof(stack));
    S->top = NULL;
    return S;
}

void push(stack *S, int data)
{
    ll_node *temp = (ll_node*) malloc(sizeof(ll_node));
    temp->data = data;
    temp->next = S->top;
    S->top = temp;
}

int isEmpty(stack *S)
{
    return S->top == NULL;
}

int pop(stack *S)
{
    if (isEmpty(S))
    {
        printf("Stack is empty\n");
        return -1;
    }
    ll_node *temp = S->top;
    int data = temp->data;
    S->top = S->top->next;
    free(temp);
    return data;
}


typedef enum color
{
    WHITE,
    GREY,
    BLACK
} color;

// Graph Node
typedef struct graph_node
{
    int data;
    color c;
} graph_node;

// Graph
typedef struct Graph
{
    int V;
    int E;
    int **adjacency_matrix;
    graph_node *vertices;
} Graph;

// Modify the get_graph function from Task 1 to now only use the adjacency matrix and not the adjacency list
// Allocate memory for the vertices array (Array of |V| graph_nodes)
// Initialize all the vertices to WHITE
// Initialize data to the index of the vertex

Graph *get_graph(int V, int E)
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->V = V;
    G->E = E;
    // Allocate memory for the adjacency matrix (V x V int array)
    G->adjacency_matrix=(int**) malloc(sizeof(int*)*V);
    // Allocate memory for each row of the adjacency matrix
    for (int i = 0; i < V; i++)
    {
        G->adjacency_matrix[i]=(int*) malloc(sizeof(int)*V);
        memset(G->adjacency_matrix[i], 0, sizeof(int) * V);
        
    }
    // Allocate memory for the vertices array (Array of |V| graph_nodes)
    G->vertices=(graph_node*) malloc(sizeof(graph_node)*V);

    // Initialize all the vertices to WHITE
    for(int i=0;i<V;i++){
        G->vertices[i].data=i;
        G->vertices[i].c=WHITE;
    }

    return G;
}



void dfs(Graph* G, int s){
    stack* st = get_stack();

    G->vertices[s].c = GREY;
    push(st, s);

    while(!isEmpty(st)){
        int u = pop(st);
        printf("%d ", u);

        for(int v = 0; v < G->V; v++){
            if(G->adjacency_matrix[u][v] && G->vertices[v].c == WHITE){
                G->vertices[v].c = GREY;
                push(st, v);
            }
        }
        G->vertices[u].c = BLACK;
    }
}


void add_edge_adj_matrix(Graph *G, int u, int v)
{
    G->adjacency_matrix[u][v] = 1;
}

int main()
{
    // You can change the file name to input1.txt or input2.txt to test your code for different graphs
    FILE *fp = fopen("input3.txt", "r");
    int V, E;
    fscanf(fp, "%d", &V);
    fscanf(fp, "%d", &E);
    struct Graph *G = get_graph(V, E);
    for (int i = 0; i < E; i++) 
    {
        int u, v;
        fscanf(fp, "%d %d", &u, &v);
        add_edge_adj_matrix(G, u, v);
    }
    fclose(fp);
    dfs(G, 0);

    return 0;
}