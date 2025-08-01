#include<stdio.h>

struct Edge {
    int src, dest, weight;
};

void sortEdges(struct Edge edges[], int numEdges) {
    for (int i = 0; i < numEdges - 1; i++) {
        for (int j = 0; j < numEdges - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                struct Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

int findParent(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return findParent(parent, parent[i]);
}

void unionSets(int parent[], int x, int y) {
    int xset = findParent(parent, x);
    int yset = findParent(parent, y);
    parent[xset] = yset;
}

void kruskal(int numVertices, struct Edge edges[], int numEdges) {
    int parent[numVertices];
    for (int i = 0; i < numVertices; i++)
        parent[i] = -1;

    sortEdges(edges, numEdges);

    printf("Edges in the Minimum Spanning Tree:\n");
    int minCost = 0;
    for (int i = 0; i < numEdges; i++) {
        int x = findParent(parent, edges[i].src);
        int y = findParent(parent, edges[i].dest);

        if (x != y) {
            unionSets(parent, x, y);
            printf("Edge: %d - %d, Weight: %d\n", edges[i].src, edges[i].dest, edges[i].weight);
            minCost += edges[i].weight;
        }
    }

    printf("Minimum Cost: %d\n", minCost);
}

int main() {
    int numVertices = 7;
    struct Edge edges[] = {
        {0, 1, 1},
        {0, 3, 4},
        {1, 2, 2},
        {1, 3, 6},
        {1, 4, 4},
        {2, 4, 5},
        {2, 5, 6},
        {3, 4, 3},
        {3, 6, 4},
        {4, 5, 8},
        {4, 6, 7},
        {5, 6, 3}
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);

    kruskal(numVertices, edges, numEdges);

    return 0;
}