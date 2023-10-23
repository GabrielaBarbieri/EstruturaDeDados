#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct NoArvore* PtrNoArvore;

typedef struct NoArvore {
    char* palavra_chave;
    int frequencia;
    PtrNoArvore direita;
    PtrNoArvore esquerda;
} NoArvore;

typedef struct NoArvoreAVL* PtrNoArvoreAVL;

typedef struct NoArvoreAVL {
    char* palavra_chave;
    int frequencia;
    PtrNoArvoreAVL direita;
    PtrNoArvoreAVL esquerda;
    int altura;
} NoArvoreAVL;

int altura(PtrNoArvoreAVL no) {
    if (no == NULL) return -1;
    return no->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamento(PtrNoArvoreAVL no) {
    return altura(no->esquerda) - altura(no->direita);
}

void atualizarAltura(PtrNoArvoreAVL no) {
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));
}

PtrNoArvoreAVL rotacaoDireita(PtrNoArvoreAVL y) {
    PtrNoArvoreAVL x = y->esquerda;
    PtrNoArvoreAVL T = x->direita;

    x->direita = y;
    y->esquerda = T;

    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

PtrNoArvoreAVL rotacaoEsquerda(PtrNoArvoreAVL x) {
    PtrNoArvoreAVL y = x->direita;
    PtrNoArvoreAVL T = y->esquerda;

    y->esquerda = x;
    x->direita = T;

    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

PtrNoArvoreAVL inserirArvoreAVL(PtrNoArvoreAVL no, char* valor, int* comparar, int* atribuir) {
    if (no == NULL) {
        PtrNoArvoreAVL novo = malloc(sizeof(NoArvoreAVL));
        novo->palavra_chave = strdup(valor);
        novo->frequencia = 1;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
        return novo;
    }

    int cmp = strcmp(valor, no->palavra_chave);
    (*comparar) = (*comparar) + 1;

    if (cmp < 0) {
        no->esquerda = inserirArvoreAVL(no->esquerda, valor, comparar, atribuir);
    } else if (cmp > 0) {
        no->direita = inserirArvoreAVL(no->direita, valor, comparar, atribuir);
    } else {
        no->frequencia++;
    }

    atualizarAltura(no);

    int balanceamento = fatorBalanceamento(no);

    if (balanceamento > 1 && strcmp(valor, no->esquerda->palavra_chave) < 0) {
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && strcmp(valor, no->direita->palavra_chave) > 0) {
        return rotacaoEsquerda(no);
    }

    if (balanceamento > 1 && strcmp(valor, no->esquerda->palavra_chave) > 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if (balanceamento < -1 && strcmp(valor, no->direita->palavra_chave) < 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

void iniciaArvoreBinaria(PtrNoArvore *r) {
    (*r) = NULL;
}

bool estaVaziaArvoreBinaria(PtrNoArvore *r) {
    return ((*r) == NULL);
}

NoArvore* inserirArvoreBinaria(PtrNoArvore *no, char* valor, int* comparar, int* atribuir) {
    if ((*no) == NULL) {
        (*no) = malloc(sizeof(NoArvore));
        (*no)->palavra_chave = strdup(valor);
        (*no)->frequencia = 1;
        (*no)->direita = NULL;
        (*no)->esquerda = NULL;
        return (*no);
    }

    int cmp = strcmp(valor, (*no)->palavra_chave);
    (*comparar) = (*comparar) + 1;

    if (cmp < 0) {
        (*no)->esquerda = inserirArvoreBinaria(&((*no)->esquerda), valor, comparar, atribuir);
    } else if (cmp > 0) {
        (*no)->direita = inserirArvoreBinaria(&((*no)->direita), valor, comparar, atribuir);
    } else {
        (*no)->frequencia++;
    }

    return (*no);
}

void EmOrdemArvoreBinaria(PtrNoArvore no) {
    if (no == NULL) return;
    EmOrdemArvoreBinaria(no->esquerda);
    printf("%s: %d\n", no->palavra_chave, no->frequencia);
    EmOrdemArvoreBinaria(no->direita);
}

void EmOrdemPrincipal(PtrNoArvore no) {
    printf("EmOrdem = { ");
    EmOrdemArvoreBinaria(no);
    printf("}\n");
}

void liberarArvore(PtrNoArvore no) {
    if (no == NULL) return;
    liberarArvore(no->esquerda);
    liberarArvore(no->direita);
    free(no->palavra_chave);
    free(no);
}

void EmOrdemArvoreAVL(PtrNoArvoreAVL no) {
    if (no == NULL) return;
    EmOrdemArvoreAVL(no->esquerda);
    printf("%s: %d\n", no->palavra_chave, no->frequencia);
    EmOrdemArvoreAVL(no->direita);
}

void EmOrdemPrincipalAVL(PtrNoArvoreAVL no) {
    printf("EmOrdem AVL = { ");
    EmOrdemArvoreAVL(no);
    printf("}\n");
}

void liberarArvoreAVL(PtrNoArvoreAVL no) {
    if (no == NULL) return;
    liberarArvoreAVL(no->esquerda);
    liberarArvoreAVL(no->direita);
    free(no->palavra_chave);
    free(no);
}

typedef struct {
    char* palavra;
    int frequencia;
} FrequenciaPalavra;

FrequenciaPalavra* novaFrequenciaPalavra(char* palavra) {
    FrequenciaPalavra* nova = malloc(sizeof(FrequenciaPalavra));
    nova->palavra = strdup(palavra);
    nova->frequencia = 1;
    return nova;
}

int compararFrequenciaPalavra(const void* a, const void* b) {
    return strcmp(((FrequenciaPalavra*)a)->palavra, ((FrequenciaPalavra*)b)->palavra);
}

void imprimirFrequencias(FrequenciaPalavra* frequencias, int numFrequencias) {
    for (int i = 0; i < numFrequencias; i++) {
        printf("%s: %d\n", frequencias[i].palavra, frequencias[i].frequencia);
    }
}



int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <arquivo> <estrutura>\n", argv[0]);
        return 1;
    }

    char* arquivo_nome = argv[1];
    char* estrutura = argv[2];
    PtrNoArvore raiz;
    iniciaArvoreBinaria(&raiz);

    PtrNoArvoreAVL raizAVL = NULL;

    FILE* arquivo = fopen(arquivo_nome, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char palavra[200];
    int comparar = 0, atribuir = 0;
    int compararAVL = 0, atribuirAVL = 0;

    clock_t inicioBinaria = clock();
    clock_t inicioAVL = clock();

    while (fscanf(arquivo, "%199s", palavra) == 1) {
        for (int i = 0; palavra[i] != '\0'; i++) {
            palavra[i] = tolower(palavra[i]);
            if (!isalpha(palavra[i])) {
                palavra[i] = '\0';
                break;
            }
        }
        if (palavra[0] != '\0') {
            if (strcmp(estrutura, "arvore-binaria") == 0) {
                raiz = inserirArvoreBinaria(&raiz, palavra, &comparar, &atribuir);
            } else if (strcmp(estrutura, "arvore-avl") == 0) {
                raizAVL = inserirArvoreAVL(raizAVL, palavra, &compararAVL, &atribuirAVL);
            }
        }
    }

    clock_t fimBinaria = clock();
    clock_t fimAVL = clock();

    fclose(arquivo);

    if (strcmp(estrutura, "arvore-binaria") == 0) {
        printf("arvore binaria:\n");
        printf("%d comparacoes\n", comparar);
        printf("%d atribuicoes\n", atribuir);
        printf("%.2f segundos\n", (double)(fimBinaria - inicioBinaria) / CLOCKS_PER_SEC);

        FrequenciaPalavra* frequencias = malloc(sizeof(FrequenciaPalavra) * numPalavras);
        int numPalavras = 0;
        preencherFrequencias(raiz, frequencias, &numPalavras);
        qsort(frequencias, numPalavras, sizeof(FrequenciaPalavra), compararFrequenciaPalavra);
        imprimirFrequencias(frequencias, numPalavras);
        for (int i = 0; i < numPalavras; i++) {
            free(frequencias[i].palavra);
        }
        free(frequencias);

        EmOrdemPrincipal(raiz);
        liberarArvore(raiz);
    }
    else if (strcmp(estrutura, "arvore-avl") == 0) {
        printf("arvore AVL:\n");
        printf("%d comparacoes\n", compararAVL);
        printf("%d atribuicoes\n", atribuirAVL);
        printf("%.2f segundos\n", (double)(fimAVL - inicioAVL) / CLOCKS_PER_SEC);

        FrequenciaPalavra* frequenciasAVL = malloc(sizeof(FrequenciaPalavra) * numPalavrasAVL);
        int numPalavrasAVL = 0;
        preencherFrequenciasAVL(raizAVL, frequenciasAVL, &numPalavrasAVL);
        qsort(frequenciasAVL, numPalavrasAVL, sizeof(FrequenciaPalavra), compararFrequenciaPalavra);
        imprimirFrequencias(frequenciasAVL, numPalavrasAVL);
        for (int i = 0; i < numPalavrasAVL; i++) {
            free(frequenciasAVL[i].palavra);
        }
        free(frequenciasAVL);

        EmOrdemPrincipalAVL(raizAVL);
        liberarArvoreAVL(raizAVL);
    }

    return 0;
}
