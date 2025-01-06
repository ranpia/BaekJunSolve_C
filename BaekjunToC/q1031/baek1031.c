#include <stdio.h>
#include <stdlib.h>

// 팀에서 대진횟수가 큰 사람부터 대진을 짜야함
// 순차 탐색으로 찾은 후에 대진표 만들기
// + 사전순 확인하기 
// 결국 그래프 형태로 해서 간선으로 풀어야 될듯
// 대전을 결정하는 알고리즘에서 사전순으로 배열까지 생각해야됨
// 왜냐면 대전순서가 망가짐

int makeBracket(int **bracket, int *teamM, int *teamN, int n, int m, int *x, int *y)
{
    int i = 0;
    while (i < n)
    {
        for (int j = 0; j < m; j++)
        {
            // 종료 조건
            if (bracket[x[i]][y[j]] >= 2)
            {
                return -1;
                break;
            }
            if (teamN[x[i]] >= 1 && teamM[y[j]] >= 1)
            {
                bracket[x[i]][y[j]] += 1;
                teamN[x[i]]--;
                teamM[y[j]]--;
            }
        }
        if (teamN[x[i]] >= 1)
        {
            return -1;
        }
        else
            i++;
    }
    for (int j = 0; j < m; j++)
    {
        if (teamM[y[j]] > 0)
        {
            return -1;
        }
    }

    return 0;
}

void searchLarge(int *team, int length, int *k)
{
    int tmp = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = i; j < length; j++)
        {
            if (team[k[i]] < team[k[j]])
            {
                tmp = k[i];
                k[i] = k[j];
                k[j] = tmp;
            }
        }
    }
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    int *teamN = (int *)malloc(sizeof(int) * N); // 팀 N 배열
    int *teamM = (int *)malloc(sizeof(int) * M); // 팀 M 배열
    int *x = (int *)malloc(sizeof(int) * N); // 팀 N 오름차순 인덱스 배열
    int *y = (int *)malloc(sizeof(int) * M); // 팀 M 오름차순 인덱스 배열
    int **bracket = (int **)malloc(sizeof(int *) * N); // 대진표
    for (int i = 0; i < N; i++)
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

    // 대진표 + 크기 비교 배열 초기화
    for (int i = 0; i < N; i++)
    {
        x[i] = i;
        for (int j = 0; j < M; j++)
        {
            y[j] = j;
            bracket[i][j] = 0;
        }
    }
    searchLarge(teamN, N, x);
    searchLarge(teamM, M, y);
    int result = makeBracket(bracket, teamM, teamN, N, M, x, y);

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
    else
    {
        printf("%d\n", result);
    }

    /* print team
    for (int i = 0; i < N; i++)
    {
        printf("%d ", teamN[i]);
    }
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", teamM[i]);
    }*/

    free(teamM);
    free(teamN);
    free(x);
    free(y);
    for (int i = 0; i < N; i++)
    {
        free(bracket[i]);
    }
    free(bracket);
}
