#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*===========================================================
    STRUCTS
===========================================================*/

// Estrutura básica do item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/*===========================================================
    VARIÁVEIS GLOBAIS para contagem de comparações
===========================================================*/

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

/*===========================================================
    FUNÇÕES PARA O VETOR
===========================================================*/

// Inserir item no vetor
void inserirItemVetor(Item *vetor, int *tam, Item novo) {
    vetor[*tam] = novo;
    (*tam)++;
}

// Remover item do vetor
void removerItemVetor(Item *vetor, int *tam, char nome[]) {
    for (int i = 0; i < *tam; i++) {
        if (strcmp(vetor[i].nome, nome) == 0) {
            for (int j = i; j < *tam - 1; j++)
                vetor[j] = vetor[j+1];
            (*tam)--;
            printf("Item removido do vetor!\n");
            return;
        }
    }
    printf("Item não encontrado no vetor!\n");
}

// Listar itens do vetor
void listarVetor(Item *vetor, int tam) {
    printf("\n--- MOCHILA (VETOR) ---\n");
    for (int i = 0; i < tam; i++) {
        printf("%s | %s | qtd: %d\n",
               vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}

// Busca sequencial no vetor
int buscarSequencialVetor(Item *vetor, int tam, char nome[]) {
    comparacoesSequencial = 0;

    for (int i = 0; i < tam; i++) {
        comparacoesSequencial++;
        if (strcmp(vetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

// Selection Sort para ordenar o vetor
void ordenarVetor(Item *vetor, int tam) {
    for (int i = 0; i < tam - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < tam; j++) {
            if (strcmp(vetor[j].nome, vetor[menor].nome) < 0)
                menor = j;
        }
        if (menor != i) {
            Item tmp = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = tmp;
        }
    }
    printf("\nVetor ordenado!\n");
}

// Busca binária (somente após ordenar)
int buscarBinariaVetor(Item *vetor, int tam, char nome[]) {
    int ini = 0, fim = tam - 1;
    comparacoesBinaria = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(nome, vetor[meio].nome);

        if (cmp == 0)
            return meio;
        else if (cmp > 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    return -1;
}

/*===========================================================
    FUNÇÕES PARA LISTA ENCADEADA
===========================================================*/

// Inserir item na lista
No* inserirLista(No *lista, Item novo) {
    No *novoNo = malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = lista;
    return novoNo;
}

// Remover item da lista
No* removerLista(No *lista, char nome[]) {
    No *ant = NULL, *atual = lista;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (ant == NULL)
                lista = atual->proximo;
            else
                ant->proximo = atual->proximo;

            free(atual);
            printf("Item removido da lista!\n");
            return lista;
        }
        ant = atual;
        atual = atual->proximo;
    }

    printf("Item não encontrado na lista!\n");
    return lista;
}

// Listar itens da lista
void listarLista(No *lista) {
    printf("\n--- MOCHILA (LISTA ENCADEADA) ---\n");
    while (lista != NULL) {
        printf("%s | %s | qtd: %d\n",
               lista->dados.nome, lista->dados.tipo, lista->dados.quantidade);
        lista = lista->proximo;
    }
}

// Busca sequencial na lista
int buscarSequencialLista(No *lista, char nome[]) {
    comparacoesSequencial = 0;

    while (lista != NULL) {
        comparacoesSequencial++;
        if (strcmp(lista->dados.nome, nome) == 0)
            return 1;

        lista = lista->proximo;
    }
    return 0;
}

/*===========================================================
    FUNÇÃO PRINCIPAL - MENU
===========================================================*/

int main() {
    Item vetor[100];
    int tam = 0;

    No *lista = NULL;

    int opc, estruturaEscolhida;
    char nomeBusca[30];

    printf("Escolha a estrutura:\n1 - Vetor\n2 - Lista Encadeada\n> ");
    scanf("%d", &estruturaEscolhida);

    do {
        printf("\n=== MENU ===\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar (sequencial)\n");
        printf("5 - Ordenar vetor\n");
        printf("6 - Buscar binária (vetor)\n");
        printf("0 - Sair\n> ");
        scanf("%d", &opc);
        getchar();

        if (opc == 1) {
            Item novo;
            printf("Nome: ");
            fgets(novo.nome, 30, stdin);
            novo.nome[strcspn(novo.nome, "\n")] = 0;

            printf("Tipo: ");
            fgets(novo.tipo, 20, stdin);
            novo.tipo[strcspn(novo.tipo, "\n")] = 0;

            printf("Quantidade: ");
            scanf("%d", &novo.quantidade);
            getchar();

            if (estruturaEscolhida == 1)
                inserirItemVetor(vetor, &tam, novo);
            else
                lista = inserirLista(lista, novo);

        } else if (opc == 2) {
            printf("Nome para remover: ");
            fgets(nomeBusca, 30, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = 0;

            if (estruturaEscolhida == 1)
                removerItemVetor(vetor, &tam, nomeBusca);
            else
                lista = removerLista(lista, nomeBusca);

        } else if (opc == 3) {
            if (estruturaEscolhida == 1)
                listarVetor(vetor, tam);
            else
                listarLista(lista);

        } else if (opc == 4) {
            printf("Nome para buscar: ");
            fgets(nomeBusca, 30, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = 0;

            if (estruturaEscolhida == 1) {
                int pos = buscarSequencialVetor(vetor, tam, nomeBusca);
                if (pos != -1)
                    printf("Item encontrado!\n");
                else
                    printf("Item não encontrado!\n");

                printf("Comparações: %d\n", comparacoesSequencial);

            } else {
                int achou = buscarSequencialLista(lista, nomeBusca);
                printf(achou ? "Item encontrado!\n" : "Item não encontrado!\n");
                printf("Comparações: %d\n", comparacoesSequencial);
            }

        } else if (opc == 5 && estruturaEscolhida == 1) {
            ordenarVetor(vetor, tam);

        } else if (opc == 6 && estruturaEscolhida == 1) {
            printf("Nome para busca binária: ");
            fgets(nomeBusca, 30, stdin);
            nomeBusca[strcspn(nomeBusca, "\n")] = 0;

            int pos = buscarBinariaVetor(vetor, tam, nomeBusca);

            if (pos != -1)
                printf("Item encontrado!\n");
            else
                printf("Item não encontrado!\n");

            printf("Comparações: %d\n", comparacoesBinaria);
        }

    } while (opc != 0);

    printf("Encerrando...\n");
    return 0;
}

