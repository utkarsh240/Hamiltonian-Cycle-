#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define V 9

int graph[V][V] = {
    {0, 4, 0, 0, 0, 0, 0, 8, 0},
    {4, 0, 8, 0, 0, 0, 0, 11, 0},
    {0, 8, 0, 7, 0, 4, 0, 0, 2},
    {0, 0, 7, 0, 9, 14, 0, 0, 0},
    {0, 0, 0, 9, 0, 10, 0, 0, 0},
    {0, 0, 4, 14, 10, 0, 2, 0, 0},
    {0, 0, 0, 0, 0, 2, 0, 1, 6},
    {8, 11, 0, 0, 0, 0, 1, 0, 7},
    {0, 0, 2, 0, 0, 0, 6, 7, 0}
};

bool isSafe(int v, bool visited[], int path[], int pos, int k)
{
    if (graph[path[pos-1]][v] == 0)
        return false;
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;
    return (visited[v] == false && graph[path[pos-1]][v] <= k);
}

bool hamCycleUtil(int path[], bool visited[], int pos, int k)
{
    if (pos == V)
    {
        if (graph[path[pos-1]][path[0]] <= k)
            return true;
        else
            return false;
    }
    for (int v = 1; v < V; v++)
    {
        if (isSafe(v, visited, path, pos, k))
        {
            path[pos] = v;
            visited[v] = true;
            if (hamCycleUtil(path, visited, pos+1, k) == true)
                return true;
            visited[v] = false;
        }
    }
    return false;
}

bool hamCycle(int k)
{
    int *path = (int *)malloc(sizeof(int)*V);
    for (int i = 0; i < V; i++)
        path[i] = -1;
    bool *visited = (bool *)malloc(sizeof(bool)*V);
    for (int i = 0; i < V; i++)
        visited[i] = false;
    path[0] = 0;
    visited[0] = true;
    if ( hamCycleUtil(path, visited, 1, k) == false )
    {
        printf("Solution does not exist for k = %d ", k);
        return false;
    }
    printSolution(path);
    return true;
}

void printSolution(int path[])
{
    printf ("Solution Exists: Following is one Hamiltonian Cycle \n");
    for (int i = 0; i < V; i++)
        printf(" %d ", path[i]);
    printf(" %d ", path[0]);
    printf(" ");
}

int main()
{
    int k = 58;
    hamCycle(k);
    return 0;
}
