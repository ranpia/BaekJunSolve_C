#include <stdio.h>
#include <stdlib.h>

/* 
final 해결방안
비용 7로 사는 와중에 i+1번 인덱스가 다른 인덱스보다 크다면 이는 i번째 인덱스를 비용 5로 사는 것이 이득

따로 해볼것 
- 재귀를 반복문으로 풀어보기

*/

void buyCase1(int i, int *facLoc, int facNum, int *total); // 비용 3
void buyCase2(int i, int *facLoc, int facNum, int *total); // 비용 5
void buyCase3(int i, int *facLoc, int facNum, int *total); // 비용 7

void buyCase3(int i, int *facLoc, int facNum, int *total)
{
    if (facNum <= i + 2)
    {
        buyCase2(0, facLoc, facNum, total);
        return;
    }

    if (facLoc[i] >= 1 && facLoc[i + 1] >= 1 && facLoc[i + 2] >= 1) // 라면 사는 동작
    {
        if (facLoc[i + 1] > facLoc[i + 2])
        {
            for (int j = 0; j < 2; j++)
            {
                facLoc[i + j]--;
            }
            *total += 5;
            buyCase3(i, facLoc, facNum, total);
        }
        else
        {
            for (int j = 0; j < 3; j++)
            {
                facLoc[i + j]--;
            }
            *total += 7;
            buyCase3(i, facLoc, facNum, total);
        }
    }
    else
    { // 다음 인덱스 탐색
        i++;
        buyCase3(i, facLoc, facNum, total);
    }
}

void buyCase2(int i, int *facLoc, int facNum, int *total)
{
    if (facNum <= i + 1)
    {
        buyCase1(0, facLoc, facNum, total);
        return;
    }
    if (facLoc[i] >= 1 && facLoc[i + 1] >= 1)
    {
        for (int j = 0; j < 2; j++)
        {
            facLoc[i + j]--;
        }
        *total += 5;
        buyCase2(i, facLoc, facNum, total);
    }
    else
    {
        i++;
        buyCase2(i, facLoc, facNum, total);
    }
}

void buyCase1(int i, int *facLoc, int facNum, int *total)
{
    if (facNum <= i)
    {
        return;
    }
    if (facLoc[i] >= 1)
    {
        facLoc[i]--;
        *total += 3;
        buyCase1(i, facLoc, facNum, total);
    }
    else
    {
        i++;
        buyCase1(i, facLoc, facNum, total);
    }
}

int main()
{
    int facNum = 0;
    int total = 0;
    scanf("%d", &facNum);
    int *facLoc = (int *)malloc(sizeof(int) * facNum);
    for (int i = 0; i < facNum; i++)
    {
        scanf("%d", &facLoc[i]);
    }

    buyCase3(0, facLoc, facNum, &total);
    printf("%d", total);

    free(facLoc);
}