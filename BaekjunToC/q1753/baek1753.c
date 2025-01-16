#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTEX 20000
#define MAX_EDGE 300000

// bfs 탐색으로 다익스트라 알고리즘 진행 -> 이거 출력 초과 뜸뜸
// + 수정사항 : 우선순위 큐로 구현한 뒤 다익스트라 구성 

typedef struct
{
    int arr[MAX_VERTEX];
    int rear;
    int front;
} Queue;

void init_Queue(Queue *q)
{
    q->rear = -1;
    q->front = 0;
    for (int i = 0; i < MAX_VERTEX; i++)
    {
        q->arr[i] = 0;
    }
}

int sizeof_queue(Queue *q)
{
    int size = q->rear - (q->front) + 1;
    if (size <= -1)
    {
        return 0;
    }
    return size;
}

void insert_queue(Queue *q, int insertNum)
{
    if ((q->rear) < MAX_VERTEX)
    {
        q->arr[++(q->rear)] = insertNum;
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
        int num = q->arr[q->front++];
        return num;
    }
    else
    {
        init_Queue(q);
        return -1;
    }
}

typedef struct Node
{
    int vertex;
    int weight;
    struct Node *next;

} Node;

void printList(Node *adjList[], int N)
{
    for (int i = 1; i <= N; i++)
    {
        printf("%d: ", i);
        Node *temp = adjList[i];
        while (temp)
        {
            printf("(%d, %d) ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("\n");
}

void djikstra(Node *adjList[MAX_VERTEX + 1], int startVertex, int vertexNum)
{
    Queue *que = (Queue *)malloc(sizeof(Queue));
    int weight[vertexNum];
    for (int i=0; i<vertexNum;i++){
        weight[i]=INT_MAX;
    }
    weight[startVertex-1] = 0;
    init_Queue(que);
    insert_queue(que, startVertex);
    while (sizeof_queue(que) > 0)
    {
        int searchVertex = pop_queue(que);
        Node *search = adjList[searchVertex];
        // printf("%d ", searchVertex);
        while (search)
        {
            insert_queue(que, search->vertex);
            // printf("node->vertex:%d ", search->vertex);
            if (search->weight!=0)
                weight[search->vertex - 1] =weight[searchVertex-1] + search->weight < weight[search->vertex - 1] ?weight[searchVertex-1]+ search->weight : weight[search->vertex - 1];
            search = search->next;
        }
    }
    // printf("weight : ");
    for (int i = 0; i < vertexNum; i++)
    {
        if (weight[i]!=INT_MAX)
            printf("%d\n", weight[i]);
        else
            printf("INF\n");
    }
}

int main()
{
    int v, e, startVertex;
    scanf("%d %d", &v, &e);
    scanf("%d", &startVertex);

    Node *adjList[MAX_VERTEX + 1] = {NULL};

    int v1, v2, w;
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d %d", &v1, &v2, &w);
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->vertex = v2;
        newNode->weight = w;
        newNode->next = adjList[v1];
        adjList[v1] = newNode;
    }

    // printList(adjList, v);
    djikstra(adjList, startVertex, v);

    for (int i = 1; i <= v; i++)
    {
        Node *temp = adjList[i];
        while (temp)
        {
            Node *toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
}