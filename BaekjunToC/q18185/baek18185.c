#include <stdio.h>
#include <stdlib.h>

/* 해결못한것들
4
1 2 1 1

생각되는 해결 방안: 메모이제이션 활용?
라면을 연달아 사는 경우 안사는 경우를 나누어 계산
이를 메모이제이션으로 저장 후 비교분석
현재 구현방식: 3개를 처음부터 사기

or 3개 연달아 사는 걸 i가 1부터 시작하지 않기
문제: 다시 i가 0일때 탐색을 못할 수도?

비용 7과 비용 3을 연산하는 1 2 1의 경우
비용 5를 두번하는 연산과 비용이 같음
1 2 1을 7의 비용으로 하는 방법과 5의 비용으로 하는 방법으로 나누어 생각
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