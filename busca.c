#include <stdio.h>
#include <stdlib.h>

// Estrutura de uma lista de adjacências
typedef struct Node {
    int cidade;
    struct Node* prox;
} Node;

// jlndvl

typedef struct {
    int numCidades;
    Node** listaAdj;
} Grafo;

// Função para criar um grafo
Grafo* criarGrafo(int numCidades) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numCidades = numCidades;
    grafo->listaAdj = (Node**)malloc(numCidades * sizeof(Node*));
    for (int i = 0; i < numCidades; i++) {
        grafo->listaAdj[i] = NULL;
    }
    return grafo;
}

// Função para criar um nó
Node* criarNode(int cidade) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    novoNode->cidade = cidade;
    novoNode->prox = NULL;
    return novoNode;
}

// Adicionar conexão (aresta)
void adicionarAresta(Grafo* grafo, int origem, int destino) {
    Node* novoNode = criarNode(destino);
    novoNode->prox = grafo->listaAdj[origem];
    grafo->listaAdj[origem] = novoNode;
}

// Remover conexão (aresta)
void removerAresta(Grafo* grafo, int origem, int destino) {
    Node* atual = grafo->listaAdj[origem];
    Node* anterior = NULL;

    while (atual != NULL && atual->cidade != destino) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL) {
        if (anterior == NULL) {
            grafo->listaAdj[origem] = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }
        free(atual);
    }
}

// DFS (Busca em Profundidade)
void dfsRecursivo(Grafo* grafo, int cidade, int* visitado) {
    visitado[cidade] = 1;
    printf("%d ", cidade);

    Node* adj = grafo->listaAdj[cidade];
    while (adj != NULL) {
        if (!visitado[adj->cidade]) {
            dfsRecursivo(grafo, adj->cidade, visitado);
        }
        adj = adj->prox;
    }
}

void dfs(Grafo* grafo, int cidadeInicial) {
    int* visitado = (int*)calloc(grafo->numCidades, sizeof(int));
    printf("DFS a partir da cidade %d: ", cidadeInicial);
    dfsRecursivo(grafo, cidadeInicial, visitado);
    printf("\n");
    free(visitado);
}

// BFS (Busca em Largura)
void bfs(Grafo* grafo, int cidadeInicial) {
    int* visitado = (int*)calloc(grafo->numCidades, sizeof(int));
    int* fila = (int*)malloc(grafo->numCidades * sizeof(int));
    int inicio = 0, fim = 0;

    fila[fim++] = cidadeInicial;
    visitado[cidadeInicial] = 1;

    printf("BFS a partir da cidade %d: ", cidadeInicial);
    while (inicio < fim) {
        int cidade = fila[inicio++];
        printf("%d ", cidade);

        Node* adj = grafo->listaAdj[cidade];
        while (adj != NULL) {
            if (!visitado[adj->cidade]) {
                fila[fim++] = adj->cidade;
                visitado[adj->cidade] = 1;
            }
            adj = adj->prox;
        }
    }
    printf("\n");

    free(visitado);
    free(fila);
}

// Imprimir o grafo
void imprimirGrafo(Grafo* grafo) {
    printf("Grafo:\n");
    for (int i = 0; i < grafo->numCidades; i++) {
        printf("%d -> ", i);
        Node* adj = grafo->listaAdj[i];
        while (adj != NULL) {
            printf("%d ", adj->cidade);
            adj = adj->prox;
        }
        printf("\n");
    }
}

// Liberar memória do grafo
void liberarGrafo(Grafo* grafo) {
    for (int i = 0; i < grafo->numCidades; i++) {
        Node* atual = grafo->listaAdj[i];
        while (atual != NULL) {
            Node* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(grafo->listaAdj);
    free(grafo);
}

// Menu interativo
void menu() {
    int numCidades, escolha, origem, destino, cidadeInicial;
    printf("Digite o numero de cidades no grafo: ");
    scanf("%d", &numCidades);

    Grafo* grafo = criarGrafo(numCidades);

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar conexao\n");
        printf("2. Remover conexao\n");
        printf("3. Imprimir grafo\n");
        printf("4. Buscar com DFS\n");
        printf("5. Buscar com BFS\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("Digite origem e destino: ");
                scanf("%d %d", &origem, &destino);
                adicionarAresta(grafo, origem, destino);
                break;
            case 2:
                printf("Digite origem e destino para remover: ");
                scanf("%d %d", &origem, &destino);
                removerAresta(grafo, origem, destino);
                break;
            case 3:
                imprimirGrafo(grafo);
                break;
            case 4:
                printf("Digite a cidade inicial para DFS: ");
                scanf("%d", &cidadeInicial);
                dfs(grafo, cidadeInicial);
                break;
            case 5:
                printf("Digite a cidade inicial para BFS: ");
                scanf("%d", &cidadeInicial);
                bfs(grafo, cidadeInicial);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (escolha != 6);

    liberarGrafo(grafo);
}

int main() {
    menu();
    return 0;
}