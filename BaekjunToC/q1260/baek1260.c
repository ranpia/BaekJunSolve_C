#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_EDGE 10000
#define MAX_VERTEX 1000

typedef struct
{
    int n;
    int adg_mat[MAX_VERTEX][MAX_VERTEX];
    int visit[MAX_VERTEX];
} Graph;

void init_Graph(Graph *g)
{
    g->n = 0;
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        g->visit[i] = false;
        for (int j = 0; j < MAX_VERTEX; j++)
        {
            g->adg_mat[i][j] = 0;
        }
    }
}

void insert_Vertex(Graph *g, int vertex)
{
    if (g->n >= MAX_VERTEX - 1)
    {
        printf("overflow");
    }
    else
    {
        g->n = vertex;
    }
}

void insert_Edge(Graph *g, int v1, int v2)
{
    if (v1 <= g->n && v2 <= g->n)
    {
        g->adg_mat[v1 - 1][v2 - 1] += 1;
        g->adg_mat[v2 - 1][v1 - 1] += 1;
    }
}

// 스택
typedef struct
{
    int arr[MAX_VERTEX];
    int top;
} Stack;

void Init_Stack(Stack *stack)
{
    stack->top = -1;
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        stack->arr[i] = 0;
    }
}

void insert_Stack(Stack *stack, int insertNum)
{
    if (stack->top < MAX_VERTEX)
    {
        stack->arr[++stack->top] = insertNum;
    }
    else
    {
        printf("cannot insert");
    }
}

int pop_Stack(Stack *stack)
{
    if (stack->top >= 0)
    {
        int output = stack->arr[stack->top];
        stack->arr[stack->top--] = 0;
        return output;
    }
    return -1;
}

int sizeof_Stack(Stack *stack)
{
    if (stack->top < 0)
    {
        return -1;
    }
    else
    {
        return stack->top + 1;
    }
}

void print_stack(Stack *s)
{
    int size = sizeof_Stack(s);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", s->arr[i]);
    }
}

void DFS(Graph *graph, Stack *stack, int current_vertex, int vertexNum, int *dfs)
{
    graph->visit[current_vertex - 1] += 1;
    insert_Stack(stack, current_vertex);
    int i = 0;
    while (i < vertexNum)
    {
        if (graph->adg_mat[current_vertex - 1][i] == 1 && graph->visit[i] == false)
        {
            DFS(graph, stack, i + 1, vertexNum, dfs);
        }
        else
        {
            i++;
        }
    }
    int k=sizeof_Stack(stack);
    dfs[k-1] = pop_Stack(stack);
}

int main()
{
    int vertexNum, edge, first_v;
    int dfs[MAX_VERTEX], bfs[MAX_VERTEX]; //
    int v1, v2;                           // 간선 입력
    for (int i=0; i<MAX_VERTEX;i++){
        dfs[i]=0;
        bfs[i]=0;
    }

    Graph *g;
    g = (Graph *)malloc(sizeof(Graph));
    Stack *s;
    s = (Stack *)malloc(sizeof(Stack));

    init_Graph(g);
    Init_Stack(s);

    scanf("%d %d %d", &vertexNum, &edge, &first_v);
    insert_Vertex(g, vertexNum);

    for (int i = 0; i < edge; i++)
    {
        scanf("%d %d", &v1, &v2);
        insert_Edge(g, v1, v2);
    }

    DFS(g, s, first_v, vertexNum, dfs);
    for (int i = 0; i < vertexNum; i++)
    {
        printf("%d ",dfs[i]);
    }

    free(s);
    free(g);
}