#include<stdio.h>
#include<stdlib.h>

void dfsHelper(int graph[7][7], int visited[], int key){
    visited[key] = 1; 
    printf("%d ", key+1); 

    for(int i = 0; i < 7; i++){ 
        if(graph[key][i] == 1 && !visited[i]){ 
            dfsHelper(graph, visited, i); 
        }
    }
}

void dfs(int graph[7][7], int start){
    int visited[7] = {0}; 
    printf("DFS Traversal starting from vertex %d:\n", start+1);
    dfsHelper(graph, visited, start); 
    printf("\n");
}

int main(){
    int graph[7][7] = {
        {0, 1, 0, 1, 0, 0, 0},
        {1, 0, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0},
        {1, 1, 0, 0, 1, 0, 1},
        {0, 1, 1, 1, 0, 1, 1},
        {0, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 1, 0}
    };

    dfs(graph, 0);

    return 0;
}