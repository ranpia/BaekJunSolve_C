#include <stdio.h>
#include <limits.h>

#define MAX_FRIENDS 101

void search_friends(int friendship[MAX_FRIENDS][MAX_FRIENDS], int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                if (friendship[j][i] >= 1 && friendship[i][k] >= 1 && j != k)
                    if (friendship[j][k] != 0)
                        friendship[j][k] = (friendship[j][k] < friendship[j][i] + friendship[i][k]) ? friendship[j][k] : friendship[j][i] + friendship[i][k];
                    else
                        friendship[j][k] = friendship[j][i] + friendship[i][k];
            }
        }
    }
}

void printmat(int mat[MAX_FRIENDS][MAX_FRIENDS], int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int bacconGame(int friendship[MAX_FRIENDS][MAX_FRIENDS], int N){
    int smallestbaccon = INT_MAX;
    int superinsider=0;
     for (int i = 0; i < N; i++)
    {
        int currentbaccon = 0;
        for (int j = 0; j < N; j++)
        {
            currentbaccon+=friendship[i][j];
        }
        if (smallestbaccon>currentbaccon){
            smallestbaccon = currentbaccon;
            superinsider = i+1;
        }
    }
    return superinsider;
}

int main()
{
    int N, M;
    int friendship[MAX_FRIENDS][MAX_FRIENDS] = {
        0,
    };
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++)
    {
        int start, end;
        scanf("%d %d", &start, &end);
        friendship[start - 1][end - 1] = 1;
        friendship[end - 1][start - 1] = 1;
    }
    // printmat(friendship, N);
    search_friends(friendship, N);
    // printmat(friendship, N);
    printf("%d ", bacconGame(friendship,N));
}