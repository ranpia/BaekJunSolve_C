#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_EDGE 10001
#define MAX_VERTEX 1001

// bfs dfs 알고리즘은 문제없음
// 큐에서 최대 갯수 들어왔을때 문제?
/*
6 7 1
1 3
1 2
3 5
2 6
5 6
4 5
2 4

1 2 4 5 6 3   // DFS
1 2 3 4 5 6   // BFS
*/

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

void reset_visit(Graph *g)
{ // not init, graph struct must have Max vertex
    for (int i = 0; i < g->n; i++)
    {
        g->visit[i] = 0;
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

// 큐
typedef struct
{
    int arr[MAX_VERTEX];
    int rear;
    int top;
} Queue;

void init_Queue(Queue *q)
{
    q->rear = 0;
    q->top = -1;
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        q->arr[i] = 0;
    }
}

int sizeof_queue(Queue *q)
{
    int size = q->top - (q->rear) + 1;
    if (size <= -1)
    {
        return 0;
    }
    return size;
}

void insert_queue(Queue *q, int insertNum)
{
    if ((q->top) < MAX_VERTEX)
    {
        q->arr[++(q->top)] = insertNum;
    }
    else
    {
        printf("out of range, init queue");
        return;
    }
}

int pop_queue(Queue *q)
{
    if (sizeof_queue(q) > 0)
    {
        int num = q->arr[q->rear++];
        return num;
    }
    else
    {
        init_Queue(q);
        return -1;
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
}

void BFS(Graph *graph, Queue *queue, int current_vertex, int vertexNum, int *bfs)
{
    graph->visit[current_vertex - 1] += 1;
    bfs[queue->rear] = current_vertex;
    bool insert=true;
    for (int i = 0; i < vertexNum; i++)
    {
        if (graph->adg_mat[current_vertex - 1][i] == 1 && graph->visit[i] == 0)
        {
            for (int j=queue->rear; j<=queue->top;j++){
                if (queue->arr[j]==(i+1))
                    insert = false;
            }
            if (insert)
                insert_queue(queue, i + 1);
        }
    }
    for (int i = 0; i < sizeof_queue(queue); i++)
    {
        BFS(graph, queue, pop_queue(queue), vertexNum, bfs);
    }
}

int main()
{
    int vertexNum, edge, first_v;         // initial value
    int dfs[MAX_VERTEX], bfs[MAX_VERTEX]; // final results
    int v1, v2;                           // 간선 입력
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        dfs[i] = 0;
        bfs[i] = 0;
    }

    Graph *g;
    g = (Graph *)malloc(sizeof(Graph));
    Stack *s;
    s = (Stack *)malloc(sizeof(Stack));
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));

    init_Graph(g);
    Init_Stack(s);
    init_Queue(q);

    scanf("%d %d %d", &vertexNum, &edge, &first_v);
    insert_Vertex(g, vertexNum);

    for (int i = 0; i < edge; i++)
    {
        scanf("%d %d", &v1, &v2);
        insert_Edge(g, v1, v2);
    }

    DFS(g, s, first_v, vertexNum, dfs);
    for (int k=sizeof_Stack(s)-1;k>=0;k--){
        dfs[k]=pop_Stack(s);
    }
    reset_visit(g);
    BFS(g, q, first_v, vertexNum, bfs);

    for (int i = 0; dfs[i]!=0; i++)
    {
        printf("%d ", dfs[i]);
    }
    printf("\n");
    for (int i = 0; bfs[i]!=0; i++)
    {
        printf("%d ", bfs[i]);
    }

    free(s);
    free(g);
    free(q);
}