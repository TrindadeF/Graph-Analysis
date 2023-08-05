#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 4
#define INFINITY 999999

// Estrutura para representar uma aresta do grafo
struct Edge {
    int source;
    int destination;
    int weight;
};

// Função para encontrar o nó com a distância mínima não processada
int findMinDistance(int dist[], bool processed[]) {
    int minDistance = INFINITY;
    int minNode;

    for (int node = 0; node < MAX_NODES; node++) {
        if (!processed[node] && dist[node] <= minDistance) {
            minDistance = dist[node];
            minNode = node;
        }
    }

    return minNode;
}

// Função para imprimir o caminho mais eficiente do nó inicial até o nó destino
void printPath(int parent[], int node) {
    if (parent[node] == -1)
        return;

    printPath(parent, parent[node]);
    printf(" -> %d", node + 1);
}

// Função para implementar o algoritmo de Dijkstra
void dijkstra(int graph[MAX_NODES][MAX_NODES], int startNode, int destination) {
    int dist[MAX_NODES]; // Vetor para armazenar as distâncias mínimas do nó inicial a todos os outros nós
    bool processed[MAX_NODES]; // Vetor para rastrear nós processados
    int parent[MAX_NODES]; // Vetor para rastrear o caminho mais eficiente

    // Inicializa o vetor de distâncias e processados
    for (int i = 0; i < MAX_NODES; i++) {
        dist[i] = INFINITY;
        processed[i] = false;
        parent[i] = -1;
    }

    // A distância do nó inicial para ele mesmo é sempre 0
    dist[startNode] = 0;

    // Loop para encontrar o caminho mais eficiente para todos os nós
    for (int count = 0; count < MAX_NODES - 1; count++) {
        int u = findMinDistance(dist, processed);

        processed[u] = true;

        for (int v = 0; v < MAX_NODES; v++) {
            if (!processed[v] && graph[u][v] && dist[u] != INFINITY && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Caminho mais eficiente de %d para %d: ", startNode + 1 , destination + 1 );
    printf("%d", startNode + 1);
    printPath(parent, destination);
    printf("\nTempo total: %d minutos\n", dist[destination]);
}

int main() {
    int graph[MAX_NODES][MAX_NODES] = {
        {0, 10, 8, 17},
        {10, 0, 1, 5},
        {8, 1, 0, 15},
        {17, 5, 15, 0}
    };

    int startNode = 0; // Nó inicial (1)
    int destination = 3; // Nó destino (4)

    dijkstra(graph, startNode, destination);

    return 0;
}

