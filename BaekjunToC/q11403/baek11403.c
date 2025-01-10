#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 100

void findDirection(int adj_mat[MAX_VERTEX][MAX_VERTEX], int vertexNum)
{
    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
                for (int k = 0; k < vertexNum; k++)
                {
                    if (adj_mat[j][k]+adj_mat[k][i]>1)
                    {
                        adj_mat[j][i]=1;
                    }
                    else if (adj_mat[j][i]+adj_mat[i][k]>1){
                        adj_mat[j][k]=1;
                    }
                }
        }
    }
}

int main()
{
    int vertexNum;
    int adj_mat[MAX_VERTEX][MAX_VERTEX];
    scanf("%d", &vertexNum);

    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            scanf("%d", &adj_mat[i][j]);
        }
    }
    findDirection(adj_mat, vertexNum);

    for (int i = 0; i < vertexNum; i++)
    {
        for (int j = 0; j < vertexNum; j++)
        {
            printf("%d ", adj_mat[i][j]);
        }
        printf("\n");
    }
}