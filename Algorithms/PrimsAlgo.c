#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define V 7

int main(){
    int graph[V][V] = {
        {0, 1, 0, 4, 0, 0, 0},
        {1, 0, 2, 6, 4, 0, 0},
        {0, 2, 0, 0, 5, 6, 0},
        {4, 6, 0, 0, 3, 0, 4},
        {0, 4, 5, 3, 0, 8, 7},
        {0, 0, 6, 0, 8, 0, 3},
        {0, 0, 0, 4, 7, 3, 0}
    };

    int visited[V] = {0};
    visited[0] = 1;
    int edges = 0;
    int minCost = 0;

    while (edges < V - 1) {
        int min = INT_MAX;
        int a = -1, b = -1;

        for (int i = 0; i < V; i++) {
            if (visited[i]) {
                for (int j = 0; j < V; j++) {
                    if (!visited[j] && graph[i][j] && graph[i][j] < min) {
                        min = graph[i][j];
                        a = i;
                        b = j;
                    }
                }
            } 
        }

        visited[b] = 1;
        edges++;
        minCost += min;
        printf("Edge: %d - %d, Weight: %d\n", a, b, min);
    }

    printf("Minimum Cost: %d\n", minCost);
}