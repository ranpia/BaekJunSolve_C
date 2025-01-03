#include <stdio.h>
#include <stdlib.h>

int makeBracket(int **bracket, int *teamM, int *teamN, int n, int m)
{
    for (int x=0;x < n;x++)
    {
        for (int y=0; y < m;y++)
        {
            if (teamN[x] > 0 && teamM[y] > 0)
            {
                bracket[x][y] += 1;
                teamN[x]--;
                teamM[y]--;
                if (teamN[x]<0||teamM[y]<0)
                    return -1;
            }
        }
    }
    return 0;
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    int *teamN = (int *)malloc(sizeof(int) * N);
    int *teamM = (int *)malloc(sizeof(int) * M);
    int **bracket = (int **)malloc(sizeof(int *) * N); // 대진표
    for (int i = 0; i < M; i++)
    {
        bracket[i] = (int *)malloc(sizeof(int) * M);
    }

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &teamN[i]);
    }
    for (int j = 0; j < M; j++)
    {
        scanf("%d", &teamM[j]);
    }

    // 대진표 초기화
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            bracket[i][j] = 0;
        }
    }

    int result = makeBracket(bracket, teamM, teamN, N, M);

    if (result == 0)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                printf("%d", bracket[i][j]);
            }
            printf("\n");
        }
    }
    else {
        printf("%d", result);
    }

    //print team
    for (int i = 0; i < N; i++)
    {
        printf("%d ",teamN[i]);
    }
    for (int i = 0; i < N; i++)
    {
        printf("%d ",teamM[i]);
    }


    free(teamM);
    free(teamN);
    for (int i = 0; i < N; i++)
    {
        free(bracket[i]);
    }
    free(bracket);
}
