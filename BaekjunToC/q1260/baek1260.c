#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGE 10000

typedef struct
{
    int vertexNum;
    struct Vertex *connected[MAX_EDGE];
}Vertex;


int main(){
    int vertexNum, edge, first_v;
    scanf("%d %d %d", &vertexNum, &edge,&first_v);

    int v1, v2;
    for (int i=0;i<edge;i++){
        scanf("%d %d", &v1, &v2);

    }
}