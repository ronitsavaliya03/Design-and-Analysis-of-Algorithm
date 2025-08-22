#include<stdio.h>
  #define SIZE 7

int queue[SIZE];
int front = -1, rear = -1;

void enqueue(int val) {
    if (rear == SIZE - 1)
        printf("Queue Overflow\n");
    else {
        if (front == -1)
            front = 0;
        rear++;
        queue[rear] = val;
    }
}

int dequeue() {
    if (front == -1 || front > rear){
        printf("Queue Underflow\n");
        return -1;
    }
    else {
        front++;

        return queue[front-1];
    }
}

void bfs(int graph[7][7], int start) {
    int visited[7] = {0};
    enqueue(start);
    visited[start] = 1;

    while (front != -1 && front <= rear) {
        int current = dequeue();
        printf("%d ", current+1);

        for (int i = 0; i < 7; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int graph[7][7] = {
        {0, 1, 0, 1, 0, 0, 0},
        {1, 0, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0},
        {1, 1, 0, 0, 1, 0, 1},
        {0, 1, 1, 1, 0, 1, 1},
        {0, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 1, 1, 0}
    };

    printf("BFS Traversal starting from vertex %d:\n", 1);
    bfs(graph, 0);

    return 0;
}