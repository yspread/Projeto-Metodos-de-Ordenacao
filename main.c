#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct resultado_ {
    long long comparacoes;
    long long movimentacoes;
    double tempoExecucao;
}RESULTADO;


int main(){
    int n;
    printf("Digite o número de elementos: ");
    scanf("%d", &n);
    printf("\n");

    int *vetor = (int*)malloc(sizeof(int)*n);
    if (vetor == NULL){
        printf("Erro ao alocar memória para o vetor\n");
        return 1;
    }

    printf("Digite os elementos do vetor:\n");
    for(int i = 0; i < n; i++){
        scanf("%d", &vetor[i]);
    }

    int ordem;
    printf("Selecione o modelo dos registros no vetor:\n");
    printf("1.Elementos ordenados\n");
    printf("2.Elementos inversamente ordenados\n");
    printf("3.Elementos em ordem aleatória\n");
    printf("Sua escolha: ");
    scanf("%d", &ordem);
    printf("\n");

    int algoritimo;
    printf("Selecione o modelo dos registros no vetor:\n");
    printf("1.Bubble-Sort\n");
    printf("2.Selection-Sort\n");
    printf("3.Insertion-Sort\n");
    printf("4.Shell-Sort\n");
    printf("5.Quick-Sort\n");
    printf("6.Heap-Sort\n");
    printf("7.Merge-Sort\n");
    printf("8.Contagem dos Menores\n");
    printf("Radix-Sort\n");
    printf("Sua escolha: ");
    scanf("%d", &algoritimo);
    printf("\n");

    RESULTADO res;
    res.comparacoes = 0;
    res.movimentacoes = 0;
    res.tempoExecucao = 0;

    clock_t inicio, fim;
    inicio = clock();

    switch(algoritimo)        
    {
        case 1: 
        {
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
        case 4:
        {
            break;
        }
        case 5:
        {
            break;
        }
        case 6:
        {
            break;
        }
        case 7:
        {
            break;
        }
        case 8:
        {
            break;
        }
        default:
        {
            printf("Escolha do algoritimo inválida\n");
            return 0;
        }
    }

    fim = clock();
    res.tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Resultado Final:\n");
    printf("Comparações de Chaves: %lld\n", res.comparacoes);
    printf("Movimentações de Registro: %lld\n", res.movimentacoes);
    printf("Tempo de execução: %.6f segundos\n", res.tempoExecucao);

    free(vetor);
    return 0;

}

// Função auxiliar para trocar dois elementos
void troca(int  *a, int *b, long long *movimentacoes){
    int temp = *a;
    *a = *b;
    *b = temp;

    *movimentacoes += 2;
}

// Função do algoritimo bubble-sort
void bubblesort (int *vetor, int tamanho, int *comparacoes, int *movimentacoes)
{
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho - i - 1; j++)
        {
            if(vetor[j] > vetor[j + 1])
            {
                troca(&vetor[j], &vetor[j + 1], movimentacoes);
            }
            *comparacoes += 1;  
        }
    }

    return;
}

// Função do algoritimo Insertion-sort
void insertion_sort(int *vetor, int tamanho, int *comparacoes, int *movimentacoes){
    // Percorrer o array não ordenado
    for (int i = 1; i < tamanho; i++){
        int elemento = vetor[i];
        int j = i - 1;

        // Abrindo espaço para inserção no vetor ordenado (mover os elementos "maiores")
        while (j >= 0 && vetor[j] > elemento){
            *comparacoes += 1;
            vetor[j + 1] = vetor[j];
            j--;
            *movimentacoes += 1;
        }
        vetor[j + 1] = elemento;
        *movimentacoes += 1;
    }

    return;
}

// Função de partição do algoritimo quick-sort
int particionar_quick_sort(int *vetor, int inferior, int superior, long long *comparacoes, long long *movimentacoes){

    //Escolha do pivô pela mediana de 3
    int meio = inferior + (superior - inferior) / 2;

    // Logica para ordenar o inferior, superior e meio para encontrar a mediana
    if (vetor[meio] < vetor[inferior]){
        troca(&vetor[inferior], &vetor[meio], movimentacoes);
        *comparacoes += 1;
    }
    if (vetor[superior] < vetor[inferior]){
        troca(&vetor[inferior], &vetor[superior], movimentacoes);
        *comparacoes += 1;
    }
    if (vetor[meio] > vetor[superior]){
        troca(&vetor[meio], &vetor[superior], movimentacoes);
        *comparacoes += 1;
    }

    troca(&vetor[meio], &vetor[superior], movimentacoes);

    // Atribuir a mediana no pivo
    int pivo = vetor[superior];

    int i = (inferior - 1);
    for (int j = inferior; j <= superior - 1; j++){
        // Se o elemento atual for menor ou igual ao pivô incrementa o índice do menor elemento
        if (vetor[j] <= pivo){
            i++;
            troca(&vetor[i], &vetor[j], movimentacoes);
            *comparacoes += 1;
        }
    }
    // Coloca o pivô na posição correta
    troca(&vetor[i + 1], &vetor[superior],movimentacoes);

    // Retorna o índice onde a partição foi feita
    return (i + 1);
}

// Função principal do algoritimo quick-sort
void quick_sort(int *vetor, int inferior, int superior, int *comparacoes, int *movimentacoes){
    if (inferior < superior){
        // Encontrando o indice correto do pivô
        int indice_pivo = particionar_quick_sort(vetor, inferior, superior, comparacoes, movimentacoes);

        // Ordenando recursivamente os elementos antes e depois da partição
        quick_sort(vetor, inferior, indice_pivo - 1, comparacoes, movimentacoes);
        quick_sort(vetor, indice_pivo + 1, superior, comparacoes, movimentacoes);
    }
}