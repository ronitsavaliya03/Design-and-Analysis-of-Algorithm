#include<stdio.h>
#include<limits.h>

#define V 5
#define E 6

int findMinKey(int visited[], int distance[]){
    int min = INT_MAX, min_index;

    for(int v = 0; v < V; v++){
        if(!visited[v] && distance[v] < min){
            min = distance[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[V][V]){
    int distance[V];
    int visited[V];

    for(int i = 0; i < V; i++){
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[0]=0;

    for(int i=0; i<V; i++){
        int u = findMinKey(visited, distance);
        visited[u] = 1;

        for(int v=0; v<V; v++){
            if(!visited[v] && graph[u][v] && distance[u] + graph[u][v] < distance[v]){
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    for(int i=0; i<V; i++){
        printf("Distance from source to %d is %d\n", i, distance[i]);
    }
}
int main(){
    int graph[V][V] = {
        {0, 9, 75, 0, 0},
        {0, 0, 95, 0, 42},
        {0, 0, 0, 51, 0},
        {0, 19, 0, 0, 0},
        {0, 0, 0, 31, 0}
    };
    dijkstra(graph);
    return 0;
}