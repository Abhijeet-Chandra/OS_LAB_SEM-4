#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void calculateNeed(int n, int m, int max[][MAX], int alloc[][MAX], int need[][MAX])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

void printMatrix(int n, int m, int mat[][MAX])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int isSafe(int n, int m, int alloc[][MAX], int need[][MAX], int safeSeq[], int avail[])
{
    int work[MAX], finish[MAX];

    for (int i = 0; i < m; i++)
    {
        work[i] = avail[i];
    }

    for (int i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        break;
                    }
                }

                if (j == m)
                {
                    for (int k = 0; k < m; k++)
                    {
                        work[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
        {
            return 0;
        }
    }
    return 1;
}

void requestResources(int n, int m, int alloc[][MAX], int need[][MAX], int avail[])
{
    int process;
    printf("\nEnter process number: ");
    scanf("%d", &process);

    int request[MAX];
    printf("Enter request vector: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &request[i]);
    }

    // request i <= need i
    for (int i = 0; i < m; i++)
    {
        if (request[i] > need[process][i])
        {
            printf("\nError: Request exceeds Need\n");
            return;
        }
    }

    // request i <= available i
    for (int i = 0; i < m; i++)
    {
        if (request[i] > avail[i])
        {
            printf("\nError: Request exceeds available\n");
            return;
        }
    }

    // temporary allocation:
    for (int i = 0; i < m; i++)
    {
        need[process][i] -= request[i];
        avail[i] -= request[i];
        alloc[process][i] += request[i];
    }

    int safeSeq[MAX];

    if (isSafe(n, m, alloc, need, safeSeq, avail))
    {
        printf("\nRequest Granted\nSafe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safeSeq[i]);
    }
    else
    {
        printf("\nRequest Denied (unsafe)\n");
        for (int i = 0; i < m; i++)
        {
            need[process][i] += request[i];
            avail[i] += request[i];
            alloc[process][i] -= request[i];
        }
    }
}

int main(){
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    printf("Enter the number of resources: ");
    scanf("%d",&m);

    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX], avail[MAX];

    printf("\nEnter Allocation matrix:\n");
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Max matrix:\n");
    for(int i = 0; i<n; i++)
        for(int j = 0; j<m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available resources:\n");
    for(int i = 0; i<m; i++)
        scanf("%d", &avail[i]);

    //part a:
    calculateNeed(n,m,max,alloc,need);

    printf("\nNeed Matrix:\n");
    printMatrix(n,m,need);

    //part b:
    int safeSeq[MAX];
    if(isSafe(n,m,alloc,need,safeSeq,avail)){
        printf("\nSystem is in safe state, safe sequence: ");
        for(int i = 0; i<n; i++)
            printf("P%d ",safeSeq[i]);
    }
    else{
        printf("\nSystem is not safe\n");
        return 0;
    }

    // part c,d,e

    char ch;
    do
    {
        requestResources(n,m,alloc,need,avail);
        printf("\nDo you want to enter another request? (y/n): ");
        scanf(" %c", &ch);
    } while (ch == 'y' || ch == 'Y');
    
    return 0;
}